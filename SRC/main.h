#include "NuMicro.h"

#ifdef __cplusplus
extern "C"
{
#endif

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

#define FWV	1234
#define CE
//#define FCC
//#define RCM
//#define TELEC

enum  {OFF,ON};

struct WR3PTX_INFO {

	__IO uint8_t year;
	__IO uint8_t month;
	__IO uint32_t sn;
	__IO uint16_t pressure;		//hpa
	__IO uint16_t rh;			//none
	__IO int16_t temperature;		//deg-F
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

	__IO current_page;
	__IO enum  {INIT,WORK} page_step;

//	__IO uint8_t wireless_ch_status;
	__IO uint8_t tx_sn_binding_status;
	
	__IO uint8_t power_on;

	__IO uint32_t cc1200_timeout_cn;
	__IO uint8_t cc1200_sleep_mode;
	__IO uint8_t cc1200_sleep_mode_cnt;
	__IO uint8_t cc1200_wait_2_dot_6sec_flag;
	__IO uint8_t cc1200_wait_2_dot_6sec_cnt;


	struct WR3PTX_INFO wr3ptx_info;
	
	__IO uint8_t rx_sn[6];	//0:year 1:month 2~3:module name 4:No. 5:ch
	__IO uint8_t tx_sn[6];	//0:year 1:month 2~3:module name 4:No. 5:ch
	__IO uint8_t origin_tx_data[16];

	__IO enum  {W_FCC,W_CE,W_RCM,W_TELEC} country;
	__IO enum  {T_NORMAL,T_DIRECTION} type;
	__IO uint8_t rssi_value_show;
	
	__IO uint8_t exit_sleep_flag;
	
	__IO uint8_t windv_type;
	__IO uint8_t windv_ad;
	__IO uint8_t windv_unit;
	__IO uint8_t windv_thr;
	__IO uint8_t windv_sound_sw;
	__IO uint8_t windv_sound_reset_time;
	__IO uint8_t windv_light_level;
	__IO uint8_t windv_mode;
	__IO uint8_t windv_fla_sw;

};

enum windv_type_item{

	TYPE_WR3P,
	TYPE_WL21,
	TYPE_WR3P_EX,
};

enum windv_unit_item{
	
	UNIT_MPH,
	UNIT_KM,
	UNIT_MS,
};

enum windv_light_level_item{
	
	LIGHT_HI,
	LIGHT_NOR,
	LIGHT_LO,
};

enum windv_mode_item{
	
	MODE_DEF,
	MODE_U01,
	MODE_U02,
	MODE_SPD,
};

extern __IO uint8_t cc1200_get_flag;

extern struct RX_INFO info;

extern void windview_eeprom_read(void);
extern void windview_eeprom_default(void);
extern void led_light_level(uint8_t bri_level);

