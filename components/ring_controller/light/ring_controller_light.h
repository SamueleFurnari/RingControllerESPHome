#pragma once
#include "esphome/core/component.h"
#include "esphome/components/light/light_output.h"
#include "esphome/core/gpio.h"
#include <Adafruit_NeoPixel.h>
#include "effects.h"

namespace esphome::ring_controller {

class RingController : public light::LightOutput, public Component {
 public:
  void setup() override;
  void loop() override;
  light::LightTraits get_traits() override;
  void write_state(light::LightState *state) override;

  void set_pin(InternalGPIOPin *pin);
  void set_num_leds(uint16_t num);
  void set_effect(const std::string &name);
  std::string get_effect() const;
  void set_speed(int v);
  int get_speed() const;
  void set_intensity(int v);
  int get_intensity() const;

  ~RingController();

 protected:
  InternalGPIOPin *pin_{nullptr};
  uint8_t pin_num_{2};
  uint16_t num_leds_{16};
  Adafruit_NeoPixel *strip_{nullptr};

  effects::RGB current_color_;
  std::string current_effect_name_{"Rainbow"};
  effects::Effect *current_effect_{nullptr};
  int speed_{50};
  int intensity_{150};
  
  bool enabled_{true};
  std::string saved_effect_name_{"Rainbow"};
};

}  // namespace esphome::ring_controller