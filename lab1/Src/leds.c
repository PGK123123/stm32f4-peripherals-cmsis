#include "leds.h"

const led_t leds[LED_COUNT] = {
    {GPIOB, 0}, // VD1
    {GPIOA, 7}, // VD2
    {GPIOA, 6}, // VD3
    {GPIOA, 5}, // VD4
    {GPIOA, 3}, // VD5
    {GPIOA, 4}, // VD6
    {GPIOA, 2}  // VD7
};

void led_init(const led_t *led){

    led->port->MODER &= ~(3U << (led->pin * 2));
    led->port->MODER |=  (1U << (led->pin * 2)); // output

    led->port->OTYPER &= ~(1U << led->pin); // push pull

    led->port->OSPEEDR &= ~(3U << (led->pin * 2)); // low

    led->port->PUPDR &= ~(3U << (led->pin * 2)); // без подтяжки

    led->port->BSRR = (1U << (led->pin + 16)); // по умолчанию гасим
}

void all_led_init(){
	 RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOBEN;
	 for(uint8_t i = 0; i < LED_COUNT; i++){
		 led_init(&leds[i]);
	 }
}

void led_on(const led_t *led) {
    led->port->BSRR = (1U << led->pin);
}

void led_off(const led_t *led) {
    led->port->BSRR = (1U << (led->pin + 16));
}

void all_led_off() {
    for (uint8_t i = 0; i < LED_COUNT; i++) {
        led_off(&leds[i]);
    }
}

