
#include "canzero/canzero.h"
#include "firmware/pdu12.hpp"
#include "util/metrics.h"
#include <algorithm>
#include <array>
#include <random>

std::array<Current, CHANNEL_COUNT> pdu12::m_currents;
std::array<bool, CHANNEL_COUNT> pdu12::m_shorts;
std::array<bool, CHANNEL_COUNT> pdu12::m_ctrl;


static std::random_device rd{};
static std::mt19937 gen{rd()};

static std::normal_distribution current_dist{1.0f, 0.05f};

static std::normal_distribution temp_dist{30.0f, 0.5f};

void pdu12::begin() {
  for (size_t i = 0; i < CHANNEL_COUNT; ++i) {
    m_shorts[i] = false;
    m_currents[i] = 0_A;
    m_ctrl[i] = false;
  }
}

void pdu12::update() { }

Current pdu12::sense(Pdu12Channel channel) {
  if (m_ctrl[channel]) {
    return Current(current_dist(gen));
  }else {
    return 0_A;
  }
}

Pdu12ChannelStatus pdu12::status(Pdu12Channel channel) {
  return m_ctrl[channel] ? ON : OFF;
}

void pdu12::control(Pdu12Channel channel, bool active) {
  m_ctrl[channel] = active;
}

void pdu12::set_sdc(bool closed) { 
}

Temperature pdu12::read_mcu_temperature() {
  float celcius = temp_dist(gen);
  return Temperature(celcius - 273.15);
}

bool pdu12::any_short() {
  return std::any_of(m_shorts.begin(), m_shorts.end(),
                     [](auto x) { return x; });
}

Power pdu12::total_power_output() {
  return std::accumulate(m_currents.begin(), m_currents.end(), Power(0), 
      [](Power p, Current c) { return p + Voltage(12) * c; });
}
