#pragma once
#include <Adafruit_NeoPixel.h>
#include <string>

namespace effects {

struct RGB {
  float r, g, b;
};
struct EffectParams {
  int speed;
  int intensity;
};

class Effect {
 public:
  virtual ~Effect() = default;
  virtual void apply(Adafruit_NeoPixel *strip, const EffectParams &params) = 0;
};

class RainbowEffect : public Effect {
 public:
  ~RainbowEffect() override;
  void apply(Adafruit_NeoPixel *strip, const EffectParams &params) override;
};
class TheaterEffect : public Effect {
 public:
  ~TheaterEffect() override;
  void apply(Adafruit_NeoPixel *strip, const EffectParams &params) override;
};
class BreathingEffect : public Effect {
 public:
  ~BreathingEffect() override;
  void apply(Adafruit_NeoPixel *strip, const EffectParams &params) override;
};
class WipeEffect : public Effect {
 public:
  ~WipeEffect() override;
  void apply(Adafruit_NeoPixel *strip, const EffectParams &params) override;
};
class SparkleEffect : public Effect {
 public:
  ~SparkleEffect() override;
  void apply(Adafruit_NeoPixel *strip, const EffectParams &params) override;
};
class ColorCycleEffect : public Effect {
 public:
  ~ColorCycleEffect() override;
  void apply(Adafruit_NeoPixel *strip, const EffectParams &params) override;
};
class StaticEffect : public Effect {
 public:
  ~StaticEffect() override;
  void apply(Adafruit_NeoPixel *strip, const EffectParams &params) override;
};
class OffEffect : public Effect {
 public:
  ~OffEffect() override;
  void apply(Adafruit_NeoPixel *strip, const EffectParams &params) override;
};

#define FLAME_WIDTH 3
#define FLICKER_CHANCE 3
#define SCALERVAL 256 * 3

struct flame_element {
  int brightness;
  int step;
  int max_brightness;
  long rgb[3];
  uint8_t state;
};

class FlameEffect : public Effect {
 public:
  FlameEffect();
  ~FlameEffect() override;
  void apply(Adafruit_NeoPixel *strip, const EffectParams &params) override;

 private:
  void InitFlames(int num_flames);
  void UpdateFlameColor(Adafruit_NeoPixel *strip, uint8_t flame_num, int new_brightness);
  void CreateNewFlame(uint8_t flame_num);
  int GetStepSize();
  int GetMaxBrightness();

  flame_element *flames_;
  int number_of_flames_;
  uint32_t rez_range_;

  static const double flamecolors_[22][3];
};

Effect *get_effect(const std::string &name);

}  // namespace effects