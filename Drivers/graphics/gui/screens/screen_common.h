#ifndef  screen_common_INC
#define  screen_common_INC

#include "main.h"
#include "screen.h"
#include "lcd.h"

int autoReturn_ProcessInput(screen_t * scr, RE_Rotation_t input, RE_State_t *state);
void resetScreenTimer(void);
uint8_t checkScreenTimer(uint32_t time);
void updateScreenTimer(RE_Rotation_t input);

#endif   /* ----- #ifndef screen_common_INC  ----- */
