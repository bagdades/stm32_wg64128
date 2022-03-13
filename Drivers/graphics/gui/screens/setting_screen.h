#ifndef  setting_screen_INC
#define  setting_screen_INC

#include "main.h"
#include "screen.h"
#include "screen_common.h"

extern RTC_TimeTypeDef mTime;
extern RTC_DateTypeDef mDate;

void setting_screen_setup(screen_t *scr);

#endif   /* ----- #ifndef setting_screen_INC  ----- */
