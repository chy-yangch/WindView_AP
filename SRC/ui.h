#include "NuMicro.h"
#ifdef __cplusplus
extern "C"
{
#endif

enum ui_item {

	PAGE_LOGO,
	PAGE_MAIN,
	PAGE_DEV,
	PAGE_AD,
	PAGE_THR,
	PAGE_SND,
	PAGE_DUR,
	PAGE_FLA,
	PAGE_BRL,
	PAGE_UNT,
	PAGE_NOD,

};

extern void (*ui_fun_array[25])();
extern void ui_init(void);

