
#include "skybox.h"

#include "core/log/log.h"
namespace genesis {
std::shared_ptr<VertexBuffer> Skybox::vbo_;
std::shared_ptr<VertexArray> Skybox::vao_;
std::shared_ptr<IndexBuffer> Skybox::ibo_;
std::shared_ptr<Shader> Skybox::shader_;

void Skybox::Init() {
  CORE_LOG_TRACE("Start to init Skybox's Context");
  // clang-format off
  float vertices_data[] = {
		-1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        -1.0f,  1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f,  1.0f
  };
  // clang-format on

  vbo_ = VertexBuffer::Create(vertices_data, sizeof(vertices_data));
  BufferLayout layout({{MathDataType::kFloat3, 0}});
  vao_ = VertexArray::Create(layout);
  vao_->SetVertexBuffer(vbo_);
  CORE_LOG_TRACE("Finish to init Skybox's Context");
}
Skybox::Skybox(const std::vector<std::filesystem::path>& faces_path) { texture_ = Texture3D::Create(faces_path); }
void* Skybox::GetTextureID() const { return (void*)(texture_->GetID()); }
const VertexArray& Skybox::GetVertexArray() const { return *vao_; }
void Skybox::Bind() const { texture_->Bind(0); }
}  // namespace genesis
