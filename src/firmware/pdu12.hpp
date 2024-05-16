#pragma once

#include "util/metrics.h"
#include <cmath>
#include <array>

enum pdu12_channel {
  lp_2_23 = 0,
  lp_3_22,
  lp_4_21,
  lp_5_20,
  lp_6_19,
  lp_7_18,
  lp_8_17,
  lp_9_16,
  lp_10_15,
  lp_11_14,
  lp_12_41,
  lp_24_40,
  lp_25_39,
  lp_26_38,
  CHANNEL_COUNT,
};

enum pdu12_channel_status {
  OFF,
  ON,
  SHORT,
};

class pdu12 {
public:
  static void begin();

  static void update();

  static Current sense(pdu12_channel channel);

  static pdu12_channel_status status(pdu12_channel channel);

  static void control(pdu12_channel channel, bool active);

  static void set_sdc(bool closed);

  static Temperature read_mcu_temperature();

  static bool any_short();

private:
  static constexpr int CHANNEL_2_23_SENSE_PIN = 23;
  static constexpr int CHANNEL_2_23_CTRL_PIN = 2;
  static constexpr int CHANNEL_3_22_SENSE_PIN = 22;
  static constexpr int CHANNEL_3_22_CTRL_PIN = 3;
  static constexpr int CHANNEL_4_21_SENSE_PIN = 21;
  static constexpr int CHANNEL_4_21_CTRL_PIN = 4;
  static constexpr int CHANNEL_5_20_SENSE_PIN = 20;
  static constexpr int CHANNEL_5_20_CTRL_PIN = 5;
  static constexpr int CHANNEL_6_19_SENSE_PIN = 19;
  static constexpr int CHANNEL_6_19_CTRL_PIN = 6;
  static constexpr int CHANNEL_7_18_SENSE_PIN = 18;
  static constexpr int CHANNEL_7_18_CTRL_PIN = 7;
  static constexpr int CHANNEL_8_17_SENSE_PIN = 17;
  static constexpr int CHANNEL_8_17_CTRL_PIN = 8;
  static constexpr int CHANNEL_9_16_SENSE_PIN = 16;
  static constexpr int CHANNEL_6_16_CTRL_PIN = 9;
  static constexpr int CHANNEL_10_15_SENSE_PIN = 15;
  static constexpr int CHANNEL_10_15_CTRL_PIN = 10;
  static constexpr int CHANNEL_11_14_SENSE_PIN = 14;
  static constexpr int CHANNEL_11_14_CTRL_PIN = 11;
  static constexpr int CHANNEL_12_41_SENSE_PIN = 41;
  static constexpr int CHANNEL_12_41_CTRL_PIN = 12;
  static constexpr int CHANNEL_24_40_SENSE_PIN = 40;
  static constexpr int CHANNEL_24_40_CTRL_PIN = 24;
  static constexpr int CHANNEL_25_39_SENSE_PIN = 39;
  static constexpr int CHANNEL_25_39_CTRL_PIN = 25;
  static constexpr int CHANNEL_26_38_SENSE_PIN = 38;
  static constexpr int CHANNEL_26_38_CTRL_PIN = 26;

  static constexpr Resistance R_MEAS = 910_Ohm;
  static constexpr float K_ILIS = 1730.0f;
  static constexpr Current SHORT_CIRCUIT_THRESH = 5_A;

  static constexpr int SDC_CTRL_PIN = 32;

  static std::array<Current, CHANNEL_COUNT> m_currents;
  static std::array<bool, CHANNEL_COUNT> m_shorts;
  static std::array<bool, CHANNEL_COUNT> m_ctrl;
};
