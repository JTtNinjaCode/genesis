#pragma once

#include <vector>

#include "core/core.h"
#include "core/layer/layer.h"

namespace genesis {
class DLL_API LayerStack {
  using LayerContainer = std::vector<std::unique_ptr<Layer>>;

 public:
  LayerStack();

  void PushLayer(std::unique_ptr<Layer> &&layer);
  void PopLayer(std::unique_ptr<Layer> &&layer);
  void PushOverLayer(std::unique_ptr<Layer> &&layer);
  void PopOverLayer(std::unique_ptr<Layer> &&layer);

  LayerContainer::iterator begin() { return layers_.begin(); }
  LayerContainer::iterator end() { return layers_.end(); }
  LayerContainer::reverse_iterator rbegin() { return layers_.rbegin(); }
  LayerContainer::reverse_iterator rend() { return layers_.rend(); }

 private:
  LayerContainer layers_;
  unsigned int overlayer_insert_index;
};
}  // namespace genesis