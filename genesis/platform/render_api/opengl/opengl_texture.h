#pragma once
#include <glad/glad.h>

#include <filesystem>
#include <vector>

#include "core/renderer/texture.h"

namespace genesis {

__pragma(pack(push, 1))  // Packed Format
    struct OpenGLCompressedFileHeaderFormat {
  // TODO: fix endian problem
  OpenGLCompressedFileHeaderFormat(uint16_t init_width, uint16_t init_height, uint32_t init_compress_size,
                                   uint32_t init_compress_format, uint8_t init_channels)
      : height(init_height),
        width(init_width),
        compress_size(init_compress_size),
        compress_format(init_compress_format),
        channels(init_channels){};
  const char header_name[64] = "genesis:opengl compressed texture";
  const uint16_t height;
  const uint16_t width;
  const uint32_t compress_size;
  const uint32_t compress_format;
  const uint8_t channels;
};
__pragma(pack(pop));

class OpenGLTexture2D : public Texture2D {
 public:
  OpenGLTexture2D(const std::filesystem::path& path);
  OpenGLTexture2D(unsigned char* data, TextureFormat data_format, unsigned int width, unsigned int height);
  ~OpenGLTexture2D();

  int GetWidth() const override;
  int GetHeight() const override;
  void Bind(unsigned int slot) const override;
  void UnBind() const override;
  const void* GetID() const override;

 private:
  unsigned char* LoadOriginFile(const std::filesystem::path& path);
  void CompressAndUseOriginFile(unsigned char* image_data);
  void UseCompressFile(const std::filesystem::path& path);
  void SaveCompressedFile(const std::filesystem::path& save_path);

  GLuint id_ = 0;
  int width_ = 0;
  int height_ = 0;
  int channels_ = 0;
};

class OpenGLTexture3D : public Texture3D {
 public:
  OpenGLTexture3D(const std::vector<std::filesystem::path>& faces_path);
  ~OpenGLTexture3D();

  int GetWidth() const override;
  int GetHeight() const override;
  void Bind(unsigned int slot) const override;
  void UnBind() const override;
  const void* GetID() const override;

 private:
  GLuint id_ = 0;
  int width_[6] = {};
  int height_[6] = {};
  int channels_[6] = {};
};

}  // namespace genesis