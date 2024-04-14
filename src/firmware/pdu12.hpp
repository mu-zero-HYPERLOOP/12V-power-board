

#include "core_pins.h"
#include "util/metrics.h"
#include <Arduino.h>
#include <cmath>

enum pdu12_channel {
  lp1 = 0,
  lp2,
  lp3,
  lp4,
  lp5,
  lp6,
  lp7,
  lp8,
  lp9,
  lp10,
  lp11,
  lp12,
  lp13,
  lp14,
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

private:
  static constexpr size_t CHANNEL_COUNT = 14;
  static constexpr int CHANNEL1_SENSE_PIN = 23;
  static constexpr int CHANNEL1_CTRL_PIN = 2;
  static constexpr int CHANNEL2_SENSE_PIN = 22;
  static constexpr int CHANNEL2_CTRL_PIN = 3;
  static constexpr int CHANNEL3_SENSE_PIN = 21;
  static constexpr int CHANNEL3_CTRL_PIN = 4;
  static constexpr int CHANNEL4_SENSE_PIN = 20;
  static constexpr int CHANNEL4_CTRL_PIN = 5;
  static constexpr int CHANNEL5_SENSE_PIN = 19;
  static constexpr int CHANNEL5_CTRL_PIN = 6;
  static constexpr int CHANNEL6_SENSE_PIN = 18;
  static constexpr int CHANNEL6_CTRL_PIN = 7;
  static constexpr int CHANNEL7_SENSE_PIN = 17;
  static constexpr int CHANNEL7_CTRL_PIN = 8;
  static constexpr int CHANNEL8_SENSE_PIN = 16;
  static constexpr int CHANNEL8_CTRL_PIN = 9;
  static constexpr int CHANNEL9_SENSE_PIN = 15;
  static constexpr int CHANNEL9_CTRL_PIN = 10;
  static constexpr int CHANNEL10_SENSE_PIN = 14;
  static constexpr int CHANNEL10_CTRL_PIN = 11;
  static constexpr int CHANNEL11_SENSE_PIN = 41;
  static constexpr int CHANNEL11_CTRL_PIN = 12;
  static constexpr int CHANNEL12_SENSE_PIN = 40;
  static constexpr int CHANNEL12_CTRL_PIN = 24;
  static constexpr int CHANNEL13_SENSE_PIN = 39;
  static constexpr int CHANNEL13_CTRL_PIN = 25;
  static constexpr int CHANNEL14_SENSE_PIN = 38;
  static constexpr int CHANNEL14_CTRL_PIN = 26;

  static constexpr Resistance R_MEAS = 910_Ohm;
  static constexpr float K_ILIS = 1730.0f;
  static constexpr Voltage SHORT_CIRCUIT_THRESH = 2.5_V;

  static constexpr int SDC_CTRL_PIN = 32;

  static Current m_currents[CHANNEL_COUNT];
  static bool m_shorts[CHANNEL_COUNT];
  static bool m_ctrl[CHANNEL_COUNT];
};
