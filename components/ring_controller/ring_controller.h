#pragma once
#include "esphome/core/component.h"
#include "esphome/components/light/light_output.h"
#include <Adafruit_NeoPixel.h>
#include "effects.h"

namespace esphome
{
    namespace ring_controller
    {

        class RingController : public Component, public light::LightOutput
        {
        public:
            void setup() override
            {
                strip_ = new Adafruit_NeoPixel(num_leds_, pin_, NEO_GRB + NEO_KHZ800);
                strip_->begin();
                strip_->show();
                current_effect_ = effects::get_effect("Rainbow");
            }

            void loop() override
            {
                effects::EffectParams params{speed_, intensity_};
                current_effect_.apply(strip_, params);
                strip_->show();
            }

            light::LightTraits get_traits() override
            {
                auto traits = light::LightTraits();
                traits.set_supports_rgb(true);
                traits.set_supports_brightness(true);
                return traits;
            }

            void write_state(light::LightState *state) override
            {
                float r, g, b;
                state->current_values_as_rgb(&r, &g, &b);
                current_color_ = {r, g, b};
            }

            void set_effect_by_name(const std::string &name)
            {
                current_effect_name_ = name;
                current_effect_ = effects::get_effect(name);
            }

            void set_speed(int v) { speed_ = v; }
            void set_intensity(int v) { intensity_ = v; }

        protected:
            const int pin_{2};
            const int num_leds_{16};
            Adafruit_NeoPixel *strip_{nullptr};

            effects::RGB current_color_;
            std::string current_effect_name_{"Rainbow"};
            effects::Effect current_effect_;
            int speed_{50};
            int intensity_{150};
        };

    } // namespace ring_controller
} // namespace esphome
