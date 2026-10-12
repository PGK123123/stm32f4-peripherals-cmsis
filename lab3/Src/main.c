#include "main.h"
#include "init.h"
#include "adc.h"
#include "usart.h"
#include "systick.h"
#include "dma.h"
#include "data.h"

int main(void){

	clock_init(CLOCK_HSI);
	systick_init();
	fpu_init();
	dma_init();
	adc_init();
	usart2_init();

	delay_ms(10);

	adc_data_t current_data;

	usart2_send_string("START!\r\n");

	while(1){


	current_data = get_filtered_sensor_data();
	usart2_send_message(current_data.in1,current_data.in16, current_data.temp);

    delay_ms(150);
    }
}
