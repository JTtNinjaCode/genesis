#pragma once
#include <filesystem>

#include "core/renderer/texture.h"
namespace genesis {
class OpenGLTexture2D : public Texture2D {
 public:
  OpenGLTexture2D(const std::filesystem::path &path);
  OpenGLTexture2D(unsigned char *data, unsigned int channels,
                  unsigned int width, unsigned int height);
  ~OpenGLTexture2D();
  int GetWidth() const override;
  int GetHeight() const override;
  void Bind(unsigned int slot) const override;
  void UnBind() const override;

 private:
  unsigned int id_ = 0;
  int width_ = 0;
  int height_ = 0;
};

}  // namespace genesis