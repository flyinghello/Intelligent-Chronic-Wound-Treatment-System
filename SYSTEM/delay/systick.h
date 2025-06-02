#ifndef __SYSTICK_H_
#define __SYSTICK_H_
#include "stm32f10x.h"

void RCC_HSE_Config(void);
void SYSTICK_CONFIG(void);

void delay_init(u8 SYSCLK);
void delay_us(u32 nus);
void delay_ms(u16 nms);

#endif
