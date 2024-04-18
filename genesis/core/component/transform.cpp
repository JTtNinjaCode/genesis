#include "transform.h"
#include <rttr/registration.h>

using namespace rttr;
RTTR_REGISTRATION {
  registration::class_<genesis::Transform>("Transform").constructor<>()(rttr::policy::ctor::as_std_shared_ptr);
}

namespace genesis {
genesis::Transform::Transform() : position_(0.0f), rotation_(0.0f), scale_(0.0f) {}
}  // namespace genesis