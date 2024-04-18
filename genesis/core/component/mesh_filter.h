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

using namespace rttr;
RTTR_REGISTRATION {
  registration::class_<MeshFilter>("Mesh Filter").constructor<>()(rttr::policy::ctor::as_std_shared_ptr);
}
}  // namespace genesis