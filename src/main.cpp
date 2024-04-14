
#include "canzero/canzero.h"
#include "firmware/pdu12.hpp"
#include "util/ema.hpp"
#include "assert.h"
#include "util/timestamp.h"
static constexpr Temperature ERROR_MCU_OVER_TEMP = 80_Celcius;
static constexpr Duration ERROR_MCU_OVER_TEMP_TIME_THRESH = 10_s;
static constexpr Temperature WARN_MCU_OVER_TEMP = 50_Celcius;
static constexpr Duration WARN_MCU_OVER_TEMP_TIME_THRESH = 10_s;

static inline pdu_channel_status to_canzero_status(pdu12_channel_status ch) {
  switch (ch) {
  case ON:
    return pdu_channel_status_ON;
  case OFF:
    return pdu_channel_status_OFF;
  case SHORT:
    return pdu_channel_status_SHORT_CIRCUIT;
  }
}

int main() {

  canzero_init();

  canzero_set_state(pdu_state_INIT);
  canzero_set_lp_channel1_status(pdu_channel_status_OFF);
  canzero_set_lp_channel2_status(pdu_channel_status_OFF);
  canzero_set_lp_channel3_status(pdu_channel_status_OFF);
  canzero_set_lp_channel4_status(pdu_channel_status_OFF);
  canzero_set_lp_channel5_status(pdu_channel_status_OFF);
  canzero_set_lp_channel6_status(pdu_channel_status_OFF);
  canzero_set_lp_channel7_status(pdu_channel_status_OFF);
  canzero_set_lp_channel8_status(pdu_channel_status_OFF);
  canzero_set_lp_channel9_status(pdu_channel_status_OFF);
  canzero_set_lp_channel10_status(pdu_channel_status_OFF);
  canzero_set_lp_channel11_status(pdu_channel_status_OFF);
  canzero_set_lp_channel12_status(pdu_channel_status_OFF);
  canzero_set_lp_channel13_status(pdu_channel_status_OFF);
  canzero_set_lp_channel14_status(pdu_channel_status_OFF);

  canzero_set_lp_channel1_current(0);
  canzero_set_lp_channel2_current(0);
  canzero_set_lp_channel3_current(0);
  canzero_set_lp_channel4_current(0);
  canzero_set_lp_channel5_current(0);
  canzero_set_lp_channel6_current(0);
  canzero_set_lp_channel7_current(0);
  canzero_set_lp_channel8_current(0);
  canzero_set_lp_channel9_current(0);
  canzero_set_lp_channel10_current(0);
  canzero_set_lp_channel11_current(0);
  canzero_set_lp_channel12_current(0);
  canzero_set_lp_channel13_current(0);
  canzero_set_lp_channel14_current(0);

  canzero_set_lp_channel1_control(pdu_channel_control_OFF);
  canzero_set_lp_channel2_control(pdu_channel_control_OFF);
  canzero_set_lp_channel3_control(pdu_channel_control_OFF);
  canzero_set_lp_channel4_control(pdu_channel_control_OFF);
  canzero_set_lp_channel5_control(pdu_channel_control_OFF);
  canzero_set_lp_channel6_control(pdu_channel_control_OFF);
  canzero_set_lp_channel7_control(pdu_channel_control_OFF);
  canzero_set_lp_channel8_control(pdu_channel_control_OFF);
  canzero_set_lp_channel9_control(pdu_channel_control_OFF);
  canzero_set_lp_channel10_control(pdu_channel_control_OFF);
  canzero_set_lp_channel11_control(pdu_channel_control_OFF);
  canzero_set_lp_channel12_control(pdu_channel_control_OFF);
  canzero_set_lp_channel13_control(pdu_channel_control_OFF);
  canzero_set_lp_channel14_control(pdu_channel_control_OFF);

  canzero_set_error_mcu_over_temperature(error_flag_OK);
  canzero_set_warn_mcu_over_temperature(error_flag_OK);

  canzero_set_sdc_status(sdc_status_OPEN);
  canzero_set_mcu_temperature(0);
  canzero_set_total_current(0);
  canzero_set_power_estimation(0);

  Serial.begin(38400);

  delay(3000);

  pdu12::begin();

  // initalize

  Timestamp last_error_mcu_over_temp_ok = Timestamp::now();
  Timestamp last_warn_mcu_over_temp_ok = Timestamp::now();

  ExponentialMovingAverage<Temperature> mcu_temp_filter(
      0.1, WARN_MCU_OVER_TEMP - 1_K);

  Timestamp last_iteration = Timestamp::now();

  while (true) {
    Timestamp now = Timestamp::now();
    Duration dt = now - last_iteration;
    last_iteration = now;

    canzero_set_state(pdu_state_RUNNING);

    pdu12::update();

    // reading currents
    canzero_set_lp_channel1_status(to_canzero_status(pdu12::status(lp1)));
    canzero_set_lp_channel2_status(to_canzero_status(pdu12::status(lp2)));
    canzero_set_lp_channel3_status(to_canzero_status(pdu12::status(lp3)));
    canzero_set_lp_channel4_status(to_canzero_status(pdu12::status(lp4)));
    canzero_set_lp_channel5_status(to_canzero_status(pdu12::status(lp5)));
    canzero_set_lp_channel6_status(to_canzero_status(pdu12::status(lp6)));
    canzero_set_lp_channel7_status(to_canzero_status(pdu12::status(lp7)));
    canzero_set_lp_channel8_status(to_canzero_status(pdu12::status(lp8)));
    canzero_set_lp_channel9_status(to_canzero_status(pdu12::status(lp9)));
    canzero_set_lp_channel10_status(to_canzero_status(pdu12::status(lp10)));
    canzero_set_lp_channel11_status(to_canzero_status(pdu12::status(lp11)));
    canzero_set_lp_channel12_status(to_canzero_status(pdu12::status(lp12)));
    canzero_set_lp_channel13_status(to_canzero_status(pdu12::status(lp13)));
    canzero_set_lp_channel14_status(to_canzero_status(pdu12::status(lp13)));

    Current i_lp1 = pdu12::sense(lp1);
    Current i_lp2 = pdu12::sense(lp2);
    Current i_lp3 = pdu12::sense(lp3);
    Current i_lp4 = pdu12::sense(lp4);
    Current i_lp5 = pdu12::sense(lp5);
    Current i_lp6 = pdu12::sense(lp6);
    Current i_lp7 = pdu12::sense(lp7);
    Current i_lp8 = pdu12::sense(lp8);
    Current i_lp9 = pdu12::sense(lp9);
    Current i_lp10 = pdu12::sense(lp10);
    Current i_lp11 = pdu12::sense(lp11);
    Current i_lp12 = pdu12::sense(lp12);
    Current i_lp13 = pdu12::sense(lp13);
    Current i_lp14 = pdu12::sense(lp14);

    Current i_sum = i_lp1 + i_lp2 + i_lp3 + i_lp4 + i_lp5 + i_lp6 + i_lp7 +
                    i_lp8 + i_lp9 + i_lp10 + i_lp11 + i_lp12 + i_lp13 + i_lp14;

    Power p = i_sum * 12_V;

    canzero_set_lp_channel1_current(static_cast<float>(i_lp1));
    canzero_set_lp_channel2_current(static_cast<float>(i_lp2));
    canzero_set_lp_channel3_current(static_cast<float>(i_lp3));
    canzero_set_lp_channel4_current(static_cast<float>(i_lp4));
    canzero_set_lp_channel5_current(static_cast<float>(i_lp5));
    canzero_set_lp_channel6_current(static_cast<float>(i_lp6));
    canzero_set_lp_channel7_current(static_cast<float>(i_lp7));
    canzero_set_lp_channel8_current(static_cast<float>(i_lp8));
    canzero_set_lp_channel9_current(static_cast<float>(i_lp9));
    canzero_set_lp_channel10_current(static_cast<float>(i_lp10));
    canzero_set_lp_channel11_current(static_cast<float>(i_lp11));
    canzero_set_lp_channel12_current(static_cast<float>(i_lp12));
    canzero_set_lp_channel13_current(static_cast<float>(i_lp13));
    canzero_set_lp_channel14_current(static_cast<float>(i_lp14));

    canzero_set_total_current(static_cast<float>(i_sum));
    canzero_set_power_estimation(static_cast<float>(p));

    bool any_short =
        pdu12::status(lp1) == SHORT || pdu12::status(lp2) == SHORT ||
        pdu12::status(lp3) == SHORT || pdu12::status(lp4) == SHORT ||
        pdu12::status(lp5) == SHORT || pdu12::status(lp6) == SHORT ||
        pdu12::status(lp7) == SHORT || pdu12::status(lp8) == SHORT ||
        pdu12::status(lp9) == SHORT || pdu12::status(lp10) == SHORT ||
        pdu12::status(lp11) == SHORT || pdu12::status(lp12) == SHORT ||
        pdu12::status(lp13) == SHORT || pdu12::status(lp14) == SHORT;

    if (any_short) {
      pdu12::control(lp1, false);
      pdu12::control(lp2, false);
      pdu12::control(lp3, false);
      pdu12::control(lp4, false);
      pdu12::control(lp5, false);
      pdu12::control(lp6, false);
      pdu12::control(lp7, false);
      pdu12::control(lp8, false);
      pdu12::control(lp9, false);
      pdu12::control(lp10, false);
      pdu12::control(lp11, false);
      pdu12::control(lp12, false);
      pdu12::control(lp13, false);
      pdu12::control(lp14, false);
    } else {
      // no short
      pdu12::control(lp1, canzero_get_lp_channel1_control() ==
                              pdu_channel_control_ON);
      pdu12::control(lp2, canzero_get_lp_channel2_control() ==
                              pdu_channel_control_ON);
      pdu12::control(lp3, canzero_get_lp_channel3_control() ==
                              pdu_channel_control_ON);
      pdu12::control(lp4, canzero_get_lp_channel4_control() ==
                              pdu_channel_control_ON);
      pdu12::control(lp5, canzero_get_lp_channel5_control() ==
                              pdu_channel_control_ON);
      pdu12::control(lp6, canzero_get_lp_channel6_control() ==
                              pdu_channel_control_ON);
      pdu12::control(lp7, canzero_get_lp_channel7_control() ==
                              pdu_channel_control_ON);
      pdu12::control(lp8, canzero_get_lp_channel8_control() ==
                              pdu_channel_control_ON);
      pdu12::control(lp9, canzero_get_lp_channel9_control() ==
                              pdu_channel_control_ON);
      pdu12::control(lp10, canzero_get_lp_channel10_control() ==
                               pdu_channel_control_ON);
      pdu12::control(lp11, canzero_get_lp_channel11_control() ==
                               pdu_channel_control_ON);
      pdu12::control(lp12, canzero_get_lp_channel12_control() ==
                               pdu_channel_control_ON);
      pdu12::control(lp13, canzero_get_lp_channel13_control() ==
                               pdu_channel_control_ON);
      pdu12::control(lp14, canzero_get_lp_channel14_control() ==
                               pdu_channel_control_ON);
    }

    // mcu temperature measurement
    mcu_temp_filter.push(pdu12::read_mcu_temperature());
    Temperature mcu_temp = mcu_temp_filter.get();

    canzero_set_mcu_temperature(static_cast<float>(mcu_temp) +
                                273.15f); // convertion to °C

    if (mcu_temp > ERROR_MCU_OVER_TEMP) {
      if (Timestamp::now() - last_error_mcu_over_temp_ok >
          ERROR_MCU_OVER_TEMP_TIME_THRESH) {
        canzero_set_error_mcu_over_temperature(error_flag_ERROR);
      }
    } else {
      last_error_mcu_over_temp_ok = Timestamp::now();
      canzero_set_error_mcu_over_temperature(error_flag_OK);
    }

    if (mcu_temp > WARN_MCU_OVER_TEMP) {
      if (Timestamp::now() - last_warn_mcu_over_temp_ok >
          WARN_MCU_OVER_TEMP_TIME_THRESH) {
        canzero_set_warn_mcu_over_temperature(error_flag_ERROR);
      }
    } else {
      last_warn_mcu_over_temp_ok = Timestamp::now();
      canzero_set_warn_mcu_over_temperature(error_flag_OK);
    }

    canzero_can0_poll();
    canzero_can1_poll();
    canzero_update_continue(canzero_get_time());
  }
}

void __assert_func (const char *, int, const char *, const char *) {
  while(true) {
    Serial.println("FUCKED");
  }
}
