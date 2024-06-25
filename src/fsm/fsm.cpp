#include "fsm/fsm.hpp"
#include "canzero/canzero.h"
#include "fsm/error_handling.hpp"



void fsm::begin() {
  canzero_set_state(pdu_12v_state_CHANNELS_OFF);
  canzero_set_command(pdu_12v_command_TELEMETRY);
}


void fsm::update() {
  pdu_12v_command cmd = error_handling::approve(canzero_get_command());
  switch (cmd) {

  case pdu_12v_command_NONE:
  case pdu_12v_command_START:
  case pdu_12v_command_STOP:
  case pdu_12v_command_TELEMETRY:
    break;
  }
}
