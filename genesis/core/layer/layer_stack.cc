#include "core/layer/layer_stack.h"
namespace genesis {

LayerStack::LayerStack() : overlayer_insert_index(0) {}

void LayerStack::PushLayer(std::unique_ptr<Layer>&& layer) {
  layers_.emplace(layers_.begin() + overlayer_insert_index, std::move(layer));
  overlayer_insert_index++;
}

void LayerStack::PopLayer(std::unique_ptr<Layer>&& layer) {
  auto iter = std::find(layers_.begin(), layers_.begin() + overlayer_insert_index, std::move(layer));
  if (iter != layers_.begin() + overlayer_insert_index) {
    layers_.erase(iter);
    overlayer_insert_index--;
  }
}

void LayerStack::PushOverLayer(std::unique_ptr<Layer>&& over_layer) { layers_.emplace_back(std::move(over_layer)); }

void LayerStack::PopOverLayer(std::unique_ptr<Layer>&& over_layer) {
  auto iter = std::find(layers_.begin() + overlayer_insert_index, layers_.end(), std::move(over_layer));
  if (iter != layers_.end()) {
    layers_.erase(iter);
  }
}
}  // namespace genesis