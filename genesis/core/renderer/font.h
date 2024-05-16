#pragma once
#include <ft2build.h>
#include FT_FREETYPE_H
#include <unordered_map>

#include "core/renderer/shader.h"
#include "core/renderer/texture.h"
#include "core/renderer/vertex_array.h"
namespace genesis {
class Font {
 public:
  static void Init();
  static void Uninit();
  static Shader& GetShader();
  static VertexArray& GetVertexArray();
  static Texture2D& GetTexture();
  static void LoadFont(const std::filesystem::path& file_path, const std::string& font_name,
                                             unsigned short font_size);
  // static void UseFont(const std::string& font_name);

 private:
  static FT_Library library;
  static std::shared_ptr<VertexArray> vao_;
  static std::shared_ptr<Shader> shader_;
  static std::shared_ptr<Texture2D> texture2d_;
  static std::unordered_map<std::string, FT_Face> faces_;
};
}  // namespace genesis