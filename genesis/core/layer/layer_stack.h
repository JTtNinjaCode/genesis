#pragma once

#include <vector>

#include "core/layer/layer.h"
#include "core/core.h"

namespace genesis {
class DLL_API LayerStack {
  using LayerContainer = std::vector<std::shared_ptr<Layer>>;

 public:
  LayerStack();

  void PushLayer(std::shared_ptr<Layer> layer);
  void PopLayer(std::shared_ptr<Layer> over_layer);
  void PushOverLayer(std::shared_ptr<Layer> layer);
  void PopOverLayer(std::shared_ptr<Layer> over_layer);

  LayerContainer::iterator begin() { return layers_.begin(); }
  LayerContainer::iterator end() { return layers_.end(); }
  LayerContainer::reverse_iterator rbegin() { return layers_.rbegin(); }
  LayerContainer::reverse_iterator rend() { return layers_.rend(); }

 private:
  LayerContainer layers_;
  unsigned int overlayer_insert_index;
};
}  // namespace genesis