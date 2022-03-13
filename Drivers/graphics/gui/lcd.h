#ifndef  lcd_INC
#define  lcd_INC

#include "screen.h"
#include "lcdwg.h"

extern screen_t *current_screen;
extern uint32_t current_time;
extern uint32_t screen_timer;
extern uint8_t last_scr;

screen_t *lcd_addScreen(uint8_t index);
void lcd_draw(void);
void lcd_update(void);
void lcd_processInput(void);
void lcd_init(RE_Rotation_t (*GetData)(RE_State_t*), RE_State_t *State);

#endif   /* ----- #ifndef lcd_INC  ----- */
