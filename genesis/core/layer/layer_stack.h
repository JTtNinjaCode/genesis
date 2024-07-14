#pragma once

#include <vector>

#include "core/core.h"
#include "core/layer/layer.h"

namespace genesis {
class DLL_API LayerManager {
  using LayerContainer = std::vector<std::unique_ptr<Layer>>;

 public:
  LayerManager();
  static void SetBeginRoundCallback(const std::function<void()> &begin_callback);
  static void SetEndRoundCallback(const std::function<void()> &end_callback);
  static void RunBeginCallback();
  static void RunEndCallback();

  void PushLayer(std::unique_ptr<Layer> &&layer);
  void PopLayer(std::unique_ptr<Layer> &&layer);
  void PushOverLayer(std::unique_ptr<Layer> &&layer);
  void PopOverLayer(std::unique_ptr<Layer> &&layer);

  LayerContainer::iterator begin() { return layers_.begin(); }
  LayerContainer::iterator end() { return layers_.end(); }
  LayerContainer::reverse_iterator rbegin() { return layers_.rbegin(); }
  LayerContainer::reverse_iterator rend() { return layers_.rend(); }

 private:
  static std::function<void()> begin_callback_;
  static std::function<void()> end_callback_;
  LayerContainer layers_;
  unsigned int overlayer_insert_index;
};
}  // namespace genesis