#include "font.h"

#include <filesystem>
#include <fstream>

#include "core/log/log.h"
#include "core/renderer/texture.h"
namespace genesis {

FT_Library Font::library = nullptr;
std::shared_ptr<VertexArray> Font::vao_;
std::shared_ptr<Shader> Font::shader_;
std::shared_ptr<Texture2D> Font::texture2d_;
std::unordered_map<std::string, FT_Face> Font::faces_;

void Font::Init() {
  CORE_LOG_TRACE("Start to init Font's Context");
  auto error = FT_Init_FreeType(&library);
  if (error) {
    CORE_ASSERT(false, "Fail to load FreeType library.");
  }
  shader_ = Shader::Create("./assets/shaders/font.vert", "./assets/shaders/font.frag");
  // clang-format off
  float vertices_data[24] = {
                            -1.0f, 1.0f, 0.0f, 0.0f,
                            1.0f, 1.0f, 1.0f, 0.0f,
                            1.0f, -1.0f, 1.0f, 1.0f,
                            -1.0f, -1.0f, 0.0f, 1.0f
                            };
  // clang-format on
  unsigned int indices[6] = {0, 1, 2, 2, 3, 0};
  auto vbo = VertexBuffer::Create(vertices_data, sizeof(vertices_data));
  auto ibo = IndexBuffer::Create(indices, sizeof(indices));
  vao_ = VertexArray::Create({MathDataType::kFloat2, MathDataType::kFloat2});
  vao_->SetIndexBuffer(ibo);
  vao_->SetVertexBuffer(vbo);
  CORE_LOG_TRACE("Finish to init Font's Context");
}

void Font::Uninit() {
  for (auto& face : faces_) {
    FT_Done_Face(face.second);
  }
  FT_Done_FreeType(library);
}

Shader& Font::GetShader() { return *shader_; }

VertexArray& Font::GetVertexArray() { return *vao_; }
Texture2D& Font::GetTexture() { return *texture2d_; }

void Font::LoadFont(const std::filesystem::path& file_path, const std::string& font_name, unsigned short font_size) {
  FT_Face face;
  auto error = FT_New_Face(library, file_path.string().c_str(), 0, &face);
  if (error) {
    CORE_ASSERT(false, "Fail to load FreeType library.");
  }
  FT_Set_Pixel_Sizes(face, 0, 40);
  if (FT_Load_Char(face, 'X', FT_LOAD_RENDER)) {
    CORE_LOG_TRACE("Failed to load Glyph.");
  }
  FT_Select_Charmap(face, FT_ENCODING_UNICODE);

  FT_GlyphSlot slot = face->glyph;
  FT_Render_Glyph(slot, FT_RENDER_MODE_NORMAL);
  FT_Set_Char_Size(face, 0, 16 * 64, 300, 300);
  FT_Load_Glyph(face, FT_Get_Char_Index(face, 'A'), FT_LOAD_DEFAULT);
  FT_Render_Glyph(slot, FT_RENDER_MODE_NORMAL);
  FT_Bitmap bitmap = slot->bitmap;
  FT_Pos advance = slot->advance.x;
  texture2d_ = Texture2D::Create(bitmap.buffer, TextureFormat::kR, bitmap.width, bitmap.rows, TextureType::kDiffuse);
  faces_[font_name] = face;
  CORE_LOG_TRACE("Load Font:{}", file_path.string().c_str());
}

}  // namespace genesis