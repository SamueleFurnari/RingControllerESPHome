import esphome.config_validation as cv
import esphome.codegen as cg
from esphome.components import light
from esphome.const import CONF_OUTPUT_ID, CONF_ID
from esphome import pins

CONF_PIN = "pin"
CONF_NUM_LEDS = "num_leds"

ring_controller_ns = cg.esphome_ns.namespace("ring_controller")
RingController = ring_controller_ns.class_("RingController", light.LightOutput, cg.Component)

CONFIG_SCHEMA = light.RGB_LIGHT_SCHEMA.extend({
    cv.GenerateID(CONF_OUTPUT_ID): cv.declare_id(RingController),
    cv.Optional(CONF_PIN, default=2): pins.gpio_output_pin_schema,
    cv.Optional(CONF_NUM_LEDS, default=16): cv.int_range(min=1, max=1000),
})

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_OUTPUT_ID])
    await cg.register_component(var, config)
    await light.register_light(var, config)
    
    pin = await cg.gpio_pin_expression(config[CONF_PIN])
    cg.add(var.set_pin(pin))
    cg.add(var.set_num_leds(config[CONF_NUM_LEDS]))
    
    cg.add_library("adafruit/Adafruit NeoPixel", "1.10.6")