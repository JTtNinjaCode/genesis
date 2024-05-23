#include "opengl_texture.h"
#define STB_IMAGE_IMPLEMENTATION  // dont delete this, see stb_image.h
#include <stb_image.h>

#include <fstream>

#include "core/log/log.h"
namespace genesis {
OpenGLTexture2D::OpenGLTexture2D(const std::filesystem::path& path) {
  auto compressed_path_name = path.string() + ".cpt";
  if (std::filesystem::exists(compressed_path_name)) {
    UseCompressFile(compressed_path_name);
  } else {
    unsigned char* image_data = LoadOriginFile(path);
    CompressAndUseOriginFile(image_data);
    stbi_image_free(image_data);
    SaveCompressedFile(compressed_path_name);
  }
}

OpenGLTexture2D::OpenGLTexture2D(unsigned char* data, unsigned int channels, unsigned int width, unsigned int height)
    : width_(width), height_(height) {
  glCreateTextures(GL_TEXTURE_2D, 1, &id_);
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  GLenum internal_format = 0;
  if (channels == 1) {
    internal_format = GL_R8;
  } else if (channels == 3) {
    internal_format = GL_RGB8;
  } else if (channels == 4) {
    internal_format = GL_RGBA8;
  }

  CORE_ASSERT(channels == 1 || channels == 3 || channels || 4, "texture format not support.");

  glTextureStorage2D(id_, 1, internal_format, width_,
                     height_);  // allocate memory

  glTextureParameteri(id_, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTextureParameteri(id_, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  GLenum data_format = GL_RGB;
  if (channels == 1) {
    data_format = GL_RED;
  } else if (channels == 3) {
    data_format = GL_RGB;
  } else if (channels == 4) {
    data_format = GL_RGBA;
  }
  glTextureSubImage2D(id_, 0, 0, 0, width_, height_, data_format, GL_UNSIGNED_BYTE,
                      data);  // transfer data to allocated memory
}

OpenGLTexture2D::~OpenGLTexture2D() { glDeleteTextures(1, &id_); }

int OpenGLTexture2D::GetWidth() const { return width_; }

int OpenGLTexture2D::GetHeight() const { return height_; }

void OpenGLTexture2D::Bind(unsigned int slot) const { glBindTextureUnit(slot, id_); }

void OpenGLTexture2D::UnBind() const { /*glBindTexture(GL_TEXTURE_2D, 0);*/
}

const void* OpenGLTexture2D::GetID() const { return (void*)id_; }

unsigned char* OpenGLTexture2D::LoadOriginFile(const std::filesystem::path& path) {
  using namespace std;
  if (!filesystem::exists(path)) {
    CORE_ASSERT(false, "{0} not exists.", path.string());
  }
  CORE_LOG_TRACE("load texture {0}", path.string());

  stbi_set_flip_vertically_on_load(false);
  stbi_uc* image_data = stbi_load(path.string().c_str(), &width_, &height_, &channels_, 0);
  CORE_ASSERT(image_data, "STB fail to load image.");
  return image_data;
}

void OpenGLTexture2D::CompressAndUseOriginFile(unsigned char* image_data) {
  glCreateTextures(GL_TEXTURE_2D, 1, &id_);
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  GLenum gpu_format = 0;
  GLenum origin_format = 0;
  if (channels_ == 3) {
    gpu_format = GL_COMPRESSED_RGB;
    origin_format = GL_RGB;
  } else if (channels_ == 4) {
    gpu_format = GL_COMPRESSED_RGBA;
    origin_format = GL_RGBA;
  }

  CORE_ASSERT(channels_ == 3 || channels_ == 4, "texture format not support.");

  glBindTexture(GL_TEXTURE_2D, id_);
  glTexImage2D(GL_TEXTURE_2D, 0, gpu_format, width_, height_, 0, origin_format, GL_UNSIGNED_BYTE, image_data);

  glTextureParameteri(id_, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTextureParameteri(id_, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTextureParameteri(id_, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTextureParameteri(id_, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

void OpenGLTexture2D::UseCompressFile(const std::filesystem::path& path) {
  std::ifstream input_file_stream(path, std::ios::in | std::ios::binary);
  if (!input_file_stream) {
    CORE_LOG_ERROR("Failed to read file:{0}", path.string());
    return;
  }

  char read_buffer[sizeof(OpenGLCompressedFileHeaderFormat)];
  input_file_stream.read(read_buffer, sizeof(OpenGLCompressedFileHeaderFormat));
  OpenGLCompressedFileHeaderFormat& header_format = *reinterpret_cast<OpenGLCompressedFileHeaderFormat*>(read_buffer);
  char* image_data = (char*)malloc(header_format.compress_size);
  input_file_stream.read(image_data, header_format.compress_size);
  height_ = header_format.height;
  width_ = header_format.width;
  channels_ = header_format.channels;

  glCreateTextures(GL_TEXTURE_2D, 1, &id_);
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  CORE_ASSERT(channels_ == 3 || channels_ == 4, "texture format not support.");
  glBindTexture(GL_TEXTURE_2D, id_);
  glCompressedTexImage2D(GL_TEXTURE_2D, 0, header_format.compress_format, width_, height_, 0,
                         header_format.compress_size, image_data);

  glTextureParameteri(id_, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTextureParameteri(id_, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTextureParameteri(id_, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTextureParameteri(id_, GL_TEXTURE_WRAP_T, GL_REPEAT);

  free(image_data);
}

void OpenGLTexture2D::SaveCompressedFile(const std::filesystem::path& save_path) {
  GLint compress_success = 0;
  glGetTextureLevelParameteriv(id_, 0, GL_TEXTURE_COMPRESSED, &compress_success);
  GLint compress_size = 0;
  glGetTextureLevelParameteriv(id_, 0, GL_TEXTURE_COMPRESSED_IMAGE_SIZE, &compress_size);
  GLint compress_format = 0;
  glGetTextureLevelParameteriv(id_, 0, GL_TEXTURE_INTERNAL_FORMAT, &compress_format);
  void* img = malloc(compress_size);
  glGetCompressedTextureImage(id_, 0, compress_size, img);

  std::ofstream output_file_stream(save_path, std::ios::out | std::ios::binary);
  OpenGLCompressedFileHeaderFormat header_format(width_, height_, compress_size, compress_format, channels_);
  output_file_stream.write((char*)&header_format, sizeof(OpenGLCompressedFileHeaderFormat));
  output_file_stream.write((char*)img, compress_size);
  output_file_stream.close();
  free(img);
}

OpenGLTexture3D::OpenGLTexture3D(const std::vector<std::filesystem::path>& faces_path) {
  stbi_set_flip_vertically_on_load(false);
  glCreateTextures(GL_TEXTURE_CUBE_MAP, 1, &id_);
  for (unsigned int i = 0; i < faces_path.size(); i++) {
    unsigned char* data = stbi_load(faces_path[i].string().c_str(), &width_[i], &height_[i], &channels_[i], 0);
    if (data) {
      glBindTexture(GL_TEXTURE_CUBE_MAP, id_);
      glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width_[i], height_[i], 0, GL_RGB, GL_UNSIGNED_BYTE,
                   data);
      stbi_image_free(data);
    } else {
      CORE_LOG_TRACE("Cubemap texture failed to load at path:{0}", faces_path[i].string().c_str());
      stbi_image_free(data);
    }
  }

  glTextureParameteri(id_, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTextureParameteri(id_, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTextureParameteri(id_, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTextureParameteri(id_, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTextureParameteri(id_, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}

OpenGLTexture3D::~OpenGLTexture3D() { glDeleteTextures(1, &id_); }

int OpenGLTexture3D::GetWidth() const {
  return 0;  // TODO fix OpenGLTexture3D width
}

int OpenGLTexture3D::GetHeight() const {
  return 0;  // TODO fix OpenGLTexture3D width
}

void OpenGLTexture3D::Bind(unsigned int slot) const { glBindTexture(GL_TEXTURE_CUBE_MAP, id_); }

void OpenGLTexture3D::UnBind() const {}

const void* OpenGLTexture3D::GetID() const { return (void*)id_; }

}  // namespace genesis