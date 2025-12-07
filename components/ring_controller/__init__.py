import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import light
from esphome.const import CONF_ID

# Nome del namespace C++
neo_ns = cg.esphome_ns.namespace('neopixel_ring')
NeoPixelRing = neo_ns.class_('NeoPixelRing', cg.Component, light.LightOutput)

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(NeoPixelRing),
}).extend(light.LIGHT_OUTPUT_SCHEMA)

def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    yield cg.register_component(var, config)
    yield light.register_light(var, config)
