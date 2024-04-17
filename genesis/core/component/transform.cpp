#include "transform.h"

namespace genesis {
genesis::Transform::Transform() : position_(0.0f), rotation_(0.0f), scale_(0.0f) {}
using namespace rttr;
RTTR_REGISTRATION { registration::class_<Transform>("Transform").constructor<>()(rttr::policy::ctor::as_raw_ptr); }
}  // namespace genesis