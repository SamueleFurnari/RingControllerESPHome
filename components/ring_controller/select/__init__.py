import esphome.config_validation as cv
import esphome.codegen as cg
from esphome.components import select
from esphome.const import CONF_ID
from .. import ring_controller_ns, CONF_RING_CONTROLLER_ID, RingController

# RIMUOVI QUESTA RIGA
# DEPENDENCIES = ["ring_controller"]

RingControllerSelect = ring_controller_ns.class_("RingControllerSelect", select.Select, cg.Component)

CONF_EFFECTS = [
    "Rainbow",
    "Theater", 
    "Breathing",
    "Wipe",
    "Sparkle",
    "ColorCycle",
    "Static",
    "Off"
]

CONFIG_SCHEMA = select.select_schema(RingControllerSelect).extend({
    cv.GenerateID(CONF_RING_CONTROLLER_ID): cv.use_id(RingController),
})

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await select.register_select(var, config, options=CONF_EFFECTS)
    
    parent = await cg.get_variable(config[CONF_RING_CONTROLLER_ID])
    cg.add(var.set_parent(parent))