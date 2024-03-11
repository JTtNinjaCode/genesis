#pragma once
namespace genesis {
enum class MathDataType { kFloat3, kFloat4, kMat4, kMat3 };
class Math {
 public:
  static unsigned int GetMathDataTypeSize(MathDataType math_data_type);
  static unsigned int GetMathDataTypeComponentCount(
      MathDataType math_data_type);
};

}  // namespace genesis