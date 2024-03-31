#pragma once
#include <memory>
#include <string>
#include <filesystem>
namespace genesis {
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
  static std::shared_ptr<Texture2D> Create(const std::filesystem::path& path);
  static std::shared_ptr<Texture2D> Create(unsigned char* data,
                                           unsigned int channels,
                                           unsigned int width,
                                           unsigned int height);
};
}  // namespace genesis