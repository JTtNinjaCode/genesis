#include "buffer_layout.h"

#include "core/log.h"
namespace genesis {
std::vector<BufferLayoutAttribute>::const_iterator BufferLayout::begin()
    const {
  return layout_.cbegin();
}

std::vector<BufferLayoutAttribute>::const_iterator BufferLayout::end() const {
  return layout_.cend();
}
}  // namespace genesis