#pragma once
#include "esphome/core/component.h"
#include "esphome/components/light/light_output.h"
#include "esphome/core/gpio.h"
#include <Adafruit_NeoPixel.h>
#include "effects.h"

namespace esphome
{
    namespace ring_controller
    {
        class RingController : public light::LightOutput, public Component
        {
        public:
            void setup() override
            {
                pin_->setup();
                strip_ = new Adafruit_NeoPixel(num_leds_, pin_num_, NEO_GRB + NEO_KHZ800);
                strip_->begin();
                strip_->show();
                current_effect_ = effects::get_effect("Rainbow");
            }

            void loop() override
            {
                if (current_effect_ != nullptr) {
                    effects::EffectParams params{speed_, intensity_};
                    current_effect_->apply(strip_, params);
                    strip_->show();
                }
            }

            light::LightTraits get_traits() override
            {
                auto traits = light::LightTraits();
                traits.set_supported_color_modes({light::ColorMode::RGB});
                return traits;
            }

            void write_state(light::LightState *state) override
            {
                float r, g, b;
                state->current_values_as_rgb(&r, &g, &b);
                current_color_ = {r, g, b};
            }

            void set_pin(InternalGPIOPin *pin) { 
                pin_ = pin;
                pin_num_ = pin->get_pin();
            }
            void set_num_leds(uint16_t num) { num_leds_ = num; }

            // NUOVI METODI PUBBLICI
            void set_effect(const std::string &name)
            {
                if (current_effect_ != nullptr) {
                    delete current_effect_;
                }
                current_effect_name_ = name;
                current_effect_ = effects::get_effect(name);
            }

            std::string get_effect() const { return current_effect_name_; }
            
            void set_speed(int v) { 
                speed_ = v; 
            }
            
            int get_speed() const { return speed_; }
            
            void set_intensity(int v) { 
                intensity_ = v; 
            }
            
            int get_intensity() const { return intensity_; }

            ~RingController() {
                if (strip_ != nullptr) {
                    delete strip_;
                }
                if (current_effect_ != nullptr) {
                    delete current_effect_;
                }
            }

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
        };

    } // namespace ring_controller
} // namespace esphome