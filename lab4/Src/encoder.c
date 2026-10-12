#include "encoder.h"
#include "button.h"

void encoder_init(void) {

    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;


    GPIOA->MODER &= ~(GPIO_MODER_MODER0 | GPIO_MODER_MODER1);
    GPIOA->MODER |=  (GPIO_MODER_MODER0_1 | GPIO_MODER_MODER1_1);


    GPIOA->AFR[0] &= ~((0xFU << GPIO_AFRL_AFSEL0_Pos) | (0xFU << GPIO_AFRL_AFSEL1_Pos));
    GPIOA->AFR[0] |=  ((1U   << GPIO_AFRL_AFSEL0_Pos) | (1U   << GPIO_AFRL_AFSEL1_Pos));


    GPIOA->PUPDR &= ~(GPIO_PUPDR_PUPD0 | GPIO_PUPDR_PUPD1);
    GPIOA->PUPDR |=  (GPIO_PUPDR_PUPD0_0 | GPIO_PUPDR_PUPD1_0);


    // CC1S = 01 (канал 1 на вход), IC1F = 1111 (максимальный цифровой фильтр от дребезга):
    TIM2->CCMR1 = TIM_CCMR1_CC1S_0 | TIM_CCMR1_CC2S_0;

    // 6. Режим энкодера 3 (Encoder Mode 3: считает по обоим каналам)
    TIM2->SMCR &= ~TIM_SMCR_SMS;
    TIM2->SMCR |= (3U << TIM_SMCR_SMS_Pos);

    // 7. Период на максимум (TIM2 32-битный)
    TIM2->ARR = 0xFFFFFFFF;
    TIM2->CNT = 0;

    // 8. Запуск таймера
    TIM2->CR1 |= TIM_CR1_CEN;
}



void change_brightness(volatile uint32_t *ccr, int16_t step){
    int32_t val = (int32_t)(*ccr) + step;
    if (val < 0)    val = 0;
    if (val > 1000) val = 1000;
    *ccr = (uint32_t)val;
}



void encoder_update(void){
    static int32_t last_cnt = 0;

    int32_t current_cnt = (int32_t)TIM2->CNT;

    int32_t diff = current_cnt - last_cnt;

    int32_t steps = diff / 4;

    if (steps != 0){

        last_cnt += steps * 4;
        display_need_update = 1;

        int16_t change = (int16_t)(steps * 50);

        switch(current_channel) {
            case 0: change_brightness(&TIM3->CCR3, -change); break; // Red
            case 1: change_brightness(&TIM3->CCR2, -change); break; // Green
            case 2: change_brightness(&TIM3->CCR1, -change); break; // Blue
        }
    }
}
