#include "light.h"

#include <rttr/registration.h>
namespace genesis {
using namespace rttr;
RTTR_REGISTRATION {
  registration::class_<Light>("Light").constructor<>()(rttr::policy::ctor::as_std_shared_ptr);
}
}  // namespace genesis