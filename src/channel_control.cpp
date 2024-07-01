#include "channel_control.h"
#include "canzero/canzero.h"
#include "firmware/pdu12.hpp"
#include "pinout.h"

constexpr size_t DEFAULT_FILTER_LENGTH = 100;
constexpr Frequency DEFAULT_SENSE_FREQUENCY = 1_kHz;

static Interval levitation_boards_sense_interval(DEFAULT_SENSE_FREQUENCY);
static BoxcarFilter<Current, DEFAULT_FILTER_LENGTH>
    levitation_boards_current_filter(0_A);

static Interval guidance_boards_sense_interval(DEFAULT_SENSE_FREQUENCY);
static BoxcarFilter<Current, DEFAULT_FILTER_LENGTH>
    guidance_boards_current_filter(0_A);

static Interval motor_driver_sense_interval(DEFAULT_SENSE_FREQUENCY);
static BoxcarFilter<Current, DEFAULT_FILTER_LENGTH>
    motor_driver_current_filter(0_A);

static Interval input_board_sense_interval(DEFAULT_SENSE_FREQUENCY);
static BoxcarFilter<Current, DEFAULT_FILTER_LENGTH>
    input_board_current_filter(0_A);

static Interval raspberry_pi_sense_interval(DEFAULT_SENSE_FREQUENCY);
static BoxcarFilter<Current, DEFAULT_FILTER_LENGTH>
    raspberry_pi_current_filter(0_A);

static Interval antenna_sense_interval(DEFAULT_SENSE_FREQUENCY);
static BoxcarFilter<Current, DEFAULT_FILTER_LENGTH> antenna_current_filter(0_A);

static Interval led_board_sense_interval(DEFAULT_SENSE_FREQUENCY);
static BoxcarFilter<Current, DEFAULT_FILTER_LENGTH>
    led_board_current_filter(0_A);

static Interval fans_sense_interval(DEFAULT_SENSE_FREQUENCY);
static BoxcarFilter<Current, DEFAULT_FILTER_LENGTH>
    fans_current_filter(0_A);

static Interval power_sense_interval(DEFAULT_SENSE_FREQUENCY);
static BoxcarFilter<Power, DEFAULT_FILTER_LENGTH> total_power_filter(0_W);

static inline pdu_channel_status pdu12_status_to_canzero_status(Pdu12ChannelStatus ch) {
  switch (ch) {
  case ON:
    return pdu_channel_status_ON;
  case OFF:
    return pdu_channel_status_OFF;
  case SHORT:
    return pdu_channel_status_SHORT_CIRCUIT;
  }
}

void channel_control(pdu_12v_state state) {
  switch (state) {
    case pdu_12v_state_CHANNELS_ON:
      pdu12::control(LEVITATION_BOARDS_POWER_CHANNEL, true);
      pdu12::control(GUIDANCE_BOARDS_POWER_CHANNEL, true);
      pdu12::control(MOTOR_DRIVER_POWER_CHANNEL, true);
      pdu12::control(INPUT_BOARD_POWER_CHANNEL, true);
      pdu12::control(RASPBERRY_PI_POWER_CHANNEL, true);
      pdu12::control(ANTENNA_POWER_CHANNEL, true);
      pdu12::control(FANS_POWER_CHANNEL, true);
      pdu12::control(LED_BOARD_CHANNEL, true);
      break;
    case pdu_12v_state_CHANNELS_TELEMETRY:
      pdu12::control(LEVITATION_BOARDS_POWER_CHANNEL, false);
      pdu12::control(GUIDANCE_BOARDS_POWER_CHANNEL, false);
      pdu12::control(MOTOR_DRIVER_POWER_CHANNEL, false);
      pdu12::control(INPUT_BOARD_POWER_CHANNEL, false);
      pdu12::control(RASPBERRY_PI_POWER_CHANNEL, true);
      pdu12::control(ANTENNA_POWER_CHANNEL, true);
      pdu12::control(FANS_POWER_CHANNEL, true);
      pdu12::control(LED_BOARD_CHANNEL, false);
      break;
    case pdu_12v_state_INIT:
    case pdu_12v_state_RESTARTING:
    case pdu_12v_state_CHANNELS_OFF:
      pdu12::control(LEVITATION_BOARDS_POWER_CHANNEL, false);
      pdu12::control(GUIDANCE_BOARDS_POWER_CHANNEL, false);
      pdu12::control(MOTOR_DRIVER_POWER_CHANNEL, false);
      pdu12::control(INPUT_BOARD_POWER_CHANNEL, false);
      pdu12::control(RASPBERRY_PI_POWER_CHANNEL, false);
      pdu12::control(ANTENNA_POWER_CHANNEL, false);
      pdu12::control(FANS_POWER_CHANNEL, false);
      pdu12::control(LED_BOARD_CHANNEL, false);
      break;
    }

  // ====== LEVITATION BOARDS POWER CHANNEL ===========
  if (levitation_boards_sense_interval.next()) {
    levitation_boards_current_filter.push(
        pdu12::sense(LEVITATION_BOARDS_POWER_CHANNEL));
    canzero_set_levitation_boards_power_channel_current(
        static_cast<float>(levitation_boards_current_filter.get()));
  }
  canzero_set_levitation_boards_power_channel_status(
      pdu12_status_to_canzero_status(
          pdu12::status(LEVITATION_BOARDS_POWER_CHANNEL)));

  // ===== GUIDANCE BOARDS POWER CHANNEL ============
  if (guidance_boards_sense_interval.next()) {
    guidance_boards_current_filter.push(
        pdu12::sense(GUIDANCE_BOARDS_POWER_CHANNEL));
    canzero_set_guidance_boards_power_channel_current(
        static_cast<float>(guidance_boards_current_filter.get()));
  }
  canzero_set_guidance_boards_power_channel_status(
      pdu12_status_to_canzero_status(
          pdu12::status(GUIDANCE_BOARDS_POWER_CHANNEL)));

  // ===== MOTOR DRIVER POWER CHANNEL ==============
  if (motor_driver_sense_interval.next()) {
    motor_driver_current_filter.push(pdu12::sense(MOTOR_DRIVER_POWER_CHANNEL));
    canzero_set_motor_driver_power_channel_current(
        static_cast<float>(motor_driver_current_filter.get()));
  }
  canzero_set_motor_driver_power_channel_status(pdu12_status_to_canzero_status(
      pdu12::status(MOTOR_DRIVER_POWER_CHANNEL)));

  // ======= INPUT BOARD POWER CHANNEL =============
  if (input_board_sense_interval.next()) {
    input_board_current_filter.push(pdu12::sense(INPUT_BOARD_POWER_CHANNEL));
    canzero_set_input_board_power_channel_current(
        static_cast<float>(input_board_current_filter.get()));
  }
  canzero_set_input_board_power_channel_status(
      pdu12_status_to_canzero_status(pdu12::status(INPUT_BOARD_POWER_CHANNEL)));

  // ======= RASPBERRY PI POWER CHANNEL ========
  if (raspberry_pi_sense_interval.next()) {
    raspberry_pi_current_filter.push(pdu12::sense(RASPBERRY_PI_POWER_CHANNEL));
    canzero_set_raspberry_pi_power_channel_current(
        static_cast<float>(raspberry_pi_current_filter.get()));
  }
  canzero_set_raspberry_pi_power_channel_status(pdu12_status_to_canzero_status(
      pdu12::status(RASPBERRY_PI_POWER_CHANNEL)));

  // ====== ANTENNA POWER CHANNEL ==============
  if (antenna_sense_interval.next()) {
    antenna_current_filter.push(pdu12::sense(ANTENNA_POWER_CHANNEL));
    canzero_set_antenna_power_channel_current(
        static_cast<float>(antenna_current_filter.get()));
  }
  canzero_set_antenna_power_channel_status(
      pdu12_status_to_canzero_status(pdu12::status(ANTENNA_POWER_CHANNEL)));

  // ======= LED BOARD POWER CHANNEL ===========
  if (led_board_sense_interval.next()) {
    led_board_current_filter.push(pdu12::sense(LED_BOARD_CHANNEL));
    canzero_set_led_board_power_channel_current(
        static_cast<float>(led_board_current_filter.get()));
  }
  canzero_set_led_board_power_channel_status(
      pdu12_status_to_canzero_status(pdu12::status(LED_BOARD_CHANNEL)));

  // ======= COOLING FANS POWER CHANNEL ===========
  if (fans_sense_interval.next()) {
    fans_current_filter.push(pdu12::sense(FANS_POWER_CHANNEL));
    canzero_set_fans_power_channel_current(
        static_cast<float>(fans_current_filter.get()));
  }
  canzero_set_fans_power_channel_status(
      pdu12_status_to_canzero_status(pdu12::status(FANS_POWER_CHANNEL)));

  if (power_sense_interval.next()) {
    total_power_filter.push(pdu12::total_power_output());
    canzero_set_total_power(static_cast<float>(total_power_filter.get()));
  }
}

