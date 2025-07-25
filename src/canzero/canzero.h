#ifndef CANZERO_H
#define CANZERO_H
#include <cinttypes>
#include <cstddef>
#define MAX_DYN_HEARTBEATS 10
typedef enum {
  node_id_gamepad = 0,
  node_id_telemetry_board = 1,
  node_id_motor_driver = 2,
  node_id_input_board = 3,
  node_id_guidance_board_front = 4,
  node_id_guidance_board_back = 5,
  node_id_levitation_board1 = 6,
  node_id_levitation_board2 = 7,
  node_id_levitation_board3 = 8,
  node_id_power_board12 = 9,
  node_id_power_board24 = 10,
  node_id_led_board = 11,
  node_id_count = 12,
} node_id;
typedef struct {
  uint16_t m_od_index;
  uint8_t m_client_id;
  uint8_t m_server_id;
} get_req_header;
typedef struct {
  uint8_t m_sof;
  uint8_t m_eof;
  uint8_t m_toggle;
  uint16_t m_od_index;
  uint8_t m_client_id;
  uint8_t m_server_id;
} set_req_header;
typedef enum {
  pdu_12v_command_NONE = 0,
  pdu_12v_command_START = 1,
  pdu_12v_command_STOP = 2,
  pdu_12v_command_TELEMETRY = 3,
  pdu_12v_command_RESTART = 4,
} pdu_12v_command;
typedef struct {
  uint8_t m_sof;
  uint8_t m_eof;
  uint8_t m_toggle;
  uint16_t m_od_index;
  uint8_t m_client_id;
  uint8_t m_server_id;
} get_resp_header;
typedef enum {
  set_resp_erno_Success = 0,
  set_resp_erno_Error = 1,
} set_resp_erno;
typedef struct {
  uint16_t m_od_index;
  uint8_t m_client_id;
  uint8_t m_server_id;
  set_resp_erno m_erno;
} set_resp_header;
typedef enum {
  pdu_12v_state_INIT = 0,
  pdu_12v_state_CHANNELS_OFF = 1,
  pdu_12v_state_CHANNELS_TELEMETRY = 2,
  pdu_12v_state_CHANNELS_ON = 3,
  pdu_12v_state_RESTARTING = 4,
} pdu_12v_state;
typedef enum {
  sdc_status_OPEN = 0,
  sdc_status_CLOSED = 1,
} sdc_status;
typedef enum {
  error_flag_OK = 0,
  error_flag_ERROR = 1,
} error_flag;
typedef enum {
  error_level_OK = 0,
  error_level_INFO = 1,
  error_level_WARNING = 2,
  error_level_ERROR = 3,
} error_level;
typedef enum {
  pdu_channel_status_OFF = 0,
  pdu_channel_status_ON = 1,
  pdu_channel_status_SHORT_CIRCUIT = 3,
} pdu_channel_status;
typedef struct {
  uint16_t m_year;
  uint8_t m_month;
  uint8_t m_day;
  uint8_t m_hour;
  uint8_t m_min;
  uint8_t m_sec;
} date_time;
typedef enum {
  bool_t_FALSE = 0,
  bool_t_TRUE = 1,
} bool_t;
typedef struct {
  float m_info_thresh;
  float m_info_timeout;
  float m_warning_thresh;
  float m_warning_timeout;
  float m_error_thresh;
  float m_error_timeout;
  bool_t m_ignore_info;
  bool_t m_ignore_warning;
  bool_t m_ignore_error;
} error_level_config;
static const node_id CANZERO_NODE_ID = node_id_power_board12;
typedef struct {
  uint32_t id;
  uint8_t dlc;
  __attribute__((aligned(alignof(uint64_t)))) uint8_t data[8];
} canzero_frame;
typedef enum : uint32_t {
  CANZERO_FRAME_IDE_BIT = 0x40000000, // 1 << 30
  CANZERO_FRAME_RTR_BIT = 0x80000000, // 1 << 31
} can_frame_id_bits;
typedef struct {
  uint32_t mask;
  uint32_t id;
} canzero_can_filter;
extern void canzero_can0_setup(uint32_t baudrate, canzero_can_filter* filters, int filter_count);
extern void canzero_can0_send(canzero_frame* frame);
extern int canzero_can0_recv(canzero_frame* frame);
extern void canzero_can1_setup(uint32_t baudrate, canzero_can_filter* filters, int filter_count);
extern void canzero_can1_send(canzero_frame* frame);
extern int canzero_can1_recv(canzero_frame* frame);
extern void canzero_request_update(uint32_t time);
extern uint32_t canzero_get_time();
extern void canzero_enter_critical();
extern void canzero_exit_critical();
static inline uint64_t canzero_get_config_hash() {
  extern uint64_t __oe_config_hash;
  return __oe_config_hash;
}
static inline date_time canzero_get_build_time() {
  extern date_time __oe_build_time;
  return __oe_build_time;
}
static inline pdu_12v_state canzero_get_state() {
  extern pdu_12v_state __oe_state;
  return __oe_state;
}
static inline sdc_status canzero_get_sdc_status() {
  extern sdc_status __oe_sdc_status;
  return __oe_sdc_status;
}
static inline error_flag canzero_get_assertion_fault() {
  extern error_flag __oe_assertion_fault;
  return __oe_assertion_fault;
}
static inline error_flag canzero_get_error_any_short() {
  extern error_flag __oe_error_any_short;
  return __oe_error_any_short;
}
static inline error_flag canzero_get_error_heartbeat_miss() {
  extern error_flag __oe_error_heartbeat_miss;
  return __oe_error_heartbeat_miss;
}
static inline error_level canzero_get_error_level_mcu_temperature() {
  extern error_level __oe_error_level_mcu_temperature;
  return __oe_error_level_mcu_temperature;
}
static inline pdu_12v_command canzero_get_command() {
  extern pdu_12v_command __oe_command;
  return __oe_command;
}
static inline double canzero_get_loop_frequency() {
  extern double __oe_loop_frequency;
  return __oe_loop_frequency;
}
static inline float canzero_get_levitation_boards_power_channel_current() {
  extern float __oe_levitation_boards_power_channel_current;
  return __oe_levitation_boards_power_channel_current;
}
static inline pdu_channel_status canzero_get_levitation_boards_power_channel_status() {
  extern pdu_channel_status __oe_levitation_boards_power_channel_status;
  return __oe_levitation_boards_power_channel_status;
}
static inline float canzero_get_guidance_boards_power_channel_current() {
  extern float __oe_guidance_boards_power_channel_current;
  return __oe_guidance_boards_power_channel_current;
}
static inline pdu_channel_status canzero_get_guidance_boards_power_channel_status() {
  extern pdu_channel_status __oe_guidance_boards_power_channel_status;
  return __oe_guidance_boards_power_channel_status;
}
static inline float canzero_get_motor_driver_power_channel_current() {
  extern float __oe_motor_driver_power_channel_current;
  return __oe_motor_driver_power_channel_current;
}
static inline pdu_channel_status canzero_get_motor_driver_power_channel_status() {
  extern pdu_channel_status __oe_motor_driver_power_channel_status;
  return __oe_motor_driver_power_channel_status;
}
static inline float canzero_get_input_board_power_channel_current() {
  extern float __oe_input_board_power_channel_current;
  return __oe_input_board_power_channel_current;
}
static inline pdu_channel_status canzero_get_input_board_power_channel_status() {
  extern pdu_channel_status __oe_input_board_power_channel_status;
  return __oe_input_board_power_channel_status;
}
static inline float canzero_get_raspberry_pi_power_channel_current() {
  extern float __oe_raspberry_pi_power_channel_current;
  return __oe_raspberry_pi_power_channel_current;
}
static inline pdu_channel_status canzero_get_raspberry_pi_power_channel_status() {
  extern pdu_channel_status __oe_raspberry_pi_power_channel_status;
  return __oe_raspberry_pi_power_channel_status;
}
static inline float canzero_get_antenna_power_channel_current() {
  extern float __oe_antenna_power_channel_current;
  return __oe_antenna_power_channel_current;
}
static inline pdu_channel_status canzero_get_antenna_power_channel_status() {
  extern pdu_channel_status __oe_antenna_power_channel_status;
  return __oe_antenna_power_channel_status;
}
static inline float canzero_get_led_board_power_channel_current() {
  extern float __oe_led_board_power_channel_current;
  return __oe_led_board_power_channel_current;
}
static inline pdu_channel_status canzero_get_led_board_power_channel_status() {
  extern pdu_channel_status __oe_led_board_power_channel_status;
  return __oe_led_board_power_channel_status;
}
static inline float canzero_get_fans_power_channel_current() {
  extern float __oe_fans_power_channel_current;
  return __oe_fans_power_channel_current;
}
static inline pdu_channel_status canzero_get_fans_power_channel_status() {
  extern pdu_channel_status __oe_fans_power_channel_status;
  return __oe_fans_power_channel_status;
}
static inline uint8_t canzero_get_last_node_missed() {
  extern uint8_t __oe_last_node_missed;
  return __oe_last_node_missed;
}
static inline float canzero_get_mcu_temperature() {
  extern float __oe_mcu_temperature;
  return __oe_mcu_temperature;
}
static inline error_flag canzero_get_error_mcu_temperature_invalid() {
  extern error_flag __oe_error_mcu_temperature_invalid;
  return __oe_error_mcu_temperature_invalid;
}
static inline error_level_config canzero_get_error_level_config_mcu_temperature() {
  extern error_level_config __oe_error_level_config_mcu_temperature;
  return __oe_error_level_config_mcu_temperature;
}
static inline float canzero_get_total_power() {
  extern float __oe_total_power;
  return __oe_total_power;
}
typedef struct {
  get_resp_header m_header;
  uint32_t m_data;
} canzero_message_get_resp;
static const uint32_t canzero_message_get_resp_id = 0x13D;
typedef struct {
  set_resp_header m_header;
} canzero_message_set_resp;
static const uint32_t canzero_message_set_resp_id = 0x15D;
typedef struct {
  pdu_12v_state m_state;
  sdc_status m_sdc_status;
} canzero_message_power_board12_stream_state;
static const uint32_t canzero_message_power_board12_stream_state_id = 0x90;
typedef struct {
  uint64_t m_config_hash;
} canzero_message_power_board12_stream_config_hash;
static const uint32_t canzero_message_power_board12_stream_config_hash_id = 0x50;
typedef struct {
  error_flag m_assertion_fault;
  error_flag m_error_any_short;
  error_flag m_error_heartbeat_miss;
  error_level m_error_level_mcu_temperature;
  error_flag m_error_mcu_temperature_invalid;
  uint8_t m_last_node_missed;
} canzero_message_power_board12_stream_errors;
static const uint32_t canzero_message_power_board12_stream_errors_id = 0x70;
typedef struct {
  float m_mcu_temperature;
} canzero_message_power_board12_stream_temperature;
static const uint32_t canzero_message_power_board12_stream_temperature_id = 0xD5;
typedef struct {
  pdu_channel_status m_levitation_boards_power_channel_status;
  pdu_channel_status m_guidance_boards_power_channel_status;
  pdu_channel_status m_motor_driver_power_channel_status;
  pdu_channel_status m_input_board_power_channel_status;
  pdu_channel_status m_raspberry_pi_power_channel_status;
  pdu_channel_status m_antenna_power_channel_status;
  pdu_channel_status m_led_board_power_channel_status;
} canzero_message_power_board12_stream_channel_status;
static const uint32_t canzero_message_power_board12_stream_channel_status_id = 0x95;
typedef struct {
  float m_raspberry_pi_power_channel_current;
  float m_antenna_power_channel_current;
  float m_led_board_power_channel_current;
  float m_levitation_boards_power_channel_current;
  float m_guidance_boards_power_channel_current;
  float m_motor_driver_power_channel_current;
  float m_input_board_power_channel_current;
  float m_fans_power_channel_current;
} canzero_message_power_board12_stream_channel_currents;
static const uint32_t canzero_message_power_board12_stream_channel_currents_id = 0x75;
typedef struct {
  float m_total_power;
} canzero_message_power_board12_stream_power_consumption;
static const uint32_t canzero_message_power_board12_stream_power_consumption_id = 0xB5;
typedef struct {
  uint8_t m_node_id;
  uint8_t m_unregister;
  uint8_t m_ticks_next;
} canzero_message_heartbeat_can0;
static const uint32_t canzero_message_heartbeat_can0_id = 0x16F;
typedef struct {
  uint8_t m_node_id;
  uint8_t m_unregister;
  uint8_t m_ticks_next;
} canzero_message_heartbeat_can1;
static const uint32_t canzero_message_heartbeat_can1_id = 0x16E;
typedef struct {
  get_req_header m_header;
} canzero_message_get_req;
static const uint32_t canzero_message_get_req_id = 0x13E;
typedef struct {
  set_req_header m_header;
  uint32_t m_data;
} canzero_message_set_req;
static const uint32_t canzero_message_set_req_id = 0x15E;
typedef struct {
  pdu_12v_command m_power_board12_command;
} canzero_message_input_board_stream_pdu_12v_command;
static const uint32_t canzero_message_input_board_stream_pdu_12v_command_id = 0x48;
void canzero_can0_poll();
void canzero_can1_poll();
uint32_t canzero_update_continue(uint32_t delta_time);
void canzero_init();
void canzero_set_config_hash(uint64_t value);

static inline void canzero_set_build_time(date_time value){
  extern date_time __oe_build_time;
  __oe_build_time = value;
}

void canzero_set_state(pdu_12v_state value);

void canzero_set_sdc_status(sdc_status value);

void canzero_set_assertion_fault(error_flag value);

void canzero_set_error_any_short(error_flag value);

void canzero_set_error_heartbeat_miss(error_flag value);

void canzero_set_error_level_mcu_temperature(error_level value);

static inline void canzero_set_command(pdu_12v_command value){
  extern pdu_12v_command __oe_command;
  __oe_command = value;
}

static inline void canzero_set_loop_frequency(double value){
  extern double __oe_loop_frequency;
  __oe_loop_frequency = value;
}

static inline void canzero_set_levitation_boards_power_channel_current(float value){
  extern float __oe_levitation_boards_power_channel_current;
  __oe_levitation_boards_power_channel_current = value;
}

void canzero_set_levitation_boards_power_channel_status(pdu_channel_status value);

static inline void canzero_set_guidance_boards_power_channel_current(float value){
  extern float __oe_guidance_boards_power_channel_current;
  __oe_guidance_boards_power_channel_current = value;
}

void canzero_set_guidance_boards_power_channel_status(pdu_channel_status value);

static inline void canzero_set_motor_driver_power_channel_current(float value){
  extern float __oe_motor_driver_power_channel_current;
  __oe_motor_driver_power_channel_current = value;
}

void canzero_set_motor_driver_power_channel_status(pdu_channel_status value);

static inline void canzero_set_input_board_power_channel_current(float value){
  extern float __oe_input_board_power_channel_current;
  __oe_input_board_power_channel_current = value;
}

void canzero_set_input_board_power_channel_status(pdu_channel_status value);

static inline void canzero_set_raspberry_pi_power_channel_current(float value){
  extern float __oe_raspberry_pi_power_channel_current;
  __oe_raspberry_pi_power_channel_current = value;
}

void canzero_set_raspberry_pi_power_channel_status(pdu_channel_status value);

static inline void canzero_set_antenna_power_channel_current(float value){
  extern float __oe_antenna_power_channel_current;
  __oe_antenna_power_channel_current = value;
}

void canzero_set_antenna_power_channel_status(pdu_channel_status value);

static inline void canzero_set_led_board_power_channel_current(float value){
  extern float __oe_led_board_power_channel_current;
  __oe_led_board_power_channel_current = value;
}

void canzero_set_led_board_power_channel_status(pdu_channel_status value);

static inline void canzero_set_fans_power_channel_current(float value){
  extern float __oe_fans_power_channel_current;
  __oe_fans_power_channel_current = value;
}

static inline void canzero_set_fans_power_channel_status(pdu_channel_status value){
  extern pdu_channel_status __oe_fans_power_channel_status;
  __oe_fans_power_channel_status = value;
}

void canzero_set_last_node_missed(uint8_t value);

static inline void canzero_set_mcu_temperature(float value){
  extern float __oe_mcu_temperature;
  __oe_mcu_temperature = value;
}

void canzero_set_error_mcu_temperature_invalid(error_flag value);

static inline void canzero_set_error_level_config_mcu_temperature(error_level_config value){
  extern error_level_config __oe_error_level_config_mcu_temperature;
  __oe_error_level_config_mcu_temperature = value;
}

static inline void canzero_set_total_power(float value){
  extern float __oe_total_power;
  __oe_total_power = value;
}

void canzero_send_config_hash();

void canzero_send_build_time();

void canzero_send_state();

void canzero_send_sdc_status();

void canzero_send_assertion_fault();

void canzero_send_error_any_short();

void canzero_send_error_heartbeat_miss();

void canzero_send_error_level_mcu_temperature();

void canzero_send_command();

void canzero_send_loop_frequency();

void canzero_send_levitation_boards_power_channel_current();

void canzero_send_levitation_boards_power_channel_status();

void canzero_send_guidance_boards_power_channel_current();

void canzero_send_guidance_boards_power_channel_status();

void canzero_send_motor_driver_power_channel_current();

void canzero_send_motor_driver_power_channel_status();

void canzero_send_input_board_power_channel_current();

void canzero_send_input_board_power_channel_status();

void canzero_send_raspberry_pi_power_channel_current();

void canzero_send_raspberry_pi_power_channel_status();

void canzero_send_antenna_power_channel_current();

void canzero_send_antenna_power_channel_status();

void canzero_send_led_board_power_channel_current();

void canzero_send_led_board_power_channel_status();

void canzero_send_fans_power_channel_current();

void canzero_send_fans_power_channel_status();

void canzero_send_last_node_missed();

void canzero_send_mcu_temperature();

void canzero_send_error_mcu_temperature_invalid();

void canzero_send_error_level_config_mcu_temperature();

void canzero_send_total_power();

#endif