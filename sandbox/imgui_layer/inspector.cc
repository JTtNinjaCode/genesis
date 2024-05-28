#include "inspector.h"
#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "imgui_layer/file_dialog.h"
#include "imgui_layer/global_layer_controller.h"
namespace genesis {
void Inspector::SetGameObject(GameObject* game_object) { game_object_ = game_object; }
void Inspector::OnImguiRender() {
  auto& show_inspector = LayerContext::layer_context.inspector;
  if (!show_inspector) {
    return;
  }
  ImGui::Begin("Inspector");
  if (game_object_ != nullptr) {
    auto transform = dynamic_cast<Transform*>(game_object_->GetComponent("Transform"));
    auto position = transform->GetPosition();
    auto rotation = transform->GetRotation();
    auto scale = transform->GetScale();

    ImGui::Text("Transform");
    ImGui::DragFloat3("Position", glm::value_ptr(position), 1.0f, std::numeric_limits<float>::max(),
                      -std::numeric_limits<float>::max());
    ImGui::DragFloat3("Rotation", glm::value_ptr(rotation), 1.0f, std::numeric_limits<float>::max(),
                      -std::numeric_limits<float>::max());
    ImGui::DragFloat3("Scale", glm::value_ptr(scale), 1.0f, 0.0f, std::numeric_limits<float>::max());

    transform->SetPosition(position);
    transform->SetRotation(rotation);
    transform->SetScale(scale);

    FileDialog& file_dialog = FileDialog::Instance();
    if (ImGui::Button("Open a texture")) {
      file_dialog.Open("TextureOpenDialog", "Open a texture",
                       "Image file (*.png;*.jpg;*.jpeg;*.bmp;*.tga){.png,.jpg,.jpeg,.bmp,.tga},.*");
    }
    if (file_dialog.IsDone("TextureOpenDialog")) {
      if (file_dialog.HasResult()) {
        std::string res = file_dialog.GetResult().u8string();
        printf("OPEN[%s]\n", res.c_str());
      }
      file_dialog.Close();
    }
  }
  ImGui::End();
}

}  // namespace genesis