#include "perspective_camera.h"

#include <glm/gtc/matrix_transform.hpp>
namespace genesis {
PerspectiveCamera::PerspectiveCamera(float field_of_view, float ratio, float near, float far, glm::vec3 position,
                                     glm::vec3 target)
    : position_(position),
      direction_(glm::normalize(target - position)),
      field_of_view_(field_of_view),
      ratio_(ratio),
      near_(near),
      far_(far) {}
}  // namespace genesis