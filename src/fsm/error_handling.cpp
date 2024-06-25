#include "error_handling.hpp"
#include "canzero/canzero.h"
#include "firmware/pdu12.hpp"

pdu_12v_command fsm::error_handling::approve(pdu_12v_command cmd) {
  if (canzero_get_error_any_short() == error_flag_ERROR) {
    // affected channel is already off anyway
    pdu12::set_sdc(false);
    return cmd;
  }
  if (canzero_get_error_heartbeat_miss() == error_flag_ERROR) {
    // with only telemetry on nothing too bad can happen right?
    pdu12::set_sdc(false);
    return cmd;
  }

  if (canzero_get_error_level_mcu_temperature() == error_level_ERROR) {
    pdu12::set_sdc(false);
    return pdu_12v_command_STOP;
  }

  return cmd;
}
