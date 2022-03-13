#ifndef  adc_global_INC
#define  adc_global_INC

#include "main.h"

void ADC_Init(ADC_HandleTypeDef *adc);
uint16_t ADC_to_mV (uint16_t adc);

#endif   /* ----- #ifndef adc_global_INC  ----- */
