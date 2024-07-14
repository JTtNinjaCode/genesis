#pragma once
#include <memory>

namespace genesis {
class Sampler {
 public:
  static std::shared_ptr<Sampler> Create();

  virtual void Bind(unsigned int slot) const = 0;
  virtual void SetSamplerFunc(unsigned int slot) const = 0;
  virtual void SetWrapFunc(unsigned int slot) const = 0;
  virtual const void* GetId() const = 0;
};

}  // namespace genesis