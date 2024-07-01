#pragma once

#include "util/timestamp.h"
namespace fsm {
  constexpr Duration RESTART_TIMEOUT = 5_s;

  void begin();

  void update();

}
