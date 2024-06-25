#include "error_handling.hpp"
#include "canzero/canzero.h"
#include "firmware/pdu12.hpp"

pdu_12v_command fsm::error_handling::approve(pdu_12v_command cmd) {
  if (canzero_get_error_level_mcu_temperature() == error_level_ERROR) {
    return pdu_12v_command_STOP;
  }

  return cmd;
}
