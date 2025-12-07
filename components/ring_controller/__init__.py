import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.const import CONF_ID

CONF_RING_CONTROLLER_ID = "ring_controller_id"

ring_controller_ns = cg.esphome_ns.namespace("ring_controller")
RingController = ring_controller_ns.class_("RingController", cg.Component)

# Questo è necessario per permettere ad altri componenti di dipendere da ring_controller
CONFIG_SCHEMA = cv.COMPONENT_SCHEMA.extend({
    cv.GenerateID(): cv.declare_id(RingController),
})

async def to_code(config):
    # Nota: il componente viene registrato in light/__init__.py
    # Qui aggiungiamo solo la libreria
    cg.add_library("adafruit/Adafruit NeoPixel", "1.10.6")