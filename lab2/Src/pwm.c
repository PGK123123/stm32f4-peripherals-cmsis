#include "pwm.h"

void pwm_init(void) {
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOBEN;
    RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;


    GPIOA->MODER &= ~((3U << GPIO_MODER_MODER6_Pos) | (3U << GPIO_MODER_MODER7_Pos));
    GPIOA->MODER |=  ((2U << GPIO_MODER_MODER6_Pos) | (2U << GPIO_MODER_MODER7_Pos)); // pa6 & pa7 af

    GPIOA->AFR[0] &= ~((0xFU << GPIO_AFRL_AFSEL6_Pos) | (0xFU << GPIO_AFRL_AFSEL7_Pos));
    GPIOA->AFR[0] |=  ((2U   << GPIO_AFRL_AFSEL6_Pos) | (2U   << GPIO_AFRL_AFSEL7_Pos)); // pa6 & pa7 af2

    GPIOB->MODER &= ~(3U << GPIO_MODER_MODER0_Pos);
    GPIOB->MODER |=  (2U << GPIO_MODER_MODER0_Pos); // // pb0 af

    GPIOB->AFR[0] &= ~(0xFU << GPIO_AFRL_AFSEL0_Pos);
    GPIOB->AFR[0] |=  (2U   << GPIO_AFRL_AFSEL0_Pos); // pb0 af2

    TIM3->PSC = (SystemCoreClock / (4096 * 1000)) - 1;
    TIM3->ARR = 4096 - 1;



    TIM3->CCMR1 |= (6U << TIM_CCMR1_OC1M_Pos) | TIM_CCMR1_OC1PE;
    TIM3->CCMR1 |= (6U << TIM_CCMR1_OC2M_Pos) | TIM_CCMR1_OC2PE;

    TIM3->CCMR2 |= (6U << TIM_CCMR2_OC3M_Pos) | TIM_CCMR2_OC3PE;

    TIM3->CCER |= TIM_CCER_CC1E | TIM_CCER_CC2E | TIM_CCER_CC3E;


    TIM3->CCR1 = 0;
    TIM3->CCR2 = 0;
    TIM3->CCR3 = 0;


    TIM3->CR1 |= TIM_CR1_CEN;
}
