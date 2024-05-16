#include "transform.h"

#include <rttr/registration.h>

#include "core/component/game_object.h"

using namespace rttr;
namespace genesis {
RTTR_REGISTRATION {
  registration::class_<genesis::Transform>("Transform")
      .constructor<GameObject*>()(rttr::policy::ctor::as_std_shared_ptr);
}
}  // namespace genesis