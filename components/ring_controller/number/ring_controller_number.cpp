#include "ring_controller_number.h"

namespace esphome::ring_controller {
void RingControllerNumber::set_parent(RingController *parent) { parent_ = parent; }

void RingControllerNumber::set_parameter(const std::string &param) { parameter_ = param; }

void RingControllerNumber::setup() {
  // Imposta il valore iniziale
  if (parent_ != nullptr) {
    if (parameter_ == "speed") {
      this->publish_state(parent_->get_speed());
    } else if (parameter_ == "intensity") {
      this->publish_state(parent_->get_intensity());
    }
  }
}

void RingControllerNumber::control(float value) {
  if (parent_ != nullptr) {
    if (parameter_ == "speed") {
      parent_->set_speed((int) value);
    } else if (parameter_ == "intensity") {
      parent_->set_intensity((int) value);
    }
    this->publish_state(value);
  }
}

}  // namespace esphome::ring_controller