#include "opengl_texture.h"

#include <glad/glad.h>
#include <stb_image.h>

#include "core/log/log.h"
namespace genesis {
OpenGLTexture2D::OpenGLTexture2D(const std::filesystem::path& path) {
  using namespace std;
  if (!filesystem::exists(path)) {
    CORE_ASSERT(false, "{0} not exists.", path.string());
  }

  auto compressed_path_name = path;
  compressed_path_name += ".cpt";

  CORE_LOG_TRACE(compressed_path_name.string());

  // origin file exists, but compress version not exists
  //if (!filesystem::exists(compressed_path_name)) {
  //  OpenGLCompressor::compress();
  //}

  //CompressTextureFormat compress_texture = LoadCompressTexture();

  //glCreateTextures(GL_TEXTURE_2D, 1, &id_);
  //glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  //GLenum internal_format = 0;
  //if (compress_texture.channels == 3) {
  //  internal_format = GL_COMPRESSED_RGB;
  //} else if (compress_texture.channels == 4) {
  //  internal_format = GL_COMPRESSED_RGBA;
  //}

  //CORE_ASSERT(compress_texture.channels == 3 || compress_texture.channels || 4,
  //            "texture format not support.");

  //glTextureStorage2D(id_, 1, internal_format, width_,
  //                   height_);  // allocate memory

  //glTextureParameteri(id_, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  //glTextureParameteri(id_, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  //GLenum data_format;
  //if (compress_texture.channels == 3) {
  //  data_format = GL_COMPRESSED_RGB;
  //} else if (compress_texture.channels == 4) {
  //  data_format = GL_COMPRESSED_RGBA;
  //}
  //glTextureSubImage2D(
  //    id_, 0, 0, 0, width_, height_, data_format, GL_UNSIGNED_BYTE,
  //    compress_texture.data);  // transfer data to allocated memory

  //
  int channels = 0;
  stbi_uc* image_data =
      stbi_load(path.string().c_str(), &width_, &height_, &channels, 0);
  CORE_ASSERT(image_data, "stb fail to load image");

  glCreateTextures(GL_TEXTURE_2D, 1, &id_);
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  GLenum internal_format = 0;
  if (channels == 3) {
    internal_format = GL_RGB8;
  } else if (channels == 4) {
    internal_format = GL_RGBA8;
  }

  CORE_ASSERT(channels == 3 || channels || 4, "texture format not support.");

  glTextureStorage2D(id_, 1, internal_format, width_,
                     height_);  // allocate memory

  glTextureParameteri(id_, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTextureParameteri(id_, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  GLenum data_format;
  if (channels == 3) {
    data_format = GL_RGB;
  } else if (channels == 4) {
    data_format = GL_RGBA;
  }
  glTextureSubImage2D(id_, 0, 0, 0, width_, height_, data_format,
                      GL_UNSIGNED_BYTE,
                      image_data);  // transfer data to allocated memory
  stbi_image_free(image_data);
}

OpenGLTexture2D::OpenGLTexture2D(unsigned char* data, unsigned int channels,
                                 unsigned int width, unsigned int height)
    : width_(width), height_(height) {
  glCreateTextures(GL_TEXTURE_2D, 1, &id_);
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  GLenum internal_format = 0;
  if (channels == 3) {
    internal_format = GL_RGB8;
  } else if (channels == 4) {
    internal_format = GL_RGBA8;
  }

  CORE_ASSERT(channels == 3 || channels || 4, "texture format not support.");

  glTextureStorage2D(id_, 1, internal_format, width_,
                     height_);  // allocate memory

  glTextureParameteri(id_, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTextureParameteri(id_, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  GLenum data_format;
  if (channels == 3) {
    data_format = GL_RGB;
  } else if (channels == 4) {
    data_format = GL_RGBA;
  }
  glTextureSubImage2D(id_, 0, 0, 0, width_, height_, data_format,
                      GL_UNSIGNED_BYTE,
                      data);  // transfer data to allocated memory
}

OpenGLTexture2D::~OpenGLTexture2D() { glDeleteTextures(1, &id_); }

int OpenGLTexture2D::GetWidth() const { return width_; }

int OpenGLTexture2D::GetHeight() const { return height_; }

void OpenGLTexture2D::Bind(unsigned int slot) const {
  glBindTextureUnit(slot, id_);
}

void OpenGLTexture2D::UnBind() const { /*glBindTexture(GL_TEXTURE_2D, 0);*/
}

}  // namespace genesis