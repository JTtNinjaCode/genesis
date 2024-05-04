#pragma once
#include "core/renderer/camera/camera_3d_interface.h"
#include "core/renderer/vertex_array.h"
#include "shader.h"
namespace genesis {
// X-> Draw YZ Plane
// Y-> Draw XZ Plane
// Z-> Draw XY Plane
enum class GridMode { X = 1, Y = 2, Z = 3 };
class Grid {
 public:
  static Grid& GetInstance();
  Shader& GetShader();
  VertexArray& GetVertexArray();
  GridMode GetGridMode() const;
  void SetGridMode(GridMode mode);
  float GetOpacity() const;
  void SetOpacity(float opacity);
  void Disable();

 private:
  Grid();
  GridMode mode_ = GridMode::Y;
  float opacity_ = 0.3f;
  std::shared_ptr<Shader> shader_;
  std::shared_ptr<VertexArray> vertex_array_;
};
}  // namespace genesis