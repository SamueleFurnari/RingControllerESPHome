import esphome.codegen as cg
import esphome.config_validation as cv

CONF_RING_CONTROLLER_ID = "ring_controller_id"

ring_controller_ns = cg.esphome_ns.namespace("ring_controller")
RingController = ring_controller_ns.class_("RingController", cg.Component)

CONFIG_SCHEMA = cv.COMPONENT_SCHEMA.extend({
    cv.GenerateID(): cv.declare_id(RingController),
})