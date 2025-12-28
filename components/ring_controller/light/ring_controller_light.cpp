#include "ring_controller_light.h"

namespace esphome::ring_controller {

void RingController::setup() {
  pin_->setup();
  strip_ = new Adafruit_NeoPixel(num_leds_, pin_num_, NEO_GRB + NEO_KHZ800);
  strip_->begin();
  strip_->show();
  current_effect_ = effects::get_effect("Rainbow");
}

void RingController::loop() {
  if (current_effect_ != nullptr) {
    effects::EffectParams params{speed_, intensity_};
    current_effect_->apply(strip_, params);
    strip_->show();
  }
}

light::LightTraits RingController::get_traits() {
  auto traits = light::LightTraits();
  traits.set_supported_color_modes({light::ColorMode::RGB});
  return traits;
}

void RingController::write_state(light::LightState *state) {
  float r, g, b;
  state->current_values_as_rgb(&r, &g, &b);
  current_color_ = {r, g, b};
  
  bool is_on = state->current_values.is_on();
  
  if (is_on != enabled_) {
    if (is_on) {
      enabled_ = true;
      set_effect(saved_effect_name_);
    } else {
      enabled_ = false;
      saved_effect_name_ = current_effect_name_;
      set_effect("OffEffect");
    }
  }
}

void RingController::set_pin(InternalGPIOPin *pin) {
  pin_ = pin;
  pin_num_ = pin->get_pin();
}

void RingController::set_num_leds(uint16_t num) { num_leds_ = num; }

void RingController::set_effect(const std::string &name) {
  if (current_effect_ != nullptr) {
    delete current_effect_;
  }
  current_effect_name_ = name;
  current_effect_ = effects::get_effect(name);
}

std::string RingController::get_effect() const { return current_effect_name_; }

void RingController::set_speed(int v) { speed_ = v; }

int RingController::get_speed() const { return speed_; }

void RingController::set_intensity(int v) { intensity_ = v; }

int RingController::get_intensity() const { return intensity_; }

RingController::~RingController() {
  if (strip_ != nullptr) {
    delete strip_;
  }
  if (current_effect_ != nullptr) {
    delete current_effect_;
  }
}

}  // namespace esphome::ring_controller