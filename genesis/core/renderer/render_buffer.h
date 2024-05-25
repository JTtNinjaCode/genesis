#pragma once
#include <memory>
namespace genesis {
class RenderBuffer {
 public:
  static std::shared_ptr<RenderBuffer> Create(unsigned int width, unsigned int height);  // TODO: add type

  virtual ~RenderBuffer() {}
  virtual void Bind() const = 0;
  virtual void* GetId() const = 0;
};

}  // namespace genesis