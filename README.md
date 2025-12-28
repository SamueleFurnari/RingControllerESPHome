# Ring Controller ESPHome

A custom ESPHome component for controlling NeoPixel LED strips (WS2812B) with predefined light effects.

## 🌟 Features

- **9 built-in light effects**, including realistic flame simulation
- **Full control** from Home Assistant
- **Speed and intensity adjustment** for effects
- **Easy configuration** via YAML
- **Tested** on ESP-01 1M

## 📋 Available Effects

1. **Flame** - Realistic flickering flame simulation
2. **Rainbow** - Animated rainbow
3. **Theater** - Theater chase with alternating LEDs
4. **Breathing** - Smooth breathing effect
5. **Wipe** - Progressive fill
6. **Sparkle** - Random sparkle
7. **ColorCycle** - Color cycling
8. **Static** - Static red color
9. **Off** - Turn off device

## 🔧 Installation

### Hardware Requirements

- ESP8266 or ESP32
- NeoPixel LED strip (WS2812B, WS2811, etc.) - tested with a 16-LED NeoPixel ring
- Adequate power supply for LEDs - if necessary

### ESPHome Configuration

Add this configuration to your YAML file:

```yaml
external_components:
  - source:
      type: git
      url: https://github.com/SamueleFurnari/RingControllerESPHome.git
      ref: main
    refresh: 1min
    components: [ring_controller]

light:
  - platform: ring_controller
    output_id: ring_output
    id: ring_light
    name: "Ring Controller"
    pin: GPIO2           # LED control pin
    num_leds: 16         # Number of LEDs in the strip

select:
  - platform: ring_controller
    ring_controller_id: ring_output
    name: "Ring Effect"

number:
  - platform: ring_controller
    ring_controller_id: ring_output
    parameter: speed
    name: "Effect Speed"
    
  - platform: ring_controller
    ring_controller_id: ring_output
    parameter: intensity
    name: "Effect Intensity"
```

## ⚙️ Configuration Parameters

### Light Component

| Parameter | Type | Default | Description |
|-----------|------|---------|-------------|
| `output_id` | ID | Required | Unique controller ID |
| `id` | ID | Required | Light component ID |
| `name` | string | Required | Name displayed in Home Assistant |
| `pin` | GPIO | 2 | GPIO pin connected to LEDs |
| `num_leds` | int | 16 | Number of LEDs in the strip (1-1000) |

### Select Component

| Parameter | Type | Default | Description |
|-----------|------|---------|-------------|
| `ring_controller_id` | ID | Required | Reference to light's output_id |
| `name` | string | Required | Effect selector name |

### Number Component

| Parameter | Type | Default | Description |
|-----------|------|---------|-------------|
| `ring_controller_id` | ID | Required | Reference to light's output_id |
| `parameter` | enum | Required | `speed` or `intensity` |
| `name` | string | Required | Numeric control name |

**Ranges:**
- **Speed**: 1-100 (default: 50)
- **Intensity**: 0-255 (default: 150)

## 📱 Usage in Home Assistant

After installing the component, you'll have access to:

### Light Entity
- **Turn on/off** the LED strip/ring
- **RGB control** (note: currently not used by effects)
- **Brightness** (note: currently not used by effects)
- When turned off, automatically switches to "Off" effect
- When turned on, restores the previously selected effect

### Select Entity
- **Effect selection** - Choose from 9 available effects (Flame, Rainbow, Theater, Breathing, Wipe, Sparkle, ColorCycle, Static, Off)

### Number Entities
- **Speed** - Controls animation speed (1-100)
- **Intensity** - Controls effect intensity (0-255)

## 🔌 Wiring Diagram

### ESP8266 (ESP-01)

```
ESP-01          NeoPixel Strip
GPIO2    -->    Data In (DIN)
GND      -->    GND
         -->    +5V (external power supply)
```

⚠️ **Important**: 
- Use a separate power supply for LEDs
- Add a 1000µF capacitor between +5V and GND
- Add a 470Ω resistor on the data pin

## 🛠️ Development

### Project Structure

```
components/ring_controller/
├── __init__.py                      # Base configuration
├── light/
│   ├── __init__.py                 # Light platform configuration
│   ├── ring_controller_light.h     # Controller header
│   ├── ring_controller_light.cpp   # Controller implementation
│   ├── effects.h                   # Effects header
│   └── effects.cpp                 # Effects implementation
├── select/
│   ├── __init__.py                 # Select platform configuration
│   ├── ring_controller_select.h    # Select header
│   └── ring_controller_select.cpp  # Select implementation
└── number/
    ├── __init__.py                 # Number platform configuration
    ├── ring_controller_number.h    # Number header
    └── ring_controller_number.cpp  # Number implementation
```

### Dependencies

- **Adafruit NeoPixel** v1.10.6 (automatically included)

## 🐛 Troubleshooting

### LEDs don't turn on
- Check the configured GPIO pin
- Verify LED power supply
- Check LED type (NEO_GRB + NEO_KHZ800)

### Effect doesn't change
- Verify the select is correctly linked to `ring_controller_id`
- Check ESPHome logs for errors

### Compilation failed
- Make sure you're using ESPHome 2024.11.0 or higher
- Verify the component is downloaded correctly
- Use `refresh: 1min` in external_components configuration

### Effect turns off automatically
- This is normal behavior when you turn off the light switch
- The component automatically switches to "Off" effect
- Turn the light back on to restore the previous effect

## 📝 Complete Example

```yaml
esphome:
  name: ring-controller
  friendly_name: Ring Controller

esp8266:
  board: esp01_1m

logger:

api:
  encryption:
    key: "your_api_key"

ota:
  - platform: esphome
    password: "your_password"

wifi:
  ssid: !secret wifi_ssid
  password: !secret wifi_password
  ap:
    ssid: "Ring-Controller Fallback"
    password: "fallback_password"

captive_portal:

external_components:
  - source:
      type: git
      url: https://github.com/SamueleFurnari/RingControllerESPHome.git
      ref: main
    refresh: 1min
    components: [ring_controller]

light:
  - platform: ring_controller
    output_id: ring_output
    id: ring_light
    name: "Ring Controller"
    pin: GPIO2
    num_leds: 16

select:
  - platform: ring_controller
    ring_controller_id: ring_output
    name: "Ring Effect"

number:
  - platform: ring_controller
    ring_controller_id: ring_output
    parameter: speed
    name: "Effect Speed"
    
  - platform: ring_controller
    ring_controller_id: ring_output
    parameter: intensity
    name: "Effect Intensity"
```

## 🤝 Contributing

Contributions are welcome! Feel free to:
- Open issues for bugs or feature requests
- Submit pull requests
- Suggest new light effects

## 📄 License

This project is distributed under the MIT License.

## 👤 Author

**Samuele Furnari**
- GitHub: [@SamueleFurnari](https://github.com/SamueleFurnari)

## 🙏 Acknowledgments

- [ESPHome](https://esphome.io/) for the amazing framework
- [Adafruit](https://github.com/adafruit/Adafruit_NeoPixel) for the NeoPixel library
- The Home Assistant community

---

⭐ If this project has been useful to you, consider giving it a star on GitHub!