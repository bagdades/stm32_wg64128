/*
 * =====================================================================================
 *
 *       Filename:  gui.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05.03.22 23:23:01
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include "gui.h"
#include "lcd.h"
#include "setting_screen.h"
#include "boot_screen.h"

void gui_init(void) {
	screen_t *scr = lcd_addScreen(screen_boot);
	boot_screen_setup(scr);
	scr = lcd_addScreen(screen_main);
	main_screen_setup(scr);
	scr = lcd_addScreen(screen_settings);
	setting_screen_setup(scr);
}
