/*
 * buzzer.h
 *
 *  Created on: Jan 12, 2021
 *      Author: David    Original work by Jose Barros (PTDreamer), 2017
 */

#ifndef GENERALIO_BUZZER_H_
#define GENERALIO_BUZZER_H_

#define SHORT_BEEP    (uint16_t)  10
#define LONG_BEEP     (uint16_t)  30
#define FATAL_BEEP    (uint16_t)  2000
#define ALARM_PERIOD  (uint16_t)  2000
#define ALARM_HIGH    (uint16_t)  10
#define ALARM_LOW     (uint16_t)  (ALARM_PERIOD-ALARM_HIGH)

/********************************
 *       Buzzer        *
 ********************************/
#define BUZZER_OFF          HAL_GPIO_WritePin(BUZ0_GPIO_Port, BUZ0_Pin, GPIO_PIN_SET);  \
                            HAL_GPIO_WritePin(BUZ1_GPIO_Port, BUZ1_Pin, GPIO_PIN_SET);

#define BUZZER_ON           HAL_GPIO_WritePin(BUZ0_GPIO_Port, BUZ0_Pin, GPIO_PIN_RESET); \
                            HAL_GPIO_WritePin(BUZ1_GPIO_Port, BUZ1_Pin, GPIO_PIN_RESET);

#define BUZZER_TOGGLE       HAL_GPIO_TogglePin(BUZ0_GPIO_Port, BUZ0_Pin); \
                            HAL_GPIO_TogglePin(BUZ1_GPIO_Port, BUZ1_Pin);

void buzzer_short_beep();
void buzzer_long_beep();
void buzzer_fatal_beep();
void buzzer_alarm_start();
void buzzer_alarm_stop();
void handle_buzzer();
void buzzer_init();
#endif /* GENERALIO_BUZZER_H_ */
