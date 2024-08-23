#include "grid.h"

#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

#include "core/log/log.h"
#include "vertex_array.h"
namespace genesis {
Grid& Grid::GetInstance() {
  static Grid grid;
  return grid;
}

Shader& Grid::GetShader() { return *shader_; }

VertexArray& Grid::GetVertexArray() { return *vertex_array_; }

GridMode Grid::GetGridMode() const { return mode_; }

void Grid::SetGridMode(GridMode mode) { mode_ = mode; }

float Grid::GetOpacity() const { return opacity_; }

void Grid::SetOpacity(float opacity) { opacity_ = opacity; }

void Grid::Disable() { opacity_ = 0.0f; }

Grid::Grid() : shader_(Shader::Create("./assets/shaders/inf.vert", "./assets/shaders/inf.frag")) {
  static float vertices_data[8] = {1.0f, 1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, -1.0f};
  static unsigned int vertices_index[6] = {0, 1, 2, 2, 3, 0};
  static auto vbo = VertexBuffer::Create(vertices_data, sizeof(vertices_data));
  static auto ebo = IndexBuffer::Create(vertices_index, sizeof(vertices_index));
  vertex_array_ = VertexArray::Create({{MathDataType::kFloat2, 0}});
  vertex_array_->SetVertexBuffer(vbo);
  vertex_array_->SetIndexBuffer(ebo);
}
}  // namespace genesis