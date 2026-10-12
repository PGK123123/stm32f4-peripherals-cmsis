#ifndef INIT_H
#define INIT_H



#include "main.h"


typedef enum {
    CLOCK_HSI,  // Внутренний генератор 16 МГц
    CLOCK_HSE,  // Внешний кварц (25 МГц)
    CLOCK_PLL   // Максимальная скорость 84 МГц (от HSE)
} ClockSource_t;


void Clock_Init(ClockSource_t source);



#endif
