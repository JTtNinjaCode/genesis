#include "core/layer_stack.h"
namespace genesis {

LayerStack::LayerStack() : overlayer_insert_index(0) {}


void LayerStack::PushLayer(std::shared_ptr<Layer> layer) {
  layers_.emplace(layers_.begin() + overlayer_insert_index, layer);
  overlayer_insert_index++;
}

void LayerStack::PopLayer(std::shared_ptr<Layer> layer) {
  auto iter = std::find(layers_.begin(),
                        layers_.begin() + overlayer_insert_index, layer);
  if (iter != layers_.begin() + overlayer_insert_index) {
    layers_.erase(iter);
    overlayer_insert_index--;
  }
}

void LayerStack::PushOverLayer(std::shared_ptr<Layer> over_layer) {
  layers_.emplace_back(over_layer);
}

void LayerStack::PopOverLayer(std::shared_ptr<Layer> over_layer) {
  auto iter = std::find(layers_.begin() + overlayer_insert_index, layers_.end(),
                        over_layer);
  if (iter != layers_.end()) {
    layers_.erase(iter);
  }
}
}  // namespace genesis