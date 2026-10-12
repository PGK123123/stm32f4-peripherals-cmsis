#ifndef ENCODER_H
#define ENCODER_H

#include "main.h"

extern uint8_t display_need_update;

void encoder_init(void);
void change_brightness(volatile uint32_t *ccr, int16_t step);
void encoder_update(void);

#endif
