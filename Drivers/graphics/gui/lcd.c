/*
 * =====================================================================================
 *
 *       Filename:  lcd.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05.03.22 23:22:29
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include "lcd.h"
#include "lcdwg.h"
#include "stm32f1xx_hal.h"
#include <stdlib.h>

static screen_t *screens = NULL;
screen_t *current_screen;
uint32_t current_time;
uint32_t screen_timer;
uint8_t last_scr;
static RE_State_t* RE_State;

RE_Rotation_t (*RE_GetData)(RE_State_t*);
RE_Rotation_t RE_Rotation;

screen_t *lcd_addScreen(uint8_t index) {
	screen_t *ret = malloc(sizeof(screen_t));
	if(!ret)
		Error_Handler();
	ret->processInput = &default_screenProcessInput;
	ret->init = &default_init;
	ret->draw = &default_screenDraw;
	ret->update = &default_screenUpdate;
	ret->onEnter = NULL;
	ret->onExit = NULL;
	ret->index = index;
	ret->next_screen = NULL;
	ret->widgets = NULL;
	ret->current_widget = NULL;
	/* ret->index = index; */
	/* ret->next_screen = NULL; */
	/* ret->init = NULL; */
	/* ret->draw = NULL; */
	/* ret->onExit = NULL; */
	/* ret->onEnter = NULL; */
	/* ret->processInput = NULL; */
	/* ret->widgets = NULL; */
	/* ret->current_widget = NULL; */
	if(screens == NULL) {
		screens = ret;
	}
	else {
		screen_t *temp = screens;
		while(temp->next_screen) {
			temp = temp->next_screen;
		}
		temp->next_screen = ret;
	}
	return ret;
}

void lcd_draw(void) {
	current_time = HAL_GetTick();
	current_screen->draw(current_screen);
	ug_Update();
}

void lcd_update(void) {
	if(current_screen->update) {
		current_time = HAL_GetTick();
		current_screen->update(current_screen);
	}
}

void lcd_init(RE_Rotation_t (*GetData)(RE_State_t*), RE_State_t *State) {
	screen_timer = current_time = HAL_GetTick();
	RE_State = State;
	RE_GetData = GetData;
	screen_t *scr = screens;
	while(scr) {
		if(scr->index == 0) {
			if(scr->create)
				scr->create(scr);
			scr->init(scr);
			current_screen = scr;
			return;
		}
	}
}

void lcd_destroy_screen(screen_t *scr){
  widget_t *w = scr->widgets;
  widget_t *next;
  if(!w){ return; }
  do{
    next=w->next_widget;
    if(w->content){
      if(w->type==widget_combo){
        comboBox_item_t *Item = ((comboBox_widget_t*)w->content)->first;
        comboBox_item_t *Next;
        if(Item){
          do{
            Next=Item->next_item;
            if( (Item->type==combo_Editable) || (Item->type==combo_MultiOption)){
              free(Item->widget);
            }
            free(Item);
            Item=Next;
          }while(Next);
        }
      }
      free(w->content);
    }
    free(w);
    w = next;
  }while(next);
  scr->current_widget=NULL;
  scr->widgets=NULL;
}

void lcd_backup_comboStatus(screen_t *scr){
  if((scr->current_widget)&&(scr->current_widget->type==widget_combo)){
    comboBox_widget_t *combo = (comboBox_widget_t*)scr->current_widget->content;
    if(combo->currentItem){
      scr->backup_combo_index = comboItemToIndex(scr->current_widget,combo->currentItem);
      scr->backup_combo_scroll=combo->currentScroll;
    }
    else{
      scr->backup_combo_index=0;
      scr->backup_combo_scroll=0;
    }
  }
}

void lcd_restore_comboStatus(screen_t *scr){
  if((scr->current_widget)&&(scr->current_widget->type==widget_combo)){
    comboBox_widget_t *combo = (comboBox_widget_t*)scr->current_widget->content;
    combo->currentScroll=scr->backup_combo_scroll;
    combo->currentItem = comboIndexToItem(scr->current_widget,scr->backup_combo_index);
  }
}

void lcd_processInput(void) {
  RE_Rotation = (*RE_GetData)(RE_State);
  current_time = HAL_GetTick();
  int ret = current_screen->processInput(current_screen, RE_Rotation, RE_State);
  if(ret > 0) {   // -1 do nothing, -2 nothing processed
    screen_t *scr = screens;
	/* ucg_SetForeColor(&ucg, C_BLACK); */
	/* ucg_FillScreen(&ucg); */
	/* ucg_SetForeColor(&ucg, C_CYAN); */
	ug_Clear();
    current_time = HAL_GetTick();
    while(scr) {
      if(scr->index == ret) {
        last_scr = current_screen->index;

        if(current_screen->onExit){
          current_screen->onExit(scr);
        }

        if(current_screen->create){                     // If "create" exists,it means it's a dynamic screen
          /* lcd_backup_comboStatus(current_screen);      // Save combo position */
          lcd_destroy_screen(current_screen);          // Destroy exiting screen
        }

        if(scr->create){                                // Create entering screen
          scr->create(scr);
          /* lcd_restore_comboStatus(scr);                // Restore combo position */
        }

        screen_timer = current_time = HAL_GetTick();

        scr->init(scr);
        if(scr->onEnter){
          scr->onEnter(current_screen);
        }

        current_screen = scr;

        ret = scr->processInput(scr, Rotate_Nothing, RE_State);     // Force first pass without activity to update screen

        if( ret >0){
          scr = screens;                                            // If new screen returned a different screen, start over
        }
        else{
          if(scr->update){
            scr->update(scr);
          }
          scr->refresh=screen_Erased;
          break;
        }
      }
      scr = scr->next_screen;
    }
  }
}
