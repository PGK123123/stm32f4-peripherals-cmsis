#include "systick.h"

volatile uint32_t ms_counter = 0;

void SysTick_Handler() {
    ms_counter++;
}





uint32_t get_ticks() {
    return ms_counter;
}
