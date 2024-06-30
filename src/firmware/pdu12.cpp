#include "pdu12.hpp"
#include "canzero/canzero.h"
#include "core_pins.h"
#include "print.h"
#include "util/metrics.h"
#include "util/timestamp.h"
#include <InternalTemperature.h>
#include <algorithm>
#include <numeric>

std::array<Current, CHANNEL_COUNT> pdu12::m_currents;
std::array<bool, CHANNEL_COUNT> pdu12::m_shorts;
std::array<bool, CHANNEL_COUNT> pdu12::m_ctrl;
std::array<Timestamp, CHANNEL_COUNT> pdu12::m_last_channel_ok;

void pdu12::begin() {
  // initalize adc and shit
  const auto now = Timestamp::now();
  for (size_t i = 0; i < CHANNEL_COUNT; ++i) {
    m_shorts[i] = false;
    m_currents[i] = 0_A;
    m_ctrl[i] = false;
    m_last_channel_ok[i] = now;
  }
  pinMode(SDC_CTRL_PIN, OUTPUT);
  
  pinMode(CHANNEL_2_23_CTRL_PIN, OUTPUT);
  pinMode(CHANNEL_3_22_CTRL_PIN, OUTPUT);
  pinMode(CHANNEL_4_21_CTRL_PIN, OUTPUT);
  pinMode(CHANNEL_5_20_CTRL_PIN, OUTPUT);
  pinMode(CHANNEL_6_19_CTRL_PIN, OUTPUT);
  pinMode(CHANNEL_7_18_CTRL_PIN, OUTPUT);
  pinMode(CHANNEL_8_17_CTRL_PIN, OUTPUT);
  pinMode(CHANNEL_9_16_CTRL_PIN, OUTPUT);
  pinMode(CHANNEL_10_15_CTRL_PIN, OUTPUT);
  pinMode(CHANNEL_11_14_CTRL_PIN, OUTPUT);
  pinMode(CHANNEL_12_41_CTRL_PIN, OUTPUT);
  pinMode(CHANNEL_24_40_CTRL_PIN, OUTPUT);
  pinMode(CHANNEL_25_39_CTRL_PIN, OUTPUT);
  pinMode(CHANNEL_26_38_CTRL_PIN, OUTPUT);

  pinMode(CHANNEL_2_23_SENSE_PIN, INPUT);
  pinMode(CHANNEL_3_22_SENSE_PIN, INPUT);
  pinMode(CHANNEL_4_21_SENSE_PIN, INPUT);
  pinMode(CHANNEL_5_20_SENSE_PIN, INPUT);
  pinMode(CHANNEL_6_19_SENSE_PIN, INPUT);
  pinMode(CHANNEL_7_18_SENSE_PIN, INPUT);
  pinMode(CHANNEL_8_17_SENSE_PIN, INPUT);
  pinMode(CHANNEL_9_16_SENSE_PIN, INPUT);
  pinMode(CHANNEL_10_15_SENSE_PIN, INPUT);
  pinMode(CHANNEL_11_14_SENSE_PIN, INPUT);
  pinMode(CHANNEL_12_41_SENSE_PIN, INPUT);
  pinMode(CHANNEL_24_40_SENSE_PIN, INPUT);
  pinMode(CHANNEL_25_39_SENSE_PIN, INPUT);
  pinMode(CHANNEL_26_38_SENSE_PIN, INPUT);

  analogReadResolution(12);
}

void pdu12::update() {
  const auto now = Timestamp::now();
  {
    uint16_t avalue = analogRead(CHANNEL_2_23_SENSE_PIN);
    Voltage v = Voltage(static_cast<float>(avalue) * 3.3f / 4095.0f);
    m_currents[lp_2_23] = (v * K_ILIS) / R_MEAS;
  }
  {
    uint16_t avalue = analogRead(CHANNEL_3_22_SENSE_PIN);
    Voltage v = Voltage(static_cast<float>(avalue) * 3.3f / 4095.0f);
    m_currents[lp_3_22] = (v * K_ILIS) / R_MEAS;
  }
  {
    uint16_t avalue = analogRead(CHANNEL_4_21_SENSE_PIN);
    Voltage v = Voltage(static_cast<float>(avalue) * 3.3f / 4095.0f);
    m_currents[lp_4_21] = (v * K_ILIS) / R_MEAS;
  }
  {
    uint16_t avalue = analogRead(CHANNEL_5_20_SENSE_PIN);
    Voltage v = Voltage(static_cast<float>(avalue) * 3.3f / 4095.0f);
    m_currents[lp_5_20] = (v * K_ILIS) / R_MEAS;
  }
  {
    uint16_t avalue = analogRead(CHANNEL_6_19_SENSE_PIN);
    Voltage v = Voltage(static_cast<float>(avalue) * 3.3f / 4095.0f);
    m_currents[lp_6_19] = (v * K_ILIS) / R_MEAS;
  }
  {
    uint16_t avalue = analogRead(CHANNEL_7_18_SENSE_PIN);
    Voltage v = Voltage(static_cast<float>(avalue) * 3.3f / 4095.0f);
    m_currents[lp_7_18] = (v * K_ILIS) / R_MEAS;
  }
  {
    uint16_t avalue = analogRead(CHANNEL_8_17_SENSE_PIN);
    Voltage v = Voltage(static_cast<float>(avalue) * 3.3f / 4095.0f);
    m_currents[lp_8_17] = (v * K_ILIS) / R_MEAS;
  }
  {
    uint16_t avalue = analogRead(CHANNEL_9_16_SENSE_PIN);
    Voltage v = Voltage(static_cast<float>(avalue) * 3.3f / 4095.0f);
    m_currents[lp_9_16] = (v * K_ILIS) / R_MEAS;
  }
  {
    uint16_t avalue = analogRead(CHANNEL_10_15_SENSE_PIN);
    Voltage v = Voltage(static_cast<float>(avalue) * 3.3f / 4095.0f);
    m_currents[lp_10_15] = (v * K_ILIS) / R_MEAS;
  }
  {
    uint16_t avalue = analogRead(CHANNEL_11_14_SENSE_PIN);
    Voltage v = Voltage(static_cast<float>(avalue) * 3.3f / 4095.0f);
    m_currents[lp_11_14] = (v * K_ILIS) / R_MEAS;
  }
  {
    uint16_t avalue = analogRead(CHANNEL_12_41_SENSE_PIN);
    Voltage v = Voltage(static_cast<float>(avalue) * 3.3f / 4095.0f);
    m_currents[lp_12_41] = (v * K_ILIS) / R_MEAS;
  }
  {
    uint16_t avalue = analogRead(CHANNEL_24_40_SENSE_PIN);
    Voltage v = Voltage(static_cast<float>(avalue) * 3.3f / 4095.0f);
    m_currents[lp_24_40] = (v * K_ILIS) / R_MEAS;
  }
  {
    uint16_t avalue = analogRead(CHANNEL_25_39_SENSE_PIN);
    Voltage v = Voltage(static_cast<float>(avalue) * 3.3f / 4095.0f);
    m_currents[lp_25_39] = (v * K_ILIS) / R_MEAS;
  }
  {
    uint16_t avalue = analogRead(CHANNEL_26_38_SENSE_PIN);
    Voltage v = Voltage(static_cast<float>(avalue) * 3.3f / 4095.0f);
    m_currents[lp_26_38] = (v * K_ILIS) / R_MEAS;
  }


  for (unsigned int channel = 0; channel < CHANNEL_COUNT; ++channel) {
    if (m_currents[channel] < SHORT_CIRCUIT_THRESH || !m_ctrl[channel]) {
      m_last_channel_ok[channel] = now;
    }
    if (now - m_last_channel_ok[channel] > SHORT_CIRCUIT_TIMETRESH){
      m_shorts[channel] = true;
    }
    if (m_shorts[channel]) {
      m_currents[channel] = 0_A;
    }
  }

  digitalWrite(CHANNEL_2_23_CTRL_PIN, m_ctrl[lp_2_23] || m_shorts[lp_2_23]);
  digitalWrite(CHANNEL_3_22_CTRL_PIN, m_ctrl[lp_3_22] || m_shorts[lp_3_22]);
  digitalWrite(CHANNEL_4_21_CTRL_PIN, m_ctrl[lp_4_21] || m_shorts[lp_4_21]);
  digitalWrite(CHANNEL_5_20_CTRL_PIN, m_ctrl[lp_5_20] || m_shorts[lp_5_20]);
  digitalWrite(CHANNEL_6_19_CTRL_PIN, m_ctrl[lp_6_19] || m_shorts[lp_6_19]);
  digitalWrite(CHANNEL_7_18_CTRL_PIN, m_ctrl[lp_7_18] || m_shorts[lp_7_18]);
  digitalWrite(CHANNEL_8_17_CTRL_PIN, m_ctrl[lp_8_17] || m_shorts[lp_8_17]);
  digitalWrite(CHANNEL_9_16_CTRL_PIN, m_ctrl[lp_9_16] || m_shorts[lp_9_16]);
  digitalWrite(CHANNEL_10_15_CTRL_PIN, m_ctrl[lp_10_15] || m_shorts[lp_10_15]);
  digitalWrite(CHANNEL_11_14_CTRL_PIN, m_ctrl[lp_11_14] || m_shorts[lp_11_14]);
  digitalWrite(CHANNEL_12_41_CTRL_PIN, m_ctrl[lp_12_41] || m_shorts[lp_12_41]);
  digitalWrite(CHANNEL_24_40_CTRL_PIN, m_ctrl[lp_24_40] || m_shorts[lp_24_40]);
  digitalWrite(CHANNEL_25_39_CTRL_PIN, m_ctrl[lp_25_39] || m_shorts[lp_25_39]);
  digitalWrite(CHANNEL_26_38_CTRL_PIN, m_ctrl[lp_26_38] || m_shorts[lp_26_38]);
}

Current pdu12::sense(Pdu12Channel channel) { return m_currents[channel]; }

Pdu12ChannelStatus pdu12::status(Pdu12Channel channel) {
  if (m_shorts[channel]) {
    return SHORT;
  } else {
    return m_ctrl[channel] ? ON : OFF;
  }
}

void pdu12::control(Pdu12Channel channel, bool active) {
  m_ctrl[channel] = active;
}

void pdu12::set_sdc(bool close) { 
  digitalWrite(SDC_CTRL_PIN, close); 
}

Temperature pdu12::read_mcu_temperature() {
  float temp = InternalTemperature.readTemperatureC();
  float temp_kelvin = temp - 273.15f;
  return Temperature(temp_kelvin);
}

bool pdu12::any_short() {
  return std::any_of(m_shorts.begin(), m_shorts.end(),
                     [](auto x) { return x; });
}

Power pdu12::total_power_output() {
  return std::accumulate(
      m_currents.begin(), m_currents.end(), Power(0),
      [](Power p, Current c) { return p + Voltage(12) * c; });
}
