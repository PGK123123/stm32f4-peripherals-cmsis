#ifndef DMA_H
#define DMA_H

#include "main.h"

#define DMA_DATA_COUNT 2

extern volatile uint16_t adc_result[DMA_DATA_COUNT];

void dma_init(void);

#endif
