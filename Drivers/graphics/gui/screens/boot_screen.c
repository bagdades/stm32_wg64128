/*
 * =====================================================================================
 *
 *       Filename:  boot_screen.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  09.03.22 21:39:43
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include "boot_screen.h"
#include "lcdwg.h"
#include "screen.h"
#include "screen_common.h"
#include "widgets.h"

#define SPLASH_TIMEOUT 2000

extern ug_t ug;
uint8_t boot_step = 0;

static uint8_t boot_screen_draw(screen_t *scr) {
	uint8_t refresh = scr->refresh;
	uint8_t ret = default_screenDraw(scr);
	if(refresh != screen_Idle) {
		ug_SetMode(&ug, LCD_MODE_NORM);
		ug_SetFont(&ug, &Arial9_b);
		ug_DrawString(&ug, 10, 20, "HELLO");
	}
	return ret;
}

void boot_screen_init(screen_t *scr) {
	default_init(scr);
}

void boot_screen_create(screen_t *scr) {
	/* widget_t *w; */
	/* displayOnly_widget_t *dis; */
	/* newWidget(&w, widget_display, scr); */
	/* dis = extractDisplayPartFromWidget(w); */
	/* dis->displayString = "Hello, World"; */
	/* dis->reservedChars = 12; */
	/* dis->type = field_string; */
	/* dis->font = &Arial9_b; */
	/* w->posX = 20; */
	/* w->posY = 30; */
	/* w->enabled = 1; */
}

int boot_screen_processInput(screen_t *scr, RE_Rotation_t input, RE_State_t *state) {
	if(checkScreenTimer(SPLASH_TIMEOUT))
		return screen_main;
	return default_screenProcessInput(scr, input, state);
}

void boot_screen_setup(screen_t *scr) {
	scr->draw = &boot_screen_draw;
	scr->init = &boot_screen_init;
	scr->create = &boot_screen_create;
	scr->processInput = &boot_screen_processInput;
}
