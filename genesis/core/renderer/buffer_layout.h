#pragma once
#include <core/math_struct.h>

#include <initializer_list>
#include <vector>

namespace genesis {
struct BufferLayoutAttribute {
  BufferLayoutAttribute(MathDataType math_data_type)
      : type(math_data_type),
        size(Math::GetMathDataTypeSize(type)),
        count(Math::GetMathDataTypeComponentCount(type)) {}
  MathDataType type;
  size_t size;
  unsigned int count;
};

class BufferLayout {
 public:
  BufferLayout(const std::initializer_list<BufferLayoutAttribute>& init_list)
      : layout_(init_list) {
    // calculate total stride
    for (const auto& element : layout_) {
      total_stride_ += element.size;
    }
  }
  std::vector<BufferLayoutAttribute>::const_iterator begin() const;
  std::vector<BufferLayoutAttribute>::const_iterator end() const;
  const std::vector<BufferLayoutAttribute>& GetLayout() const {
    return layout_;
  }
  size_t GetTotalStride() const { return total_stride_; }

 private:
  std::vector<BufferLayoutAttribute> layout_;
  size_t total_stride_ = 0;
};

}  // namespace genesis