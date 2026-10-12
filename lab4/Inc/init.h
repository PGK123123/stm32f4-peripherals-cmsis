#ifndef INIT_H
#define INIT_H



#include "main.h"

extern uint8_t display_need_update;

typedef enum {
    CLOCK_HSI,  // Внутренний генератор 16 МГц
    CLOCK_HSE,  // Внешний кварц (25 МГц)
    CLOCK_PLL   // Максимальная скорость 84 МГц (от HSE)
} ClockSource_t;


void clock_init(ClockSource_t source);
void fpu_init(void);
void tim4_init();


#endif
