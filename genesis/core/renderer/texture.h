#pragma once
#include <filesystem>
#include <memory>
#include <string>
namespace genesis {
enum class TextureType { Specular, Diffuse };

class Texture {
 public:
  virtual ~Texture() = default;

  virtual int GetWidth() const = 0;
  virtual int GetHeight() const = 0;
  virtual void Bind(unsigned int slot) const = 0;
  virtual void UnBind() const = 0;
};

class Texture2D : public Texture {
 public:
  static std::shared_ptr<Texture2D> Create(
      const std::filesystem::path& path,
      TextureType texture_type = TextureType::Diffuse);
  static std::shared_ptr<Texture2D> Create(
      unsigned char* data, unsigned int channels, unsigned int width,
      unsigned int height, TextureType texture_type = TextureType::Diffuse);
  TextureType GetTextureType() const { return texture_type_; }

 private:
  TextureType texture_type_ = TextureType::Diffuse;
};
}  // namespace genesis