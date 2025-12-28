#pragma once
#include "esphome/core/component.h"
#include "esphome/components/select/select.h"
#include "../light/ring_controller_light.h"

namespace esphome::ring_controller {
class RingControllerSelect : public select::Select, public Component {
 public:
  void set_parent(RingController *parent);
  void setup() override;

 protected:
  void control(const std::string &value) override;

  RingController *parent_{nullptr};
};

}  // namespace esphome::ring_controller