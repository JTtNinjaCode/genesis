#include "core/layer/layer_stack.h"
namespace genesis {
std::function<void()> LayerManager::begin_callback_;
std::function<void()> LayerManager::end_callback_;

LayerManager::LayerManager() : overlayer_insert_index(0) {}

void LayerManager::SetBeginRoundCallback(const std::function<void()>& begin_callback) {
  begin_callback_ = begin_callback;
}

void LayerManager::SetEndRoundCallback(const std::function<void()>& end_callback) { end_callback_ = end_callback; }

void LayerManager::RunBeginCallback() {
  if (begin_callback_) begin_callback_();
}

void LayerManager::RunEndCallback() {
  if (end_callback_) end_callback_();
}

void LayerManager::PushLayer(std::unique_ptr<Layer>&& layer) {
  layers_.emplace(layers_.begin() + overlayer_insert_index, std::move(layer));
  overlayer_insert_index++;
}

void LayerManager::PopLayer(std::unique_ptr<Layer>&& layer) {
  auto iter = std::find(layers_.begin(), layers_.begin() + overlayer_insert_index, std::move(layer));
  if (iter != layers_.begin() + overlayer_insert_index) {
    layers_.erase(iter);
    overlayer_insert_index--;
  }
}

void LayerManager::PushOverLayer(std::unique_ptr<Layer>&& over_layer) { layers_.emplace_back(std::move(over_layer)); }

void LayerManager::PopOverLayer(std::unique_ptr<Layer>&& over_layer) {
  auto iter = std::find(layers_.begin() + overlayer_insert_index, layers_.end(), std::move(over_layer));
  if (iter != layers_.end()) {
    layers_.erase(iter);
  }
}
}  // namespace genesis