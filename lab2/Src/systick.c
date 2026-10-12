#include "systick.h"

static volatile uint32_t ms_ticks = 0;

void systick_init(void) {
    SysTick_Config(SystemCoreClock / 1000);
}

void SysTick_Handler(void) {
    ms_ticks++;
}

uint32_t get_ticks(void) {
    return ms_ticks;
}

void delay_ms(uint32_t ms) {
    uint32_t start_time = ms_ticks;
    while ((ms_ticks - start_time) < ms) {
        __NOP();
    }
}
