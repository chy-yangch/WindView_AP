#include "NuMicro.h"
#ifdef __cplusplus
extern "C"
{
#endif

#define POW_KEY			PC2
#define CANCEL_KEY		PC5
#define CONFIRM_KEY		PF6
#define UP_KEY	  		PC4
#define DOWN_KEY  		PC3


#define Power_KEY_BIT		BIT0
#define Cancel_KEY_BIT		BIT1
#define Enter_KEY_BIT		BIT2
#define UP_KEY_BIT  		BIT3
#define Down_KEY_BIT  		BIT4


#define Restore_Default_Sec	50	//
#define FAST_SETTING_HOLD_TIME 25	//2.5秒 

extern enum {

	UP_KEY_HOLD,
	Down_KEY_HOLD,
	Power_KEY_HOLD,
	Enter_KEY_HOLD,
	Cancel_KEY_HOLD

} key_hold;


struct KEY_INFO {
	__IO uint8_t key_bit;
	__IO uint8_t key_lock_bit;
	__IO uint8_t key_action_key;
	__IO uint8_t key_action;
	__IO uint8_t key_st[8];							//防止先按下KEY後,再開啟電源,需先放開KEY後才開始判斷
	__IO uint32_t key_hold_cn[8];
	__IO uint8_t key_setting_mode;
	__IO uint8_t key_baseline_coordinate[4];				//key_baseline_coordinate[0]:X,key_baseline_coordinate[1]:Y,key_baseline_coordinate[2]:With,key_baseline_coordinate[3]:Hight
	__IO uint8_t key_baseline_offset;
	__IO uint8_t key_blinking_flag;
	__IO uint8_t key_blinking_cn;
	__IO uint32_t register_value[10];
	__IO enum  {NO,YES} yes_no;
	__IO uint8_t had_turn_on_pkey_release;
	
	__IO uint8_t fast_setting_mode;
	
	__IO uint8_t key_test[8];
};

extern struct KEY_INFO Key_Info;
extern void key_case_init(void);

extern void (*key_case_array[25])();

