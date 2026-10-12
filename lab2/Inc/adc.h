#ifndef ADC_H
#define ADC_H

#include "main.h"

void adc_init();
uint16_t adcReadValue(uint8_t channel);
#endif
