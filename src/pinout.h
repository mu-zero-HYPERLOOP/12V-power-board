#pragma once

#include "firmware/pdu12.hpp"

//purple
constexpr Pdu12Channel LEVITATION_BOARDS_POWER_CHANNEL = lp_2_23;

//purple
constexpr Pdu12Channel GUIDANCE_BOARDS_POWER_CHANNEL = lp_4_21;

//white
constexpr Pdu12Channel MOTOR_DRIVER_POWER_CHANNEL = lp_5_20;

//yellow
constexpr Pdu12Channel INPUT_BOARD_POWER_CHANNEL = lp_6_19;

//green
constexpr Pdu12Channel RASPBERRY_PI_POWER_CHANNEL = lp_7_18;

//brown
constexpr Pdu12Channel ANTENNA_POWER_CHANNEL = lp_8_17;

//grey
constexpr Pdu12Channel FANS_POWER_CHANNEL = lp_9_16;

// wtf
constexpr Pdu12Channel LED_BOARD_CHANNEL = lp_10_15;
