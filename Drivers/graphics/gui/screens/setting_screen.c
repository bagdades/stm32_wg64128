/*
 * =====================================================================================
 *
 *       Filename:  setting_screen.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  09.03.22 20:11:40
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include "setting_screen.h"
#include "m_rtc.h"
#include "screen.h"
#include "widgets.h"
#include <stdio.h>

static uint32_t sTemp = 100;
static uint32_t sMTemp = 200;
screen_t Screen_system;
screen_t Screen_settings;

static void *getDate() {
	mRTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN);
	snprintf(showDate, 11, "%02d.%02d.20%02d", sDate.Date, sDate.Month, sDate.Year);
	return showDate;
}

static void setDate(RTC_DateTypeDef *date) {
	mRTC_SetDate(&hrtc, date, RTC_FORMAT_BIN);
}

static void *getTime() {
	mRTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
	snprintf(showTime, 9, "%02d:%02d:%02d", sTime.Hours, sTime.Minutes, sTime.Seconds);
	return showTime;
}

static void setTime(RTC_TimeTypeDef *time) {
	mRTC_SetTime(&hrtc, time, RTC_FORMAT_BIN);
}

static void setTempSet(uint16_t *val) { sTemp = *val; }

static void *getTempSet() { return &sTemp; }

static void setValueSet(uint16_t *val) { sMTemp = *val; }

static void *getValueSet() { return &sMTemp; }

static void system_onEnter(screen_t *scr){
	if(scr==&Screen_settings){
		comboResetIndex(Screen_system.current_widget);
	}
}

void setting_screen_init(screen_t *scr) {
	default_init(scr);
}

int setting_screenProcessInput(screen_t * scr, RE_Rotation_t input, RE_State_t *state) {
	if(input != Rotate_Nothing)
		resetScreenTimer();
	switch ((uint8_t)input) {
		case LongClick:
			return screen_main;
		default:
			break;
	}
	return default_screenProcessInput(scr, input, state);
}

void setting_screen_create(screen_t *scr) {
	widget_t *w;
	displayOnly_widget_t *dis;
	editable_widget_t *edit;
	newWidget(&w, widget_display, scr);
	dis = extractDisplayPartFromWidget(w);
	dis->displayString = "Setting";
	dis->type = field_string;
	dis->font = &Arial7;
	dis->dispAlign = align_center;
	dis->reservedChars = 7;
	w->posX = 0;
	w->posY = 0;
	w->enabled = 1;

	newWidget(&w, widget_combo, scr);
	newComboEditable(w, "Set Time", &edit, NULL);
	w->posY = 9;
	dis = &edit->inputData;
	dis->reservedChars = 8;
	dis->type = field_time;
	dis->getData = &getTime;
	edit->big_step = 1;
	edit->step = 1;
	edit->selectable.tab = 0;
	edit->setData = (void (*)(void *)) & setTime;

	newComboEditable(w, "Set Date", &edit, NULL);
	dis = &edit->inputData;
	dis->reservedChars = 11;
	dis->type = field_date;
	dis->getData = &getDate;
	edit->big_step = 1;
	edit->step = 1;
	edit->selectable.tab = 0;
	edit->setData = (void (*)(void *)) & setDate;

	newComboEditable(w, "Second", &edit, NULL);
	dis = &edit->inputData;
	dis->reservedChars = 4;
	dis->endString = "V";
	dis->getData = &getValueSet;
	edit->big_step = 10;
	edit->step = 1;
	edit->setData = (void (*)(void *)) & setValueSet;
	edit->max_value = 300;
	edit->min_value = 0;

	newComboEditable(w, "First", &edit, NULL);
	dis = &edit->inputData;
	dis->reservedChars = 4;
	dis->endString = "V";
	dis->getData = &getValueSet;
	edit->big_step = 10;
	edit->step = 1;
	edit->setData = (void (*)(void *)) & setValueSet;
	edit->max_value = 300;
	edit->min_value = 0;

	newComboEditable(w, "TestTest", &edit, NULL);
	dis = &edit->inputData;
	dis->reservedChars = 5;
	dis->endString = "mS";
	dis->getData = &getTempSet;
	edit->big_step = 10;
	edit->step = 1;
	edit->setData = (void (*)(void *)) & setTempSet;
	edit->max_value = 200;
	edit->min_value = 0;

	newComboEditable(w, "WelcomeOne", &edit, NULL);
	dis = &edit->inputData;
	dis->reservedChars = 4;
	dis->endString = "V";
	dis->getData = &getValueSet;
	edit->big_step = 10;
	edit->step = 1;
	edit->setData = (void (*)(void *)) & setValueSet;
	edit->max_value = 300;
	edit->min_value = 0;

	newComboEditable(w, "SecondTest", &edit, NULL);
	dis = &edit->inputData;
	dis->reservedChars = 4;
	dis->endString = "V";
	dis->getData = &getValueSet;
	edit->big_step = 10;
	edit->step = 1;
	edit->setData = (void (*)(void *)) & setValueSet;
	edit->max_value = 300;
	edit->min_value = 0;

	newComboEditable(w, "WelcomeTest", &edit, NULL);
	dis = &edit->inputData;
	dis->reservedChars = 4;
	dis->endString = "V";
	dis->getData = &getValueSet;
	edit->big_step = 10;
	edit->step = 1;
	edit->setData = (void (*)(void *)) & setValueSet;
	edit->max_value = 300;
	edit->min_value = 0;
	newComboScreen(w, "Exit", screen_main, NULL);
}

void setting_screen_setup(screen_t *scr) {
	scr->draw = default_screenDraw;
	scr->init = setting_screen_init;
	scr->processInput = autoReturn_ProcessInput;
	scr->onEnter = &system_onEnter;
	scr->create = setting_screen_create;
}
