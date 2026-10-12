#include "data.h"
#include "adc.h"


adc_data_t get_filtered_sensor_data(void) {
	adc_data_t data;

    uint32_t sum_in1  = 0;
    uint32_t sum_in16 = 0;

    for (int i = 0; i < 16; i++) {
        while (!(DMA2->LISR & DMA_LISR_TCIF0));
        DMA2->LIFCR = DMA_LIFCR_CTCIF0;

        sum_in1  += adc_result[0];
        sum_in16 += adc_result[1];
    }

    data.in1  = (uint16_t)(sum_in1 >> 4);
    data.in16 = (uint16_t)(sum_in16 >> 4);

    data.temp = get_temperature(data.in16);

    return data;
}
