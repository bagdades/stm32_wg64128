/*
 * delay.c
 *
 *  Created on: 13 груд. 2012
 *      Author: vovan
 */


#include "delay.h"

void _delay_ms(uint32_t ms){
	volatile uint32_t nCount;
	nCount = (SystemCoreClock / 10000) * ms;
	for(; nCount !=0 ; nCount--){
		asm("nop");
		asm("nop");
		asm("nop");
		asm("nop");
	}
}
void _delay_us(uint32_t us){
	volatile uint32_t nCount;
	nCount = (SystemCoreClock / 10000000) * us;
	for(; nCount !=0 ; nCount--){
		asm("nop");
		asm("nop");
		asm("nop");
		asm("nop");
	}
}
