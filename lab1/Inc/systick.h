#ifndef SYSTICK_H
#define SYSTICK_H

#include "main.h"


void SysTick_Handler();
void delay_ms(uint32_t ms);
uint32_t get_ticks();
#endif
