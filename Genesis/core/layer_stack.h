#pragma once

#include <vector>

#include "core/Layer.h"
#include "core/core.h"

namespace Genesis {
class DLL_API LayerStack {
  using LayerContainer = std::vector<Layer*>;

 public:
  LayerStack();
  ~LayerStack();

  void PushLayer(Layer* layer);
  void PopLayer(Layer* over_layer);
  void PushOverLayer(Layer* layer);
  void PopOverLayer(Layer* over_layer);

  LayerContainer::iterator begin() { return layers_.begin(); }
  LayerContainer::iterator end() { return layers_.end(); }
  LayerContainer::reverse_iterator rbegin() { return layers_.rbegin(); }
  LayerContainer::reverse_iterator rend() { return layers_.rend(); }

 private:
  LayerContainer layers_;
  unsigned int overlayer_insert_index;
};
}  // namespace Genesis