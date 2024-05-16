#include "math_struct.h"

#include "core/log/log.h"
namespace genesis {
unsigned int Math::GetMathDataTypeSize(MathDataType math_data_type) {
  switch (math_data_type) {
    case MathDataType::kFloat2:
      return 4 * 2;
    case MathDataType::kFloat3:
      return 4 * 3;
    case MathDataType::kFloat4:
      return 4 * 4;
    case MathDataType::kMat3:
      return 4 * 3 * 3;
    case MathDataType::kMat4:
      return 4 * 4 * 4;
  }
  CORE_ASSERT(false, "Invalid Math Data Type.");
  return 0;
}

unsigned int Math::GetMathDataTypeComponentCount(MathDataType math_data_type) {
  switch (math_data_type) {
    case MathDataType::kFloat2:
      return 2;
    case MathDataType::kFloat3:
      return 3;
    case MathDataType::kFloat4:
      return 4;
    case MathDataType::kMat3:
      return 3 * 3;
    case MathDataType::kMat4:
      return 4 * 4;
  }
  CORE_ASSERT(false, "Invalid Math Data Type.");
  return 0;
}
}  // namespace genesis