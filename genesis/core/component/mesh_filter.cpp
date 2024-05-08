#include "mesh_filter.h"

#include <rttr/registration.h>

#include "core/component/game_object.h"
namespace genesis {
using namespace rttr;
RTTR_REGISTRATION {
  registration::class_<MeshFilter>("Mesh Filter").constructor<GameObject *>()(rttr::policy::ctor::as_std_shared_ptr);
}
}  // namespace genesis