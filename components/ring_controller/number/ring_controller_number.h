#pragma once
#include "esphome/core/component.h"
#include "esphome/components/number/number.h"
#include "../light/ring_controller_light.h"

namespace esphome {
namespace ring_controller {

class RingControllerNumber : public number::Number, public Component {
 public:
  void set_parent(RingController *parent) { parent_ = parent; }
  void set_parameter(const std::string &param) { parameter_ = param; }

  void setup() override {
    // Imposta il valore iniziale
    if (parent_ != nullptr) {
      if (parameter_ == "speed") {
        this->publish_state(parent_->get_speed());
      } else if (parameter_ == "intensity") {
        this->publish_state(parent_->get_intensity());
      }
    }
  }

 protected:
  void control(float value) override {
    if (parent_ != nullptr) {
      if (parameter_ == "speed") {
        parent_->set_speed((int)value);
      } else if (parameter_ == "intensity") {
        parent_->set_intensity((int)value);
      }
      this->publish_state(value);
    }
  }

  RingController *parent_{nullptr};
  std::string parameter_;
};

}  // namespace ring_controller
}  // namespace esphome