#include "pdu12.hpp"
#include "util/metrics.h"
#include <InternalTemperature.h>

Current pdu12::m_currents[CHANNEL_COUNT];
bool pdu12::m_shorts[CHANNEL_COUNT];
bool pdu12::m_ctrl[CHANNEL_COUNT];

void pdu12::begin() {
  // initalize adc and shit
  for (size_t i = 0; i < CHANNEL_COUNT; ++i) {
    m_shorts[i] = false;
    m_currents[i] = 0_A;
    m_ctrl[i] = false;
  }
}

void pdu12::update() {
  // channel1
  {
    uint16_t avalue = analogRead(CHANNEL1_SENSE_PIN);
    Voltage v = Voltage(static_cast<float>(avalue) * 3.3f / 4095.0f);
    if (v > SHORT_CIRCUIT_THRESH) {
      m_currents[lp1] = 0_A;
      m_shorts[lp1] = true;
    } else {
      m_currents[lp1] = (v * K_ILIS) / R_MEAS;
      m_shorts[lp1] = false;
    }
  }
  {
    uint16_t avalue = analogRead(CHANNEL2_SENSE_PIN);
    Voltage v = Voltage(static_cast<float>(avalue) * 3.3f / 4095.0f);
    if (v > SHORT_CIRCUIT_THRESH) {
      m_currents[lp2] = 0_A;
      m_shorts[lp2] = true;
    } else {
      m_currents[lp2] = (v * K_ILIS) / R_MEAS;
      m_shorts[lp2] = false;
    }
  }
  {
    uint16_t avalue = analogRead(CHANNEL3_SENSE_PIN);
    Voltage v = Voltage(static_cast<float>(avalue) * 3.3f / 4095.0f);
    if (v > SHORT_CIRCUIT_THRESH) {
      m_currents[lp3] = 0_A;
      m_shorts[lp3] = true;
    } else {
      m_currents[lp3] = (v * K_ILIS) / R_MEAS;
      m_shorts[lp3] = false;
    }
  }
  {
    uint16_t avalue = analogRead(CHANNEL4_SENSE_PIN);
    Voltage v = Voltage(static_cast<float>(avalue) * 3.3f / 4095.0f);
    if (v > SHORT_CIRCUIT_THRESH) {
      m_currents[lp4] = 0_A;
      m_shorts[lp4] = true;
    } else {
      m_currents[lp4] = (v * K_ILIS) / R_MEAS;
      m_shorts[lp4] = false;
    }
  }
  {
    uint16_t avalue = analogRead(CHANNEL5_SENSE_PIN);
    Voltage v = Voltage(static_cast<float>(avalue) * 3.3f / 4095.0f);
    if (v > SHORT_CIRCUIT_THRESH) {
      m_currents[lp5] = 0_A;
      m_shorts[lp5] = true;
    } else {
      m_currents[lp5] = (v * K_ILIS) / R_MEAS;
      m_shorts[lp5] = false;
    }
  }
  {
    uint16_t avalue = analogRead(CHANNEL6_SENSE_PIN);
    Voltage v = Voltage(static_cast<float>(avalue) * 3.3f / 4095.0f);
    if (v > SHORT_CIRCUIT_THRESH) {
      m_currents[lp6] = 0_A;
      m_shorts[lp6] = true;
    } else {
      m_currents[lp6] = (v * K_ILIS) / R_MEAS;
      m_shorts[lp6] = false;
    }
  }
  {
    uint16_t avalue = analogRead(CHANNEL7_SENSE_PIN);
    Voltage v = Voltage(static_cast<float>(avalue) * 3.3f / 4095.0f);
    if (v > SHORT_CIRCUIT_THRESH) {
      m_currents[lp7] = 0_A;
      m_shorts[lp7] = true;
    } else {
      m_currents[lp7] = (v * K_ILIS) / R_MEAS;
      m_shorts[lp7] = false;
    }
  }
  {
    uint16_t avalue = analogRead(CHANNEL8_SENSE_PIN);
    Voltage v = Voltage(static_cast<float>(avalue) * 3.3f / 4095.0f);
    if (v > SHORT_CIRCUIT_THRESH) {
      m_currents[lp8] = 0_A;
      m_shorts[lp8] = true;
    } else {
      m_currents[lp8] = (v * K_ILIS) / R_MEAS;
      m_shorts[lp8] = false;
    }
  }
  {
    uint16_t avalue = analogRead(CHANNEL9_SENSE_PIN);
    Voltage v = Voltage(static_cast<float>(avalue) * 3.3f / 4095.0f);
    if (v > SHORT_CIRCUIT_THRESH) {
      m_currents[lp9] = 0_A;
      m_shorts[lp9] = true;
    } else {
      m_currents[lp9] = (v * K_ILIS) / R_MEAS;
      m_shorts[lp9] = false;
    }
  }
  {
    uint16_t avalue = analogRead(CHANNEL10_SENSE_PIN);
    Voltage v = Voltage(static_cast<float>(avalue) * 3.3f / 4095.0f);
    if (v > SHORT_CIRCUIT_THRESH) {
      m_currents[lp10] = 0_A;
      m_shorts[lp10] = true;
    } else {
      m_currents[lp10] = (v * K_ILIS) / R_MEAS;
      m_shorts[lp10] = false;
    }
  }
  {
    uint16_t avalue = analogRead(CHANNEL11_SENSE_PIN);
    Voltage v = Voltage(static_cast<float>(avalue) * 3.3f / 4095.0f);
    if (v > SHORT_CIRCUIT_THRESH) {
      m_currents[lp11] = 0_A;
      m_shorts[lp11] = true;
    } else {
      m_currents[lp11] = (v * K_ILIS) / R_MEAS;
      m_shorts[lp11] = false;
    }
  }
  {
    uint16_t avalue = analogRead(CHANNEL12_SENSE_PIN);
    Voltage v = Voltage(static_cast<float>(avalue) * 3.3f / 4095.0f);
    if (v > SHORT_CIRCUIT_THRESH) {
      m_currents[lp12] = 0_A;
      m_shorts[lp12] = true;
    } else {
      m_currents[lp12] = (v * K_ILIS) / R_MEAS;
      m_shorts[lp12] = false;
    }
  }
  {
    uint16_t avalue = analogRead(CHANNEL13_SENSE_PIN);
    Voltage v = Voltage(static_cast<float>(avalue) * 3.3f / 4095.0f);
    if (v > SHORT_CIRCUIT_THRESH) {
      m_currents[lp13] = 0_A;
      m_shorts[lp13] = true;
    } else {
      m_currents[lp13] = (v * K_ILIS) / R_MEAS;
      m_shorts[lp13] = false;
    }
  }
  {
    uint16_t avalue = analogRead(CHANNEL14_SENSE_PIN);
    Voltage v = Voltage(static_cast<float>(avalue) * 3.3f / 4095.0f);
    if (v > SHORT_CIRCUIT_THRESH) {
      m_currents[lp14] = 0_A;
      m_shorts[lp14] = true;
    } else {
      m_currents[lp14] = (v * K_ILIS) / R_MEAS;
      m_shorts[lp14] = false;
    }
  }
  digitalWrite(CHANNEL1_CTRL_PIN, m_ctrl[lp1] && !m_shorts[lp1]);
  digitalWrite(CHANNEL2_CTRL_PIN, m_ctrl[lp2] && !m_shorts[lp2]);
  digitalWrite(CHANNEL3_CTRL_PIN, m_ctrl[lp3] && !m_shorts[lp3]);
  digitalWrite(CHANNEL4_CTRL_PIN, m_ctrl[lp4] && !m_shorts[lp4]);
  digitalWrite(CHANNEL5_CTRL_PIN, m_ctrl[lp5] && !m_shorts[lp5]);
  digitalWrite(CHANNEL6_CTRL_PIN, m_ctrl[lp6] && !m_shorts[lp6]);
  digitalWrite(CHANNEL7_CTRL_PIN, m_ctrl[lp7] && !m_shorts[lp7]);
  digitalWrite(CHANNEL8_CTRL_PIN, m_ctrl[lp8] && !m_shorts[lp8]);
  digitalWrite(CHANNEL9_CTRL_PIN, m_ctrl[lp9] && !m_shorts[lp9]);
  digitalWrite(CHANNEL10_CTRL_PIN, m_ctrl[lp10] && !m_shorts[lp10]);
  digitalWrite(CHANNEL11_CTRL_PIN, m_ctrl[lp11] && !m_shorts[lp11]);
  digitalWrite(CHANNEL12_CTRL_PIN, m_ctrl[lp12] && !m_shorts[lp12]);
  digitalWrite(CHANNEL13_CTRL_PIN, m_ctrl[lp13] && !m_shorts[lp13]);
  digitalWrite(CHANNEL14_CTRL_PIN, m_ctrl[lp14] && !m_shorts[lp14]);
}

Current pdu12::sense(pdu12_channel channel) { return m_currents[channel]; }

pdu12_channel_status pdu12::status(pdu12_channel channel) {
  if (m_shorts[channel]) {
    return SHORT;
  } else {
    return m_ctrl[channel] ? ON : OFF;
  }
}

void pdu12::control(pdu12_channel channel, bool active) {
  m_ctrl[channel] = active;
}

void pdu12::set_sdc(bool closed) { digitalWrite(SDC_CTRL_PIN, closed); }

Temperature pdu12::read_mcu_temperature() {
  float temp = InternalTemperature.readTemperatureC();
  float temp_kelvin = temp - 273.15f;
  return Temperature(temp_kelvin);
}
