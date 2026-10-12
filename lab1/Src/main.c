#include "main.h"
#include "init.h"
#include "leds.h"
#include "systick.h"
#include "button.h"

extern volatile int8_t direction;

int main(void)
{

	Clock_Init(CLOCK_PLL);
	all_led_init();
	button_init();

	SysTick_Config(SystemCoreClock / 1000);

	int8_t current_led = 0;
	uint32_t last_step_time = 0;

	while(1){

	if ((get_ticks() - last_step_time) >= LED_MS_LIGHT_TIME){
		last_step_time = get_ticks();

		led_off(&leds[current_led]);

		current_led+=direction;
		if (current_led >= LED_COUNT) current_led = 0;
		else if (current_led < 0) current_led = LED_COUNT - 1;

		led_on(&leds[current_led]);

	}
	}
}
