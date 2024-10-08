#pragma once
#include <filesystem>

#include "core/component/game_object.h"
#include "core/renderer/model.h"
namespace genesis {
class MeshFilter : public Component {
 public:
  MeshFilter(GameObject* game_object) : Component(game_object) {}
  const Model& GetModel() const { return model_; }
  void SetModel(const std::filesystem::path& path, const VerticesLayout layout) { model_.LoadModel(path, layout); }

 private:
  Model model_;
};
}  // namespace genesis