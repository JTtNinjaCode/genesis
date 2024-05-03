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
void Grid::OnUpdate(const Camera3DInterface& camera) {
  using namespace glm;
  mat4 inv_projection = inverse(camera.GetProjection());
  mat4 inv_view = inverse(camera.GetView());
  auto camera_position = camera.GetPosition();

  constexpr int vertices_count = 4;
  static vec2 vertices_data[vertices_count] = {{0.95f, 0.95f}, {-0.95f, 0.95f}, {-0.95f, -0.95f}, {0.95f, -0.95f}};

  std::vector<vec3> rays;
  for (size_t i = 0; i < vertices_count; i++) {
    vec4 camera_space_ray = inv_projection * vec4(vec2(vertices_data[i]), -1.0f, 1.0f);
    camera_space_ray = vec4(vec2(camera_space_ray), -1.0, 0.0);
    vec3 ray = vec3(inv_view * camera_space_ray);
    ray = normalize(ray);

    float t = -(dot(vec3(0, 1, 0), camera_position)) / dot(vec3(0, 1, 0), ray);
    vec3 intersection = camera_position;
    if (t > 0) {
      intersection += t * ray;
    }
    rays.push_back(intersection);
  }
  CORE_LOG_TRACE("{0}", glm::to_string(rays[0]));
  vertex_array_->GetVertexBuffer().SubData(rays.data(), sizeof(vec3) * rays.size());
}
Shader& Grid::GetShader() { return *shader_; }
VertexArray& Grid::GetVertexArray() { return *vertex_array_; }

GridMode Grid::GetGridMode() const { return mode_; }

void Grid::SetGridMode(GridMode mode) { mode_ = mode; }

float Grid::GetOpacity() const { return opacity_; }

void Grid::SetOpacity(float opacity) { opacity_ = opacity; }

bool Grid::GetEnable() const { return enable_; }

void Grid::SetEnable(bool enable) { enable_ = enable; }

Grid::Grid() : shader_(Shader::Create("./assets/shaders/inf.vert", "./assets/shaders/inf.frag")) {
  static unsigned int index_data[6] = {0, 1, 2, 2, 3, 0};
  static auto vbo = VertexBuffer::Create(nullptr, sizeof(glm::vec3) * 4);
  static auto ebo = IndexBuffer::Create(index_data, sizeof(index_data));
  vertex_array_ = VertexArray::Create({MathDataType::kFloat3});
  vertex_array_->SetVertexBuffer(vbo);
  vertex_array_->SetIndexBuffer(ebo);
}
}  // namespace genesis