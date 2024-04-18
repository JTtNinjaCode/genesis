#include "mesh_filter.h"
namespace genesis {
using namespace rttr;
RTTR_REGISTRATION {
  registration::class_<MeshFilter>("Mesh Filter").constructor<>()(rttr::policy::ctor::as_std_shared_ptr);
}
}  // namespace genesis