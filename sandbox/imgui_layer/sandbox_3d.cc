#include "sandbox_3d.h"
#define IMGUI_DEFINE_MATH_OPERATORS
#include <core/audio/audio.h>
#include <imgui.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/string_cast.hpp>
#include <limits>

#include "core/renderer/font.h"
#include "imgui_gizmos.h"
#include "imgui_layer/file_dialog.h"
#include "imgui_layer/inspector.h"

bool useWindow = false;
float camDistance = 8.f;
static ImGuiExtend::OPERATION mCurrentGizmoOperation(ImGuiExtend::TRANSLATE);

void EditTransform(glm::mat4& view_matrix, glm::mat4& projection_matrix, glm::mat4& model_matrix,
                   bool editTransformDecomposition) {
  static ImGuiExtend::MODE mCurrentGizmoMode(ImGuiExtend::LOCAL);
  static bool use_snap = false;
  static glm::vec3 snap(1.0f);
  // TODO bound snap 是甚麼?
  static float bounds[] = {-0.5f, -0.5f, -0.5f, 0.5f, 0.5f, 0.5f};
  static float boundsSnap[] = {0.1f, 0.1f, 0.1f};
  static bool boundSizing = false;
  static bool boundSizingSnap = false;

  if (editTransformDecomposition) {
    if (ImGui::IsKeyPressed(ImGuiKey_T)) mCurrentGizmoOperation = ImGuiExtend::TRANSLATE;
    if (ImGui::IsKeyPressed(ImGuiKey_E)) mCurrentGizmoOperation = ImGuiExtend::ROTATE;
    if (ImGui::IsKeyPressed(ImGuiKey_R)) mCurrentGizmoOperation = ImGuiExtend::SCALE;
    if (ImGui::RadioButton("Translate", mCurrentGizmoOperation == ImGuiExtend::TRANSLATE))
      mCurrentGizmoOperation = ImGuiExtend::TRANSLATE;
    ImGui::SameLine();
    if (ImGui::RadioButton("Rotate", mCurrentGizmoOperation == ImGuiExtend::ROTATE))
      mCurrentGizmoOperation = ImGuiExtend::ROTATE;
    ImGui::SameLine();
    if (ImGui::RadioButton("Scale", mCurrentGizmoOperation == ImGuiExtend::SCALE))
      mCurrentGizmoOperation = ImGuiExtend::SCALE;
    ImGui::SameLine();
    if (ImGui::RadioButton("Universal", mCurrentGizmoOperation == ImGuiExtend::UNIVERSAL))
      mCurrentGizmoOperation = ImGuiExtend::UNIVERSAL;

    glm::vec3 translation, rotation, scale;  // TODO rotation 應該是各個軸的歐拉角?
    ImGuiExtend::DecomposeTranslationMatrix(model_matrix, translation, rotation, scale);
    ImGui::InputFloat3("Tr", value_ptr(translation));
    ImGui::InputFloat3("Rt", value_ptr(rotation));
    ImGui::InputFloat3("Sc", value_ptr(scale));
    ImGuiExtend::RecomposeMatrixFromComponents(translation, rotation, scale, model_matrix);

    if (mCurrentGizmoOperation != ImGuiExtend::SCALE) {
      if (ImGui::RadioButton("Local", mCurrentGizmoMode == ImGuiExtend::LOCAL)) mCurrentGizmoMode = ImGuiExtend::LOCAL;
      ImGui::SameLine();
      if (ImGui::RadioButton("World", mCurrentGizmoMode == ImGuiExtend::WORLD)) mCurrentGizmoMode = ImGuiExtend::WORLD;
    }

    if (ImGui::IsKeyPressed(ImGuiKey_S)) use_snap = !use_snap;
    ImGui::Checkbox("##UseSnap", &use_snap);
    ImGui::SameLine();

    switch (mCurrentGizmoOperation) {
      case ImGuiExtend::TRANSLATE:
        ImGui::InputFloat3("Snap", &snap[0]);
        break;
      case ImGuiExtend::ROTATE:
        ImGui::InputFloat("Angle Snap", &snap[0]);
        break;
      case ImGuiExtend::SCALE:
        ImGui::InputFloat("Scale Snap", &snap[0]);
        break;
    }

    ImGui::Checkbox("Bound Sizing", &boundSizing);
    if (boundSizing) {
      ImGui::PushID(3);
      ImGui::Checkbox("##BoundSizing", &boundSizingSnap);
      ImGui::SameLine();
      ImGui::InputFloat3("Snap", boundsSnap);
      ImGui::PopID();
    }
  }

  ImGuiIO& io = ImGui::GetIO();
  float viewManipulateRight = ImGui::GetMainViewport()->Pos.x + ImGui::GetMainViewport()->Size.x;
  float viewManipulateTop = ImGui::GetMainViewport()->Pos.y;
  static ImGuiWindowFlags gizmoWindowFlags = 0;
  if (useWindow) {
    ImGui::SetNextWindowSize(ImVec2(800, 400), ImGuiCond_Appearing);
    ImGui::SetNextWindowPos(ImVec2(400, 20), ImGuiCond_Appearing);
    ImGui::PushStyleColor(ImGuiCol_WindowBg, (ImVec4)ImColor(0.35f, 0.3f, 0.3f));
    ImGui::Begin("Gizmo", 0, gizmoWindowFlags);
    ImGuiExtend::SetDrawlist();
    float windowWidth = (float)ImGui::GetWindowWidth();
    float windowHeight = (float)ImGui::GetWindowHeight();
    ImGuiExtend::SetRect(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, windowWidth, windowHeight);
    viewManipulateRight = ImGui::GetWindowPos().x + windowWidth;
    viewManipulateTop = ImGui::GetWindowPos().y;
    ImGuiWindow* window = ImGui::GetCurrentWindow();
    gizmoWindowFlags =
        ImGui::IsWindowHovered() && ImGui::IsMouseHoveringRect(window->InnerRect.Min, window->InnerRect.Max)
            ? ImGuiWindowFlags_NoMove
            : 0;
  } else {
    ImGuiExtend::SetRect(ImGui::GetMainViewport()->Pos.x, ImGui::GetMainViewport()->Pos.y,
                         ImGui::GetMainViewport()->Size.x, ImGui::GetMainViewport()->Size.y);
  }

  // ImGuiExtend::DrawCubes(cameraView, cameraProjection, &objectMatrix[0][0], 1); // TODO fix 1
  ImGuiExtend::Manipulate(value_ptr(view_matrix), value_ptr(projection_matrix), mCurrentGizmoOperation,
                          mCurrentGizmoMode, value_ptr(model_matrix), NULL, use_snap ? &snap[0] : NULL,
                          boundSizing ? bounds : NULL, boundSizingSnap ? boundsSnap : NULL);

  ImGuiExtend::ViewManipulate(value_ptr(view_matrix), camDistance, ImVec2(viewManipulateRight - 128, viewManipulateTop),
                              ImVec2(128, 128), 0x00000000);
  printf("%f, %f\n", viewManipulateRight - 128, viewManipulateTop);

  if (useWindow) {
    ImGui::End();
    ImGui::PopStyleColor(1);
  }
}

using namespace genesis;
Sandbox3D::Sandbox3D() : ImGuiLayer("Sandbox3D") {
  auto& app = Application::GetInstance();
  auto& window = app.GetWindow();
  float ratio = float(window.GetWidth()) / window.GetHeight();
  window.SetCursorMode(CursorMode::kNormal);

  AudioManager::LoadBankFile("./assets/sounds/Master.bank");
  AudioManager::LoadBankFile("./assets/sounds/Master.strings.bank");
  AudioManager::LoadBankFile("./assets/sounds/SFX.bank");
  AudioManager::LoadBankFile("./assets/sounds/Vehicles.bank");

  AudioManager::LoadEvent("event:/Vehicles/Ride-on Mower");
  AudioManager::SetEventParameter("event:/Vehicles/Ride-on Mower", "RPM", 650.0f);

  std::vector<std::filesystem::path> faces_path({
      "./assets/textures/skybox/right.jpg",
      "./assets/textures/skybox/left.jpg",
      "./assets/textures/skybox/top.jpg",
      "./assets/textures/skybox/bottom.jpg",
      "./assets/textures/skybox/front.jpg",
      "./assets/textures/skybox/back.jpg",
  });
  model_shader_ = Shader::Create("./assets/shaders/model.vert", "./assets/shaders/model.frag");
  outline_shader = Shader::Create("./assets/shaders/outline.vert", "./assets/shaders/outline.frag");

  camera_3d_ = std::make_shared<CameraController>(glm::radians(60.0f), ratio, 0.01f, 300.0f, glm::vec3(0, 0, 10),
                                                  glm::vec3(0, 0, 0));
  camera_3d_->SetSkybox(faces_path);
  camera_3d_->SetClearColor({1.0f, 1.0f, 1.0f, 1.0f});

  scene_.AddGameObject("robot");
  scene_.AddGameObject("light");

  auto& model_ = scene_.GetGameObject("robot");
  auto& light_ = scene_.GetGameObject("light");
  auto* mesh_filter = dynamic_cast<MeshFilter*>(model_.AddComponent("Mesh Filter"));
  mesh_filter->SetModel("./assets/models/Nanosuit/nanosuit.obj");

  auto* light = dynamic_cast<Light*>(light_.AddComponent("Light"));
  light->SetPosition({0.0f, 30.0f, 30.0f});
  light->SetColor({1.0f, 1.0f, 1.0f});
  light->SetDirection({1.0f, 1.0f, 1.0f});
  light->SetLightType(LightType::Point);

  Font::LoadFont("./assets/fonts/SedanSC-Regular.ttf", "SedanSC-Regular", 16);
}

void Sandbox3D::OnUpdate(TimeStep time_step) {
  auto& renderer_3d = Renderer3D();
  auto& camera = camera_3d_->GetCamera();
  renderer_3d.BeginScene(camera);

  if (Input::GetInstance().IsKeyPressed(Keycode::kKey0)) {
    AudioManager::StartEvent("event:/Vehicles/Ride-on Mower");
  }
  AudioManager::Update();
  FMOD_3D_ATTRIBUTES listener_attribute = {{0}};

  listener_attribute.position = FMOD_VECTOR{camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z};
  listener_attribute.forward = FMOD_VECTOR{camera.GetForward().x, camera.GetForward().y, camera.GetForward().z};
  listener_attribute.up = FMOD_VECTOR{camera.GetUp().x, camera.GetUp().y, camera.GetUp().z};
  AudioManager::SetListenerAttribute(0, listener_attribute);

  auto& model_ = scene_.GetGameObject("robot");
  auto& light_ = scene_.GetGameObject("light");

  auto* light = dynamic_cast<Light*>(light_.GetComponent("Light"));
  light->SetPosition({20.0f, 0.0f, 20.0f});

  auto transform = dynamic_cast<Transform*>(model_.GetComponent("Transform"));
  if (!transform) {
    return;
  }
  FMOD_3D_ATTRIBUTES event_attribute = {{0}};
  event_attribute.position =
      FMOD_VECTOR{transform->GetPosition().x, transform->GetPosition().y, transform->GetPosition().z};
  event_attribute.forward = FMOD_VECTOR{0, 0, 1};
  event_attribute.up = FMOD_VECTOR{0, 1, 0};
  AudioManager::SetEventAttribute("event:/Vehicles/Ride-on Mower", event_attribute);

  glm::mat4 trans_mat = glm::translate(glm::mat4(1.0f), transform->GetPosition());
  auto rotation = transform->GetRotation();
  glm::mat4 rotate_mat =
      glm::eulerAngleYXZ(glm::radians(rotation.y), glm::radians(rotation.x), glm::radians(rotation.z));
  glm::mat4 scale_mat = glm::scale(glm::mat4(1.0f), transform->GetScale());
  glm::mat4 model = trans_mat * rotate_mat * scale_mat;

  auto component_model = dynamic_cast<const MeshFilter*>(model_.GetComponent("Mesh Filter"));
  auto component_light = dynamic_cast<const Light*>(light_.GetComponent("Light"));

  auto& render_command = RenderCommand::GetInstance();
  render_command.SetDrawMode(DrawMode::kFill);

  render_command.SetStencilTest(true);
  render_command.SetStencilFunc(StencilFunc::kAlways, 1, 0xff);
  render_command.SetStencilMask(true);
  renderer_3d.Submit(*model_shader_, component_model->GetModel(), model, component_light, &camera);
  render_command.SetStencilFunc(StencilFunc::kNotEqual, 1, 0xff);
  render_command.SetStencilMask(false);

  render_command.SetDepthTest(false);
  renderer_3d.Submit(*outline_shader, component_model->GetModel(), model, nullptr, nullptr);
  render_command.SetStencilMask(true);
  render_command.SetStencilFunc(StencilFunc::kAlways, 0, 0xff);
  render_command.SetDepthTest(true);

  auto& grid = Grid::GetInstance();
  grid.GetShader().Bind();
  grid.GetShader().SetUniform("u_grid_opacity", grid.GetOpacity());
  grid.GetShader().SetUniform("u_grid_plane_mode", (int)grid.GetGridMode());
  renderer_3d.Submit(grid.GetShader(), grid.GetVertexArray(), {1.0f}, nullptr, &camera);
  renderer_3d.EndScene();

  camera_3d_->OnUpdate(time_step);
}

EventState Sandbox3D::OnMouseButtonPressedEvent(MouseButtonPressedEvent& event) { return EventState::kHandled; }

EventState Sandbox3D::OnWindowResizeEvent(WindowResizeEvent& event) {
  RenderCommand::GetInstance().SetViewport(0, 0, event.GetWidth(), event.GetHeight());
  return EventState::kHandled;
}

EventState Sandbox3D::OnEvent(Event& event) {
  EventDispatcher event_dispatcher(event);
  camera_3d_->OnEvent(event);
  event_dispatcher.Dispatch<MouseButtonPressedEvent>(BIND_METHOD(Sandbox3D::OnMouseButtonPressedEvent));
  event_dispatcher.Dispatch<WindowResizeEvent>(BIND_METHOD(Sandbox3D::OnWindowResizeEvent));
  return EventState::kHandled;
}

void Sandbox3D::OnImguiRender() {
  ImGuiIO& io = ImGui::GetIO();
  auto& app = Application::GetInstance();
  io.DisplaySize = ImVec2((float)app.GetWindow().GetWidth(), (float)app.GetWindow().GetHeight());

  auto& model_ = scene_.GetGameObject("robot");
  dynamic_cast<genesis::Inspector&>(app.GetLayer("Inspector")).SetGameObject(&model_);

  // TODO beautify this
  auto transform = dynamic_cast<Transform*>(model_.GetComponent("Transform"));
  glm::mat4 trans_mat = glm::translate(glm::mat4(1.0f), transform->GetPosition());
  auto rotation = transform->GetRotation();
  glm::mat4 rotate_mat =
      glm::eulerAngleYXZ(glm::radians(rotation.y), glm::radians(rotation.x), glm::radians(rotation.z));
  glm::mat4 scale_mat = glm::scale(glm::mat4(1.0f), transform->GetScale());
  glm::mat4 model = trans_mat * rotate_mat * scale_mat;
  auto& camera = camera_3d_->GetCamera();
  ImGuiExtend::SetOrthographic(camera.GetMode() == CameraMode::Orthographic);  // use perspective
  ImGuiExtend::BeginFrame();

  ImGui::Begin("Editor");
  if (ImGuiExtend::IsUsing()) {
    ImGui::Text("Using gizmo");
  } else {
    ImGui::Text(ImGuiExtend::IsOver() ? "Over gizmo" : "");
    ImGui::SameLine();
    ImGui::Text(ImGuiExtend::IsOver(ImGuiExtend::TRANSLATE) ? "Over translate gizmo" : "");
    ImGui::SameLine();
    ImGui::Text(ImGuiExtend::IsOver(ImGuiExtend::ROTATE) ? "Over rotate gizmo" : "");
    ImGui::SameLine();
    ImGui::Text(ImGuiExtend::IsOver(ImGuiExtend::SCALE) ? "Over scale gizmo" : "");
  }
  ImGuiExtend::SetID(1);  // TODO fix id
  glm::mat4 camera_view = camera.GetView();
  glm::mat4 camera_projection = camera.GetProjection();
  EditTransform(camera_view, camera_projection, model, true);

  ImGui::End();
}
