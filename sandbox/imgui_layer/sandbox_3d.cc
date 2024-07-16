#include "sandbox_3d.h"
#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/string_cast.hpp>
#include <limits>

#include "core/renderer/font.h"
#include "core/renderer/shader_library.h"
#include "imgui_gizmos.h"
#include "imgui_layer/file_dialog.h"
#include "imgui_layer/inspector.h"

bool useWindow = false;

void EditTransform(glm::mat4& view_matrix, const glm::mat4& projection_matrix, glm::mat4& model_matrix,
                   bool editTransformDecomposition) {
  static ImGuiExtend::OPERATION current_gizmos_operation(ImGuiExtend::TRANSLATE);
  static ImGuiExtend::MODE current_gizmos_mode(ImGuiExtend::LOCAL);
  static bool use_snap = false;
  static float translate_snap[3] = {1.0f, 1.0f, 1.0f};
  static float rotate_snap = 10.0f;
  static float scale_snap = 0.5f;
  // TODO bound snap 是甚麼?好像是 bounding box，但目前不需要
  static float bounds[] = {-0.5f, -0.5f, -0.5f, 0.5f, 0.5f, 0.5f};
  static float boundsSnap[] = {0.1f, 0.1f, 0.1f};
  static bool boundSizing = false;
  static bool boundSizingSnap = false;

  if (editTransformDecomposition) {
    if (ImGui::IsKeyPressed(ImGuiKey_T)) current_gizmos_operation = ImGuiExtend::TRANSLATE;
    if (ImGui::IsKeyPressed(ImGuiKey_R)) current_gizmos_operation = ImGuiExtend::ROTATE;
    if (ImGui::IsKeyPressed(ImGuiKey_S)) current_gizmos_operation = ImGuiExtend::SCALE;
    if (ImGui::RadioButton("Translate", current_gizmos_operation == ImGuiExtend::TRANSLATE))
      current_gizmos_operation = ImGuiExtend::TRANSLATE;
    ImGui::SameLine();
    if (ImGui::RadioButton("Rotate", current_gizmos_operation == ImGuiExtend::ROTATE))
      current_gizmos_operation = ImGuiExtend::ROTATE;
    ImGui::SameLine();
    if (ImGui::RadioButton("Scale", current_gizmos_operation == ImGuiExtend::SCALE))
      current_gizmos_operation = ImGuiExtend::SCALE;
    ImGui::SameLine();
    if (ImGui::RadioButton("Universal", current_gizmos_operation == ImGuiExtend::UNIVERSAL))
      current_gizmos_operation = ImGuiExtend::UNIVERSAL;

    // TODO Local World 的差異是甚麼?
    if (current_gizmos_operation != ImGuiExtend::SCALE) {
      if (ImGui::RadioButton("Local", current_gizmos_mode == ImGuiExtend::LOCAL))
        current_gizmos_mode = ImGuiExtend::LOCAL;
      ImGui::SameLine();
      if (ImGui::RadioButton("World", current_gizmos_mode == ImGuiExtend::WORLD))
        current_gizmos_mode = ImGuiExtend::WORLD;
    }

    if (ImGui::IsKeyPressed(ImGuiKey_E)) use_snap = !use_snap;
    ImGui::Checkbox("Snap Enable", &use_snap);

    ImGui::InputFloat3("Translate Snap", &translate_snap[0]);
    ImGui::InputFloat("Rotate Snap", &rotate_snap);
    ImGui::InputFloat("Scale Snap", &scale_snap);

    // ImGui::Checkbox("Bound Sizing", &boundSizing);
    // if (boundSizing) {
    //   ImGui::PushID(3);
    //   ImGui::Checkbox("##BoundSizing", &boundSizingSnap);
    //   ImGui::SameLine();
    //   ImGui::InputFloat3("Snap", boundsSnap);
    //   ImGui::PopID();
    // }
  }

  ImGuiIO& io = ImGui::GetIO();
  ImVec2 viewManipulateRightTop =
      ImVec2(ImGui::GetMainViewport()->Pos.x + ImGui::GetMainViewport()->Size.x, ImGui::GetMainViewport()->Pos.y);
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
    viewManipulateRightTop = ImVec2(ImGui::GetWindowPos().x + windowWidth, ImGui::GetWindowPos().y);
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
  ImGuiExtend::Manipulate(view_matrix, projection_matrix, current_gizmos_operation, current_gizmos_mode, model_matrix,
                          nullptr, use_snap ? &translate_snap[0] : NULL, boundSizing ? bounds : NULL,
                          boundSizingSnap ? boundsSnap : NULL);
  float camDistance = glm::length(glm::vec3(model_matrix[3] - inverse(view_matrix)[3]));
  ImGuiExtend::ViewManipulate(view_matrix, camDistance, viewManipulateRightTop - ImVec2(128, 0), ImVec2(128, 128),
                              ImVec4(0.0f, 0.0f, 0.0f, 0.0f));

  if (useWindow) {
    ImGui::End();
    ImGui::PopStyleColor(1);
  }
}

using namespace genesis;
Sandbox3D::Sandbox3D() : ImGuiLayer("Sandbox3D") {
  auto& app = Application::GetInstance();
  auto& window = app.GetWindow();
  RenderCommand::GetInstance().OpenDebugMessage(true);

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

  ShaderLibrary::AddShader("model_shader", "./assets/shaders/model.vert", "./assets/shaders/model.frag");
  ShaderLibrary::AddShader("outline_shader", "./assets/shaders/outline.vert", "./assets/shaders/outline.frag");
  ShaderLibrary::AddShader("post_processing_shader", "./assets/shaders/post_processing.vert",
                           "./assets/shaders/post_processing.frag");

  camera_3d_ = std::make_shared<CameraController>(glm::radians(60.0f), ratio, 0.01f, 300.0f, glm::vec3(0, 5, 10),
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

  post_texture_color_ = Texture2D::Create(nullptr, TextureFormat::kRGBA, window.GetWidth(), window.GetHeight());
  post_texture_depth_ = Texture2D::Create(nullptr, TextureFormat::kDepthStencil, window.GetWidth(), window.GetHeight());
  frame_buffer_ = FrameBuffer::Create();
  frame_buffer_->BindTexture(*post_texture_color_, 0, AttachmentType::kColor);
  frame_buffer_->BindTexture(*post_texture_depth_, 0, AttachmentType::kDepthStencil);

  Font::LoadFont("./assets/fonts/SedanSC-Regular.ttf", "SedanSC-Regular", 16);
}

void Sandbox3D::OnUpdate(TimeStep time_step) {
  auto& camera = camera_3d_->GetCamera();
  if (Input::GetInstance().IsKeyPressed(Keycode::kKey0)) {
    AudioManager::StartEvent("event:/Vehicles/Ride-on Mower");
  }
  AudioManager::Update();

  // FMOD_3D_ATTRIBUTES listener_attribute = {{0}};
  // listener_attribute.position = FMOD_VECTOR{camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z};
  // listener_attribute.forward = FMOD_VECTOR{camera.GetForward().x, camera.GetForward().y, camera.GetForward().z};
  // listener_attribute.up = FMOD_VECTOR{camera.GetUp().x, camera.GetUp().y, camera.GetUp().z};
  // AudioManager::SetListenerAttribute(0, listener_attribute);

  auto& model_ = scene_.GetGameObject("robot");

  auto transform = dynamic_cast<Transform*>(model_.GetComponent("Transform"));
  FMOD_3D_ATTRIBUTES event_attribute = {{0}};
  event_attribute.position =
      FMOD_VECTOR{transform->GetPosition().x, transform->GetPosition().y, transform->GetPosition().z};
  event_attribute.forward = FMOD_VECTOR{0, 0, 1};
  event_attribute.up = FMOD_VECTOR{0, 1, 0};
  // AudioManager::SetEventAttribute("event:/Vehicles/Ride-on Mower", event_attribute);

  camera_3d_->OnUpdate(time_step);
}

void Sandbox3D::OnRender() {
  RenderCommand::GetInstance().BindDefaultFrameBuffer();
  RenderCommand::GetInstance().Clear();
  frame_buffer_->Bind();
  RenderCommand::GetInstance().Clear();

  auto& renderer_3d = Renderer3D();
  auto& camera = camera_3d_->GetCamera();
  renderer_3d.BeginScene(camera);  // draw sky in here

  auto& model_ = scene_.GetGameObject("robot");
  auto& light_ = scene_.GetGameObject("light");

  auto* light = dynamic_cast<Light*>(light_.GetComponent("Light"));
  light->SetPosition({20.0f, 0.0f, 20.0f});

  auto transform = dynamic_cast<Transform*>(model_.GetComponent("Transform"));
  if (!transform) {
    return;
  }
  glm::mat4 model = transform->GetModel();

  auto component_model = dynamic_cast<const MeshFilter*>(model_.GetComponent("Mesh Filter"));
  auto component_light = dynamic_cast<const Light*>(light_.GetComponent("Light"));

  auto& render_command = RenderCommand::GetInstance();
  frame_buffer_->Bind();
  render_command.SetDepthTest(true);
  renderer_3d.Submit(ShaderLibrary::GetShader("model_shader"), component_model->GetModel(), model, component_light,
                     &camera);

  // render_command.SetStencilTest(true);
  // render_command.SetStencilMask(true);
  // renderer_3d.Submit(*model_shader_, component_model->GetModel(), model, component_light, &camera);
  // render_command.SetStencilFunc(StencilFunc::kNotEqual, 1, 0xff);
  // render_command.SetStencilMask(false);

  // render_command.SetDepthTest(false);
  // renderer_3d.Submit(*outline_shader_, component_model->GetModel(), model, nullptr, nullptr);
  // render_command.SetStencilMask(true);
  // render_command.SetStencilFunc(StencilFunc::kAlways, 0, 0xff);
  // render_command.SetDepthTest(true);

  auto& grid = Grid::GetInstance();
  grid.GetShader().Bind();
  grid.GetShader().SetUniform("u_grid_opacity", grid.GetOpacity());
  grid.GetShader().SetUniform("u_grid_plane_mode", (int)grid.GetGridMode());
  renderer_3d.Submit(grid.GetShader(), grid.GetVertexArray(), {1.0f}, nullptr, &camera);

  // post processing
  RenderCommand::GetInstance().BindDefaultFrameBuffer();
  render_command.SetDepthTest(false);
  static float quadVertices[] = {-1.0f, 1.0f, 1.0f, 1.0f, 1.0f, -1.0f, 1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f};
  static std::shared_ptr<VertexBuffer> vb = VertexBuffer::Create(quadVertices, sizeof(quadVertices));
  static const BufferLayout bl({MathDataType::kFloat2});
  static std::shared_ptr<VertexArray> va = VertexArray::Create(bl);
  va->SetVertexBuffer(vb);
  post_texture_color_->Bind(0);
  auto& post_processing_shader = ShaderLibrary::GetShader("post_processing_shader");
  post_processing_shader.Bind();
  post_processing_shader.SetUniform("u_origin_texture", 0);
  renderer_3d.Submit(post_processing_shader, *va, glm::mat4{1.0f}, nullptr, nullptr);

  renderer_3d.EndScene();
}

EventState Sandbox3D::OnWindowResizeEvent(WindowResizeEvent& event) {
  RenderCommand::GetInstance().SetViewport(0, 0, event.GetWidth(), event.GetHeight());
  return EventState::kHandled;
}

EventState Sandbox3D::OnEvent(Event& event) {
  EventDispatcher event_dispatcher(event);
  camera_3d_->OnEvent(event);
  event_dispatcher.Dispatch<WindowResizeEvent>(BIND_METHOD(Sandbox3D::OnWindowResizeEvent));
  return EventState::kHandled;
}

void Sandbox3D::OnImguiRender() {
  ImGuiIO& io = ImGui::GetIO();
  auto& app = Application::GetInstance();
  io.DisplaySize = ImVec2((float)app.GetWindow().GetWidth(), (float)app.GetWindow().GetHeight());

  auto& model_ = scene_.GetGameObject("robot");
  auto transform = dynamic_cast<Transform*>(model_.GetComponent("Transform"));
  dynamic_cast<genesis::Inspector&>(app.GetLayer("Inspector")).SetGameObject(&model_);

  ImGui::ShowDemoWindow();

  // TODO beautify this
  glm::mat4 model_mat = transform->GetModel();
  auto& camera = camera_3d_->GetCamera();

  ImGuiExtend::SetOrthographic(camera.GetMode() == CameraMode::Orthographic);  // use perspective
  ImGuiExtend::BeginFrame();

  ImGui::Begin("Gizmos");
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

  glm::mat4 view_mat = camera.GetView();
  glm::mat4 projection_mat = camera.GetProjection();

  EditTransform(view_mat, projection_mat, model_mat, true);

  view_mat = glm::inverse(view_mat);
  camera.SetUp(view_mat[1]);        // column 2 -> up
  camera.SetForward(-view_mat[2]);  // column 3 -> forward
  camera.SetPosition(view_mat[3]);  // column 4 -> position

  // reset transform
  glm::vec3 translation, rotate, scale;
  ImGuiExtend::DecomposeTranslationMatrix(model_mat, translation, rotate, scale);
  transform->SetPosition(translation);
  transform->SetRotation(rotate);
  transform->SetScale(scale);

  ImGui::End();
}
