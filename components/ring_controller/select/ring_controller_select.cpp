#include "ring_controller_select.h"

namespace esphome::ring_controller {
void RingControllerSelect::set_parent(RingController *parent) { parent_ = parent; }

void RingControllerSelect::setup() {
  // Imposta il valore iniziale
  if (parent_ != nullptr) {
    this->publish_state(parent_->get_effect());
  }
}

void RingControllerSelect::control(const std::string &value) {
  if (parent_ != nullptr) {
    parent_->set_effect(value);
    this->publish_state(value);
  }
}

}  // namespace esphome::ring_controller