#pragma once

#include "firmware/pdu12.hpp"
#include "pinout.h"
#include "util/boxcar.h"
#include "util/interval.h"
#include "canzero/canzero.h"

pdu_12v_state channel_control(pdu_12v_command cmd);
