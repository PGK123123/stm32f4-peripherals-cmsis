#ifndef LEDS_H
#define LEDS_H

#define LED_COUNT 7
#define LED_MS_LIGHT_TIME 250

#include "main.h"

typedef struct{
	GPIO_TypeDef *port;
	uint8_t pin;
}led_t;

extern const led_t leds[LED_COUNT];

void led_init(const led_t *led);
void all_led_init();

void all_led_off(void);
void led_off(const led_t *led);

void led_on(const led_t *led);

#endif
