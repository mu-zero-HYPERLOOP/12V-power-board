#pragma once
#include "canzero/canzero.h"
#include "firmware/pdu12.hpp"

namespace sdc {

  inline void begin() {
    pdu12::set_sdc(false);
    canzero_set_sdc_status(sdc_status_OPEN);
  }

  inline void open(){
    pdu12::set_sdc(false);
    canzero_set_sdc_status(sdc_status_OPEN);
  }
  inline void close(){
    pdu12::set_sdc(true);
    canzero_set_sdc_status(sdc_status_CLOSED);
  }
}
