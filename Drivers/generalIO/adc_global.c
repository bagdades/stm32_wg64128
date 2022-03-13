/*
 * =====================================================================================
 *
 *       Filename:  adc_global.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  10.03.22 22:34:52
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include "adc_global.h"
#include "main.h"
#include "main_screen.h"
#include "stm32f1xx_hal_adc.h"
#include "stm32f1xx_hal_adc_ex.h"

void ADC_Init(ADC_HandleTypeDef *adc) {
	if(HAL_ADCEx_Calibration_Start(adc) != HAL_OK) {
		Error_Handler();
	}
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc) {
	if(hadc == &hadc1) {
		HAL_ADC_Stop_DMA(&hadc1);
		adc = adc_value;
	}
}

uint16_t ADC_to_mV (uint16_t adc){
  /*
   * Instead running ( ADC*(3300/4095) ),
   * We previously multiply (3300/4095)*2^20 = 845006
   * Then we can use the fast hardware multiplier and
   * divide just with bit rotation.
   *
   * So it becomes Vadc = (ADC * 845006) >>20
   * Max possible input = 20 bit number, more will cause overflow to the 32 bit variable
   * Calculated to use  12 bit max input from ADC (4095)
   * Much, much faster than floats!
   */

  return( ((uint32_t)845006*adc)>>20 );
}
