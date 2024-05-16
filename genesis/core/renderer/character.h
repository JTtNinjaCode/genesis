#include <glm/glm.hpp>
namespace genesis {
struct Character {
  float x;
  float y;
  float width;
  float height;
  float bearing_x;
  glm::vec3 color;
  char c;
};
}  // namespace genesis