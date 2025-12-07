#pragma once
#include "esphome/core/component.h"
#include "esphome/components/select/select.h"
#include "../light/ring_controller_light.h"

namespace esphome {
namespace ring_controller {

class RingControllerSelect : public select::Select, public Component {
 public:
  void set_parent(RingController *parent) { parent_ = parent; }

  void setup() override {
    // Imposta il valore iniziale
    if (parent_ != nullptr) {
      this->publish_state(parent_->get_effect());
    }
  }

 protected:
  void control(const std::string &value) override {
    if (parent_ != nullptr) {
      parent_->set_effect(value);
      this->publish_state(value);
    }
  }

  RingController *parent_{nullptr};
};

}  // namespace ring_controller
}  // namespace esphome