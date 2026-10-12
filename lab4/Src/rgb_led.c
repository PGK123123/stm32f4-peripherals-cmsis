#include "rgb_led.h"
#include "pwm.h"

void rgb_led_init(void){
	pwm_init();
}

void all_led_off(void){
	TIM3->CCR1 = 0;
	TIM3->CCR2 = 0;
	TIM3->CCR3 = 0;
}

void all_led_on_max(void){
	TIM3->CCR1 = 1000;
	TIM3->CCR2 = 1000;
	TIM3->CCR3 = 1000;
}
