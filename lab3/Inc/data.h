#ifndef DATA_H
#define DATA_H

#include "main.h"
#include "dma.h"


typedef struct {
    uint16_t in1;
    uint16_t in16;
    float    temp;
} adc_data_t;

adc_data_t get_filtered_sensor_data(void);

#endif
