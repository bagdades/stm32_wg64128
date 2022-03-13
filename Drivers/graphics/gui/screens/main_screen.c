/*
 * =====================================================================================
 *
 *       Filename:  main_screen.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  06.03.22 09:24:55
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include "main_screen.h"
#include "lcdwg.h"
#include "rotary_encoder.h"
#include "adc_global.h"
#include "screen.h"
#include "stm32f1xx_hal_rtc.h"
#include "widgets.h"
#include "arial7.h"
#include "arial9_b.h"
#include <stdio.h>
/* #include "dig.h" */

extern ug_t ug;
static uint32_t temp = 90;
static uint32_t mTemp = 200;
static uint16_t volt;
uint16_t adc;

static void *getVin() {
	volt = ADC_to_mV(adc);
	volt = volt / 10;
	return &volt;
}

static void setTemp(uint16_t *val) {
	temp = *val;
}

static void * getTemp() {
	return &temp;
}

static void setValue(uint16_t *val) {
	mTemp = *val;
}

static void * getValue() {
	return &mTemp;
}

static void* getADC() {
	return (uint16_t*)&adc;
}

int main_screenProcessInput(screen_t * scr, RE_Rotation_t input, RE_State_t *state) {
	if(input != Rotate_Nothing)
		resetScreenTimer();
	switch ((uint8_t)input) {
		case LongClick:
			return screen_settings;
		default:
			break;
	}
	return default_screenProcessInput(scr, input, state);
}

static void main_screen_init(screen_t *scr) {
	default_init(scr);
}

static uint8_t main_screen_draw(screen_t *scr) {
	/* ug_SetMode(&ug, LCD_MODE_NORM); */
	/* ug_SetFont(&ug, &Arial9_b); */
	/* ug_DrawString(&ug, 20, 0, "Hello, World!"); */
	return default_screenDraw(scr);
}

static void main_screen_create(screen_t *scr) {
	widget_t *w;
	displayOnly_widget_t *dis;
	editable_widget_t *edit;

	/* newWidget(&w,widget_combo,scr); */
	/* ((comboBox_widget_t*)w->content)->font = &Arial9_b; */
	/* newComboScreen(w, "ONE", 0, NULL); */
	/* newComboScreen(w, "TWO", 1, NULL); */
	/* newComboScreen(w, "THREE", 1, NULL); */
	/* newComboScreen(w, "FOUR", 1, NULL); */

	/* newWidget(&w, widget_display, scr); */
	/* dis = extractDisplayPartFromWidget(w); */
	/* dis->displayString = "Hello, World!"; */
	/* dis->font = &Arial7; */
	/* dis->type = field_string; */
	/* dis->dispAlign = align_left; */
	/* w->posX = 0; */
	/* w->posY = 0; */
	/* w->width = 60; */
	/* w->enabled = 1; */
	newWidget(&w, widget_display, scr);
	dis = extractDisplayPartFromWidget(w);
	dis->reservedChars = 9;
	dis->displayString = showTime;
	dis->dispAlign = align_center;
	dis->font = &Arial9_b;
	dis->type = field_string;
	w->posX = 0;
	w->posY = 0;
	w->width = 127;
	w->enabled = 1;

	newWidget(&w,widget_editable,scr);
	dis=extractDisplayPartFromWidget(w);
	edit=extractEditablePartFromWidget(w);
	dis->reservedChars=5;
	w->posY = 19;
	w->posX = 20;
	dis->getData = &getTemp;
	dis->dispAlign=align_disabled;
	dis->textAlign=align_right;
	dis->font= &Arial9_b;
	dis->type = field_temp;
	edit->selectable.tab = 0;
	edit->setData = (void (*)(void *))&setTemp;
	edit->step = 1;
	edit->big_step = 10;
	edit->max_value = 200;
	edit->min_value = 0;
	w->frameType=frame_auto;
	/* edit->selectable.state=widget_edit; */
	w->enabled=1;
	w->width=22;

	newWidget(&w,widget_editable,scr);
	dis=extractDisplayPartFromWidget(w);
	edit=extractEditablePartFromWidget(w);
	dis->reservedChars=5;
	w->posY = 32;
	w->posX = 20;
	dis->getData = &getTemp;
	dis->getData = &getValue;
	dis->dispAlign=align_disabled;
	dis->textAlign=align_right;
	dis->font= &Arial9_b;
	/* dis->type = field_temp; */
	edit->selectable.tab = 1;
	edit->setData = (void (*)(void *))&setValue;
	edit->step = 1;
	edit->big_step = 10;
	edit->max_value = 200;
	edit->min_value = 0;
	w->frameType=frame_auto;
	/* edit->selectable.state=widget_edit; */
	w->enabled=1;
	w->width=22;

	newWidget(&w, widget_display, scr);
	dis = extractDisplayPartFromWidget(w);
	dis->getData = &getADC;
	dis->type = field_int32;
	dis->reservedChars = 10;
	dis->font = &Arial9_b;
	dis->textAlign = align_right;
	w->posX = 50;
	w->posY = 19;
	w->enabled = 1;
	w->width = 70;

	newWidget(&w, widget_display, scr);
	dis = extractDisplayPartFromWidget(w);
	dis->getData = &getVin;
	dis->reservedChars = 6;
	dis->font = &Arial9_b;
	dis->number_of_dec = 2;
	dis->endString = "V";
	dis->textAlign = align_right;
	w->posX = 50;
	w->posY = 32;
	w->enabled = 1;
	w->width = 70;

	/* newWidget(&w,widget_editable,scr); */
	/* dis=extractDisplayPartFromWidget(w); */
	/* edit=extractEditablePartFromWidget(w); */
	/* dis->reservedChars=5; */
	/* w->posY = 35; */
	/* dis->getData = &getValue; */
	/* dis->dispAlign=align_disabled; */
	/* dis->textAlign=align_right; */
	/* dis->font= &Arial9_b; */
	/* #<{(| dis->type = field_temp; |)}># */
	/* edit->selectable.tab = 2; */
	/* edit->setData = (void (*)(void *))&setValue; */
	/* w->frameType=frame_solid; */
	/* edit->selectable.state=widget_edit; */
	/* w->enabled=1; */
	/* w->width=50; */
}

void main_screen_setup(screen_t *scr) {
	scr->draw = main_screen_draw;
	scr->init = main_screen_init;
	scr->processInput = main_screenProcessInput;
	scr->create = main_screen_create;
}
