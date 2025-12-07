#pragma once
#include <Adafruit_NeoPixel.h>
#include <string>

namespace effects
{

    struct RGB
    {
        float r, g, b;
    };
    struct EffectParams
    {
        int speed;
        int intensity;
    };

    class Effect
    {
    public:
        virtual ~Effect() = default;
        virtual void apply(Adafruit_NeoPixel *strip, const EffectParams &params) = 0;
    };

    class RainbowEffect : public Effect
    {
    public:
        ~RainbowEffect() override;
        void apply(Adafruit_NeoPixel *strip, const EffectParams &params) override;
    };
    class TheaterEffect : public Effect
    {
    public:
        ~TheaterEffect() override;
        void apply(Adafruit_NeoPixel *strip, const EffectParams &params) override;
    };
    class BreathingEffect : public Effect
    {
    public:
        ~BreathingEffect() override;
        void apply(Adafruit_NeoPixel *strip, const EffectParams &params) override;
    };
    class WipeEffect : public Effect
    {
    public:
        ~WipeEffect() override;
        void apply(Adafruit_NeoPixel *strip, const EffectParams &params) override;
    };
    class SparkleEffect : public Effect
    {
    public:
        ~SparkleEffect() override;
        void apply(Adafruit_NeoPixel *strip, const EffectParams &params) override;
    };
    class ColorCycleEffect : public Effect
    {
    public:
        ~ColorCycleEffect() override;
        void apply(Adafruit_NeoPixel *strip, const EffectParams &params) override;
    };
    class StaticEffect : public Effect
    {
    public:
        ~StaticEffect() override;
        void apply(Adafruit_NeoPixel *strip, const EffectParams &params) override;
    };
    class OffEffect : public Effect
    {
    public:
        ~OffEffect() override;
        void apply(Adafruit_NeoPixel *strip, const EffectParams &params) override;
    };

    Effect* get_effect(const std::string &name);

} // namespace effects