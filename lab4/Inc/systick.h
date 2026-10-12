#ifndef SYSTICK_H
#define SYSTICK_H

#include "main.h"

void systick_init(void);

uint32_t get_ticks(void);

void delay_ms(uint32_t ms);

#endif
