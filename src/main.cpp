
#include "canzero/canzero.h"
#include "channel_control.h"
#include "defaults.h"
#include "error_level_range_check.h"
#include "firmware/pdu12.hpp"
#include "util/boxcar.h"
#include "util/interval.h"
#include "util/timing.h"
#include <FlexCAN_T4.h>
#include <cassert>

static IntervalTiming main_loop_interval_timer;

static Interval mcu_temperature_interval(100_Hz);
static BoxcarFilter<Temperature, 100> mcu_temperature_filter(24_Celcius);
static ErrorLevelRangeCheck<EXPECT_UNDER>
    mcu_temp_check(canzero_get_mcu_temperature,
                   canzero_get_error_level_config_mcu_temperature,
                   canzero_set_error_level_mcu_temperature);

int main() {
  canzero_init();

  can_defaults();
  canzero_update_continue(canzero_get_time());

  pdu12::begin();

  canzero_set_state(pdu_state_RUNNING);
  while (true) {

    canzero_can0_poll();
    canzero_can1_poll();

    pdu12::update();
    channel_control();

    // =========== SDC CTRL =========
    bool any_short = pdu12::any_short();
    pdu12::set_sdc(!any_short);
    canzero_set_sdc_status(any_short ? sdc_status_OPEN : sdc_status_CLOSED);

    // ======== MCU TEMPERATURE ========
    if (mcu_temperature_interval.next()) {
      Temperature mcu_temperature = pdu12::read_mcu_temperature();
      mcu_temperature_filter.push(mcu_temperature);
      canzero_set_mcu_temperature(mcu_temperature_filter.get().as_celcius());
      mcu_temp_check.check();
    }

    // =========== main loop frequency ==========
    main_loop_interval_timer.tick();
    canzero_set_loop_frequency(
        static_cast<float>(main_loop_interval_timer.frequency()));

    canzero_update_continue(canzero_get_time());
  }
}
