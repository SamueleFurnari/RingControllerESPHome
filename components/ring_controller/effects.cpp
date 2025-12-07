#include "effects.h"
#include <math.h>
#include <stdlib.h>

namespace effects
{

    // Rainbow
    void RainbowEffect::apply(Adafruit_NeoPixel *strip, const EffectParams &params)
    {
        static uint16_t j = 0;
        for (uint16_t i = 0; i < strip->numPixels(); i++)
        {
            uint8_t r = (sin((i + j) * 0.25) + 1) * 127;
            uint8_t g = (sin((i + j) * 0.25 + 2) + 1) * 127;
            uint8_t b = (sin((i + j) * 0.25 + 4) + 1) * 127;
            strip->setPixelColor(i, strip->Color(r, g, b));
        }
        j += params.speed / 10;
    }

    // Theater
    void TheaterEffect::apply(Adafruit_NeoPixel *strip, const EffectParams &)
    {
        static int o = 0;
        for (int i = 0; i < strip->numPixels(); i++)
        {
            if ((i + o) % 3 == 0)
                strip->setPixelColor(i, strip->Color(200, 50, 0));
            else
                strip->setPixelColor(i, 0);
        }
        o = (o + 1) % 3;
    }

    // Breathing
    void BreathingEffect::apply(Adafruit_NeoPixel *strip, const EffectParams &params)
    {
        static uint16_t t = 0;
        float s = (sin(t / 30.0) + 1) * 0.5;
        uint8_t v = s * 255;
        for (int i = 0; i < strip->numPixels(); i++)
            strip->setPixelColor(i, strip->Color(v, v, v));
        t += params.speed / 5;
    }

    // Wipe
    void WipeEffect::apply(Adafruit_NeoPixel *strip, const EffectParams &)
    {
        static int p = 0;
        for (int i = 0; i < strip->numPixels(); i++)
        {
            if (i <= p)
                strip->setPixelColor(i, strip->Color(255, 0, 0));
            else
                strip->setPixelColor(i, 0);
        }
        p = (p + 1) % strip->numPixels();
    }

    // Sparkle
    void SparkleEffect::apply(Adafruit_NeoPixel *strip, const EffectParams &)
    {
        for (int i = 0; i < strip->numPixels(); i++)
            strip->setPixelColor(i, 0);
        int idx = rand() % strip->numPixels();
        strip->setPixelColor(idx, strip->Color(255, 255, 255));
    }

    // ColorCycle
    void ColorCycleEffect::apply(Adafruit_NeoPixel *strip, const EffectParams &params)
    {
        static uint8_t h = 0;
        for (int i = 0; i < strip->numPixels(); i++)
        {
            uint8_t r = (h + i * 10) % 255;
            uint8_t g = (h + i * 5) % 255;
            uint8_t b = (h) % 255;
            strip->setPixelColor(i, strip->Color(r, g, b));
        }
        h = (h + params.speed / 5) % 255;
    }

    // Static
    void StaticEffect::apply(Adafruit_NeoPixel *strip, const EffectParams &)
    {
        for (int i = 0; i < strip->numPixels(); i++)
            strip->setPixelColor(i, strip->Color(255, 0, 0));
    }

    // Off
    void OffEffect::apply(Adafruit_NeoPixel *strip, const EffectParams &)
    {
        for (int i = 0; i < strip->numPixels(); i++)
            strip->setPixelColor(i, 0);
    }

    // Factory
    Effect get_effect(const std::string &name)
    {
        if (name == "Rainbow")
            return RainbowEffect();
        if (name == "Theater")
            return TheaterEffect();
        if (name == "Breathing")
            return BreathingEffect();
        if (name == "Wipe")
            return WipeEffect();
        if (name == "Sparkle")
            return SparkleEffect();
        if (name == "ColorCycle")
            return ColorCycleEffect();
        if (name == "Static")
            return StaticEffect();
        if (name == "Off")
            return OffEffect();
        return RainbowEffect();
    }

} // namespace effects
