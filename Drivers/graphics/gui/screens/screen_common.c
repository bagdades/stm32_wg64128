/*
 * =====================================================================================
 *
 *       Filename:  screen_common.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  09.03.22 20:43:27
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include "screen_common.h"
#include "screen.h"

int autoReturn_ProcessInput(screen_t * scr, RE_Rotation_t input, RE_State_t *state) {
	updateScreenTimer(input);
	if(checkScreenTimer(15000))
		return screen_main;
	if(input == LongClick)
		return screen_main;
	return default_screenProcessInput(scr, input, state);
}

void resetScreenTimer(void){
  screen_timer=current_time;
}

uint8_t checkScreenTimer(uint32_t time){
  if((current_time-screen_timer)>time){
    return 1;
  }
  return 0;
}

void updateScreenTimer(RE_Rotation_t input){
  if(input!=Rotate_Nothing){
    screen_timer=current_time;
  }
}
