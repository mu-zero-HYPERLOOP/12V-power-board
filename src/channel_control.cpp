#include "channel_control.h"

constexpr size_t DEFAULT_FILTER_LENGTH = 10;
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

static inline pdu_channel_status pdu12_status_to_canzero_status(pdu12_channel_status ch) {
  switch (ch) {
  case ON:
    return pdu_channel_status_ON;
  case OFF:
    return pdu_channel_status_OFF;
  case SHORT:
    return pdu_channel_status_SHORT_CIRCUIT;
  }
}

void channel_control() {
  // ====== LEVITATION BOARDS POWER CHANNEL ===========
  pdu12::control(LEVITATION_BOARDS_POWER_CHANNEL,
                 canzero_get_levitation_boards_power_channel_ctrl() ==
                     pdu_channel_control_ON);
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
  pdu12::control(GUIDANCE_BOARDS_POWER_CHANNEL,
                 canzero_get_guidance_boards_power_channel_ctrl() ==
                     pdu_channel_control_ON);
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
  pdu12::control(MOTOR_DRIVER_POWER_CHANNEL,
                 canzero_get_motor_driver_power_channel_ctrl() ==
                     pdu_channel_control_ON);
  if (motor_driver_sense_interval.next()) {
    motor_driver_current_filter.push(pdu12::sense(MOTOR_DRIVER_POWER_CHANNEL));
    canzero_set_motor_driver_power_channel_current(
        static_cast<float>(motor_driver_current_filter.get()));
  }
  canzero_set_motor_driver_power_channel_status(pdu12_status_to_canzero_status(
      pdu12::status(MOTOR_DRIVER_POWER_CHANNEL)));

  // ======= INPUT BOARD POWER CHANNEL =============
  pdu12::control(INPUT_BOARD_POWER_CHANNEL,
                 canzero_get_input_board_power_channel_ctrl() ==
                     pdu_channel_control_ON);
  if (input_board_sense_interval.next()) {
    input_board_current_filter.push(pdu12::sense(INPUT_BOARD_POWER_CHANNEL));
    canzero_set_input_board_power_channel_current(
        static_cast<float>(input_board_current_filter.get()));
  }
  canzero_set_input_board_power_channel_status(
      pdu12_status_to_canzero_status(pdu12::status(INPUT_BOARD_POWER_CHANNEL)));

  // ======= RASPBERRY PI POWER CHANNEL ========
  pdu12::control(RASPBERRY_PI_POWER_CHANNEL,
                 canzero_get_raspberry_pi_power_channel_ctrl() ==
                     pdu_channel_control_ON);
  if (raspberry_pi_sense_interval.next()) {
    raspberry_pi_current_filter.push(pdu12::sense(RASPBERRY_PI_POWER_CHANNEL));
    canzero_set_raspberry_pi_power_channel_current(
        static_cast<float>(raspberry_pi_current_filter.get()));
  }
  canzero_set_raspberry_pi_power_channel_status(pdu12_status_to_canzero_status(
      pdu12::status(RASPBERRY_PI_POWER_CHANNEL)));

  // ====== ANTENNA POWER CHANNEL ==============
  pdu12::control(ANTENNA_POWER_CHANNEL,
                 canzero_get_antenna_power_channel_ctrl() ==
                     pdu_channel_control_ON);
  if (antenna_sense_interval.next()) {
    antenna_current_filter.push(pdu12::sense(ANTENNA_POWER_CHANNEL));
    canzero_set_antenna_power_channel_current(
        static_cast<float>(antenna_current_filter.get()));
  }
  canzero_set_antenna_power_channel_status(
      pdu12_status_to_canzero_status(pdu12::status(ANTENNA_POWER_CHANNEL)));

  // ======= LED BOARD POWER CHANNEL ===========
  pdu12::control(LED_BOARD_CHANNEL,
                 canzero_get_led_board_power_channel_ctrl() ==
                     pdu_channel_control_ON);
  if (led_board_sense_interval.next()) {
    led_board_current_filter.push(pdu12::sense(LED_BOARD_CHANNEL));
    canzero_set_led_board_power_channel_current(
        static_cast<float>(led_board_current_filter.get()));
  }
  canzero_set_led_board_power_channel_status(
      pdu12_status_to_canzero_status(pdu12::status(LED_BOARD_CHANNEL)));
}

