#include "fsm/fsm.hpp"
#include "canzero/canzero.h"
#include "fsm/error_handling.hpp"
#include "firmware/pdu12.hpp"
#include "sdc.h"


Timestamp last_transition;

void fsm::begin() {
  canzero_set_state(pdu_12v_state_CHANNELS_OFF);
  canzero_set_command(pdu_12v_command_START);
  pdu12::set_sdc(false);
  last_transition = Timestamp::now();
}


void fsm::update() {
  pdu_12v_command cmd = error_handling::approve(canzero_get_command());

  pdu_12v_state state = canzero_get_state();
  pdu_12v_state next_state = state;

  switch (cmd) {
  case pdu_12v_command_NONE:
    break;
  case pdu_12v_command_START:
    next_state = pdu_12v_state_CHANNELS_ON;
    if (canzero_get_error_any_short() == error_flag_OK && 
        canzero_get_error_heartbeat_miss() == error_flag_OK) {
      sdc::close();
    } else {
      sdc::open();
    }
    break;
  case pdu_12v_command_STOP:
    next_state = pdu_12v_state_CHANNELS_OFF;
    sdc::open();
    break;
  case pdu_12v_command_TELEMETRY:
    next_state = pdu_12v_state_CHANNELS_TELEMETRY;
    sdc::open();
    break;
  case pdu_12v_command_RESTART:
    next_state = pdu_12v_state_RESTARTING;
    sdc::open();
    if (Timestamp::now() - last_transition > fsm::RESTART_TIMEOUT) {
      next_state = pdu_12v_state_CHANNELS_TELEMETRY;
    }
    break;
  }
  if (state != next_state) {
    last_transition = Timestamp::now();
    canzero_set_state(next_state);
  }

}
