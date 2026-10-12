#ifndef ADC_H
#define ADC_H

#include "main.h"

void adc_init();

uint16_t adc_read_value(uint8_t channel);

float get_temperature(uint16_t adc_val);

#endif
