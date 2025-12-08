#include "effects.h"
#include <math.h>
#include <stdlib.h>

namespace effects
{
    // ========== EFFETTI ESISTENTI ==========
    
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

    // Distruttori
    RainbowEffect::~RainbowEffect() {}
    TheaterEffect::~TheaterEffect() {}
    BreathingEffect::~BreathingEffect() {}
    WipeEffect::~WipeEffect() {}
    SparkleEffect::~SparkleEffect() {}
    ColorCycleEffect::~ColorCycleEffect() {}
    StaticEffect::~StaticEffect() {}
    OffEffect::~OffEffect() {}

    // ========== NUOVO: FLAME EFFECT ==========
    
    const double FlameEffect::flamecolors_[22][3] = {
        {SCALERVAL, 0, 0},
        {SCALERVAL, 0, 0},
        {SCALERVAL, 0, 0},
        {SCALERVAL, 0, 0},
        {SCALERVAL, 0, 0},
        {SCALERVAL, 0, 0},
        {SCALERVAL, 0, 0},
        {SCALERVAL, 0, 0},
        {SCALERVAL, SCALERVAL * 0.4, 0},
        {SCALERVAL, SCALERVAL * 0.4, 0},
        {SCALERVAL, SCALERVAL * 0.4, 0},
        {SCALERVAL, SCALERVAL * 0.4, 0},
        {SCALERVAL, SCALERVAL * 0.3, 0},
        {SCALERVAL, SCALERVAL * 0.3, 0},
        {SCALERVAL, SCALERVAL * 0.3, 0},
        {SCALERVAL, SCALERVAL * 0.3, 0},
        {SCALERVAL, SCALERVAL * 0.3, 0},
        {SCALERVAL, SCALERVAL * 0.3, 0},
        {SCALERVAL, SCALERVAL * 0.3, 0},
        {SCALERVAL, SCALERVAL * 0.3, SCALERVAL},         // white
        {0, SCALERVAL * 0.2, SCALERVAL},                 // blue flame
        {SCALERVAL, SCALERVAL * 0.3, SCALERVAL * 0.5}
    };

    FlameEffect::FlameEffect() : flames_(nullptr), number_of_flames_(0), rez_range_(256 * 3)
    {
    }

    FlameEffect::~FlameEffect()
    {
        if (flames_ != nullptr) {
            delete[] flames_;
        }
    }

    void FlameEffect::InitFlames(int num_flames)
    {
        if (flames_ != nullptr && number_of_flames_ != num_flames) {
            delete[] flames_;
            flames_ = nullptr;
        }
        
        if (flames_ == nullptr) {
            number_of_flames_ = num_flames;
            flames_ = new flame_element[number_of_flames_];
            
            for (int i = 0; i < number_of_flames_; i++) {
                flames_[i].state = 0;
                flames_[i].brightness = 0;
            }
        }
    }

    void FlameEffect::apply(Adafruit_NeoPixel *strip, const EffectParams &params)
    {
        int num_leds = strip->numPixels();
        int num_flames = num_leds / FLAME_WIDTH;
        
        // Inizializza se necessario
        if (flames_ == nullptr || number_of_flames_ != num_flames) {
            InitFlames(num_flames);
        }

        for (int flame_count = 0; flame_count < number_of_flames_; flame_count++)
        {
            int new_brightness = 0;
            
            switch (flames_[flame_count].state)
            {
            case 0: // reset
                CreateNewFlame(flame_count);
                break;

            case 1: // increasing
                new_brightness = flames_[flame_count].brightness + flames_[flame_count].step;
                if (new_brightness > flames_[flame_count].max_brightness)
                {
                    UpdateFlameColor(strip, flame_count, flames_[flame_count].max_brightness);
                    flames_[flame_count].brightness = flames_[flame_count].max_brightness;
                    flames_[flame_count].step = GetStepSize();
                    flames_[flame_count].state = 2;
                }
                else
                {
                    UpdateFlameColor(strip, flame_count, new_brightness);
                    flames_[flame_count].brightness = new_brightness;
                }
                break;

            case 2: // decreasing
                new_brightness = flames_[flame_count].brightness - flames_[flame_count].step;
                // chance to flicker/rekindle
                if (new_brightness > 0 && random(new_brightness) < FLICKER_CHANCE)
                {
                    flames_[flame_count].state = 1;
                    flames_[flame_count].max_brightness = max(GetMaxBrightness(), flames_[flame_count].brightness);
                    flames_[flame_count].step = GetStepSize();
                }
                else
                {
                    if (new_brightness < 1)
                    {
                        flames_[flame_count].state = 0;
                        flames_[flame_count].brightness = 0;
                        UpdateFlameColor(strip, flame_count, 0);
                    }
                    else
                    {
                        UpdateFlameColor(strip, flame_count, new_brightness);
                        flames_[flame_count].brightness = new_brightness;
                    }
                }
                break;
            }
        }
    }

    void FlameEffect::UpdateFlameColor(Adafruit_NeoPixel *strip, uint8_t flame_num, int new_brightness)
    {
        unsigned long rgb[3];
        uint8_t scaleD_rgb[3];
        long color_channel_value;

        new_brightness = min(new_brightness, flames_[flame_num].max_brightness);

        for (int rgb_channel = 0; rgb_channel < 3; rgb_channel++)
        {
            color_channel_value = flames_[flame_num].rgb[rgb_channel];
            color_channel_value = color_channel_value * (uint32_t)new_brightness;
            color_channel_value = color_channel_value / (uint32_t)rez_range_;
            rgb[rgb_channel] = max(0L, color_channel_value);
        }

        // Distribuisci il colore sui pixel della fiamma
        for (int sub_pixel = 0; sub_pixel < FLAME_WIDTH; sub_pixel++)
        {
            for (int i = 0; i < 3; i++)
            {
                uint8_t acc = rgb[i] / 3;
                int d = rgb[i] % 3;
                if (sub_pixel < d) {
                    acc++;
                }
                scaleD_rgb[i] = acc;
            }
            uint32_t c = strip->Color(scaleD_rgb[0], scaleD_rgb[1], scaleD_rgb[2]);
            strip->setPixelColor(flame_num * FLAME_WIDTH + sub_pixel, c);
        }
    }

    void FlameEffect::CreateNewFlame(uint8_t flame_num)
    {
        flames_[flame_num].step = GetStepSize();
        flames_[flame_num].max_brightness = GetMaxBrightness();
        flames_[flame_num].brightness = 0;
        flames_[flame_num].state = 1;
        
        uint8_t color_index = random(22);
        for (int i = 0; i < 3; i++)
        {
            flames_[flame_num].rgb[i] = flamecolors_[color_index][i];
        }
    }

    int FlameEffect::GetStepSize()
    {
        return random(70) + 1;
    }

    int FlameEffect::GetMaxBrightness()
    {
        return random(rez_range_ / 2) + rez_range_ / 2;
    }

    // ========== FACTORY ==========
    
    Effect* get_effect(const std::string &name)
    {
        if (name == "Flame")
            return new FlameEffect();
        if (name == "Rainbow")
            return new RainbowEffect();
        if (name == "Theater")
            return new TheaterEffect();
        if (name == "Breathing")
            return new BreathingEffect();
        if (name == "Wipe")
            return new WipeEffect();
        if (name == "Sparkle")
            return new SparkleEffect();
        if (name == "ColorCycle")
            return new ColorCycleEffect();
        if (name == "Static")
            return new StaticEffect();
        if (name == "Off")
            return new OffEffect();
        return new RainbowEffect();
    }

} // namespace effects