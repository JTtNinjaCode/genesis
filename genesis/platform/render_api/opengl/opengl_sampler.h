#pragma once
#include <string>

#include "core/renderer/sampler.h"
namespace genesis {
enum class SamplerFunc {
  kNearest,
  kLinear,
  kNearestMipmapNearest,
  kLinearMipmapNearest,
  kNearestMipmapLinear,
  kLinearMipmapLinear
};
// TODO: kClmapToBorder need to set constant color of out of border
enum class WrapFunc { kRepeat, kMirroredRepeat, kClampToEdge, kClampToBorder, kMirrorClmapToEdge };
class OpenGLSampler : public Sampler {
 public:
  OpenGLSampler();
  virtual ~OpenGLSampler();
  void Bind(unsigned int slot) const override;
  const void* GetId() const override;
  void SetSamplerFunc(unsigned int slot) const override;
  void SetWrapFunc(unsigned int slot) const override;

 private:
  unsigned int id_ = 0;
};

}  // namespace genesis