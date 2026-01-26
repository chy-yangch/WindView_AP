#include "NuMicro.h"

#ifdef __cplusplus
extern "C"
{
#endif

#define	POW_KEY			PC2
#define	DOWN_KEY			PC3
#define	UP_KEY				PC4
#define	CANCEL_KEY			PC5
#define	CONFIRM_KEY		PF6

#define	PWM0_BEEPER_SW		PB5

#define	LED_H_SW			PA11
#define	LED_M_SW			PA10
#define	LED_L_SW			PA9

#define	RSSI_1_PIN			PD0
#define	RSSI_2_PIN			PD1
#define	RSSI_3_PIN			PD2
#define	RSSI_4_PIN			PD3

#define	MP_PIN				PB4
#define	KM_PIN				PB3
#define	MS_PIN				PB2

#define	DOT_PIN				PB8

#define	N1_A_PIN				PA7
#define	N1_B_PIN				PB1
#define	N1_C_PIN				PB0
#define	N1_D_PIN				PA8
#define	N1_E_PIN				PC7
#define	N1_F_PIN				PC6
#define	N1_G_PIN				PA6

#define	N2_A_PIN				PA13
#define	N2_B_PIN				PA15
#define	N2_C_PIN				PB12
#define	N2_D_PIN				PB7
#define	N2_E_PIN				PB11
#define	N2_F_PIN				PA14
#define	N2_G_PIN				PB13

#define	N3_A_PIN				PA12
#define	N3_B_PIN				PB15
#define	N3_C_PIN				PB9
#define	N3_D_PIN				PB6
#define	N3_E_PIN				PB10
#define	N3_F_PIN				PC14
#define	N3_G_PIN				PB14

//#define CE
#define FCC
//#define RCM
//#define TELEC

enum  {OFF,ON};

struct WR3PTX_INFO {

	__IO uint8_t year;
	__IO uint8_t month;
	__IO uint32_t sn;
	__IO uint16_t pressure;		//hpa
	__IO uint16_t rh;		//none
	__IO int16_t temperature;	//deg-F
	__IO uint16_t wind_speed;	//km/h
	__IO uint8_t low_batt;
	__IO uint16_t degrees;
	__IO uint8_t tx_count;
	__IO int8_t rssi;
	__IO uint8_t wr3ptx_first_data_get;
	__IO uint8_t wr3ptx_first_data_get_had_beeper_flag;
	__IO uint8_t wr3ptx_info_get;
	__IO uint8_t wr3ptx_info_hour_between_get;
	
	__IO uint8_t tx_0ch_sn;
	__IO uint8_t tx_0ch_fwv;
	__IO uint8_t tx_0ch_address;
	__IO uint8_t tx_0ch_setting_flag;
	
	__IO uint8_t tx_update_dot_flag;
	__IO uint8_t tx_update_search_flag;
	__IO uint8_t tx_update_search_sec_cnt;
	__IO uint8_t tx_update_ota_mode;
	__IO uint8_t tx_update_ota_start;
	__IO uint32_t tx_update_ota_step_cnt;
	__IO uint8_t tx_update_ota_step_next;
	__IO uint8_t tx_update_ota_step_next_timeout;
	
	__IO uint8_t tx_lowbatt_led_flag;
	__IO uint8_t tx_lowbatt_led_cnt;
	
	__IO uint8_t tx_frequency_cal_mode;
};

struct RX_INFO {

	__IO enum  {LOGO_Page,MAIN_Page, AVG_MAX_Page, CHART_Page, HISTORY_1_Page, HISTORY_2_Page, HISTORY_3_Page,SETTINGS_Page,GENERAL_1_Page,GENERAL_2_Page,DATA_LOGGING_Page,WIND_SPEED_Page,START_LOGGING_Page,STOP_LOGGING_Page,CLEAR_DATA_Page,TEST_Page,DOWNLOAD_Page,FIRMWARE_UPDATE_Page} current_page;
	__IO uint32_t before_download_page;
	__IO enum  {INIT,WORK} page_step;
	__IO uint32_t before_page_step;
	__IO enum  {WIND_SPEED_ITEM,DATA_LOGGING_ITEM,GENERAL_ITEM,FIRMWARE_UPDATE_ITEM} setting_item;
	__IO enum  {WIND_SPEED_UNIT_ITEM,ALARM_ITEM,ALARM_THRESHOLD_ITEM} wind_speed_item;
	__IO enum  {LOGGING_ITEM,LOGGING_INTERVAL_ITEM,CLEAR_DATA_ITEM,AVAILABLE_MEMORY_ITEM} logging_item;
	__IO enum  {DATE_ITEM,TIME_ITEM,SENSOR_ADDRESS_ITEM,TEMPERATURE_UNIT_ITEM,ATMOS_PRESS_UNIT_ITEM} general_item;
	__IO enum  {TX_FW_UPDATE_ITEM,SENSOR_ADDRESS_SETTING_ITEM,SENSOR_SN_SETTING_ITEM} fw_update_item;
	
	//__IO enum  {REC_OFF,REC_ON} logging_rec_status;
	__IO enum  {DEG_C,DEG_F} temperature_unit_status;
	__IO enum  {MS,KM,MPH,KNOTS} wind_speed_unit_status;
	__IO enum  {HPA,MMHG,BAR} pressure_unit_status;
	__IO uint8_t wireless_ch_status;
	__IO enum {DISP_OFF,DISP_5MIN,DISP_10MIN,DISP_30MIN} display_auto_on_off_status;
	__IO uint8_t tx_sn_binding_status;
	
	//__IO enum  {NO,YES} yes_no;
	__IO uint8_t power_on;
	__IO uint8_t display_on_off;
	
	__IO uint32_t timer0_cn;
	__IO uint32_t display_auto_off_cn;
	__IO uint32_t led_blinking_sec_cn;
	__IO uint16_t backlight_cn;
	__IO uint32_t cc1200_timeout_cn;
	
	__IO uint8_t cc1200_sleep_mode;
	__IO uint8_t cc1200_sleep_mode_cnt;
	__IO uint8_t cc1200_wait_2_dot_6sec_flag;
	__IO uint8_t cc1200_wait_2_dot_6sec_cnt;
	
	__IO uint8_t enter_item_select_index;

	__IO uint8_t usb_insert_flag;
	__IO uint8_t usb_insert_cnt;
	__IO uint8_t batt_measure_flag;
	
	__IO uint16_t draw_last_ofset;
	__IO uint16_t batt_v;
	__IO uint8_t low_batt_flag;
	//__IO int16_t temperature_value;
	//__IO uint16_t wind_speed_value;
	__IO uint16_t rh_value;
	__IO int16_t pressure;
	
	__IO uint8_t exit_sleep_flag;
	__IO uint16_t max_wind_speed_value;
	__IO uint16_t avg_wind_speed_value;
	
	__IO uint32_t time_setting_array[6];
	
	struct WR3PTX_INFO wr3ptx_info;
	
	__IO uint32_t wireless_get_cn;
	__IO uint8_t cal_mode;
	__IO uint32_t cal_xtal_value;
	__IO float cal_batt_slope_value;
	__IO uint32_t cal_batt_adc_count;
	__IO uint8_t rx_sn[6];	//0:year 1:month 2~3:module name 4:No. 5:ch
	__IO uint8_t tx_sn[6];	//0:year 1:month 2~3:module name 4:No. 5:ch
	__IO uint8_t origin_tx_data[16];
	__IO uint32_t flash_id;
	__IO uint8_t free_flash_percent;
	__IO enum  {W_FCC,W_CE,W_RCM,W_TELEC} country;
	__IO enum  {T_NORMAL,T_DIRECTION} type;
	__IO uint8_t rssi_value_show;
	

	__IO uint32_t cal_tx_frequency_value;
};

extern __IO uint8_t cc1200_get_flag;

extern struct RX_INFO info;
