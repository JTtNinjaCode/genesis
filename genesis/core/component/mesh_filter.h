#include <filesystem>

#include "core/renderer/model.h"
namespace genesis {
class MeshFilter : public Component {
 public:
  const Model& GetModel() const { return model_; }
  void SetModel(const std::filesystem::path& path) { model_.LoadModel(path); }

 private:
  Model model_;
};
}  // namespace genesis