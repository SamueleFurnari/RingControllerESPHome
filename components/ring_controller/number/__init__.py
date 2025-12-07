import esphome.config_validation as cv
import esphome.codegen as cg
from esphome.components import number
from esphome.const import CONF_ID, CONF_TYPE
from .. import ring_controller_ns, CONF_RING_CONTROLLER_ID, RingController

# RIMUOVI QUESTA RIGA
# DEPENDENCIES = ["ring_controller"]

RingControllerNumber = ring_controller_ns.class_("RingControllerNumber", number.Number, cg.Component)

CONF_PARAMETER = "parameter"
TYPE_SPEED = "speed"
TYPE_INTENSITY = "intensity"

CONFIG_SCHEMA = number.number_schema(RingControllerNumber).extend({
    cv.GenerateID(CONF_RING_CONTROLLER_ID): cv.use_id(RingController),
    cv.Required(CONF_PARAMETER): cv.enum({
        TYPE_SPEED: TYPE_SPEED,
        TYPE_INTENSITY: TYPE_INTENSITY
    }, upper=False),
})

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    
    if config[CONF_PARAMETER] == TYPE_SPEED:
        await number.register_number(var, config, min_value=1, max_value=100, step=1)
    else:
        await number.register_number(var, config, min_value=0, max_value=255, step=1)
    
    parent = await cg.get_variable(config[CONF_RING_CONTROLLER_ID])
    cg.add(var.set_parent(parent))
    cg.add(var.set_parameter(config[CONF_PARAMETER]))