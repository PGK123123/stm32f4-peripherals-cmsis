#include "button.h"


volatile int8_t direction = 1;

void button_init() {
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;

    GPIOB->MODER &= ~GPIO_MODER_MODER12;

    GPIOB->PUPDR &= ~GPIO_PUPDR_PUPD12;
    GPIOB->PUPDR |=  GPIO_PUPDR_PUPD12_0; // 3.3V

    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN; // тактирование SYSCFG
    SYSCFG->EXTICR[3] |= SYSCFG_EXTICR4_EXTI12_PB; // PB 12 источник прерывания

    EXTI->IMR |= (1U << 12); // разрешаем прерывания 12 линии
    EXTI->FTSR |= (1U << 12); // прерывание генерируется по спаду сигнала т.к. подтяжка 3.3 а кнопка коммутирует землю

    NVIC_EnableIRQ(EXTI15_10_IRQn);


}

void EXTI15_10_IRQHandler(void) {
	if (EXTI->PR & (1U << 12)){
		EXTI->PR = (1U << 12);
		EXTI->IMR &= ~(1U << 12); // маскируем прерывания дальнейшие, чтобы не ловить дребезг

		TIM4->CNT = 0;
		TIM4->CR1 |= TIM_CR1_CEN;

	}
}
