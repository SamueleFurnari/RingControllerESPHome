#pragma once
#include "esphome/core/component.h"
#include "esphome/components/number/number.h"
#include "../light/ring_controller_light.h"

namespace esphome::ring_controller {
class RingControllerNumber : public number::Number, public Component {
 public:
  void set_parent(RingController *parent);
  void set_parameter(const std::string &param);
  void setup() override;

 protected:
  void control(float value) override;

  RingController *parent_{nullptr};
  std::string parameter_;
};

}  // namespace esphome::ring_controller