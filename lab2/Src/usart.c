#include "usart.h"

void usart2_init(void){
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    RCC->APB1ENR |= RCC_APB1ENR_USART2EN;

    GPIOA->MODER &= ~(GPIO_MODER_MODE3 | GPIO_MODER_MODE2);
    GPIOA->MODER |= GPIO_MODER_MODE3_1  | GPIO_MODER_MODE2_1;

    GPIOA->AFR[0] &= ~(GPIO_AFRL_AFSEL3 | GPIO_AFRL_AFSEL2);
    GPIOA->AFR[0] |= (7U << GPIO_AFRL_AFSEL3_Pos) | (7U << GPIO_AFRL_AFSEL2_Pos);

    GPIOA->PUPDR |= GPIO_PUPDR_PUPD3_0;

    USART2->CR1 &= ~USART_CR1_M;      // 8 Data bit
    USART2->CR2 &= ~USART_CR2_STOP;   // 1 Stop bit

    uint32_t pclk1 = (SystemCoreClock > 42000000UL) ? (SystemCoreClock / 2) : SystemCoreClock;

    USART2->BRR = (pclk1 + (115200UL / 2)) / 115200UL;


    USART2->CR1 |= (USART_CR1_TE | USART_CR1_RE);
    USART2->CR1 |= USART_CR1_UE;
}

void usart2_send_char(char c){
    while (!(USART2->SR & USART_SR_TXE));
    USART2->DR = (uint8_t)c;
}

void usart2_send_num(uint32_t num){
	char buf[11]; // буфер под цифры числа
	int i = 0;

	if (num == 0) {
		usart2_send_char('0');
		return;
	}
	while (num > 0) {
	    buf[i++] = (num % 10) + '0';
	    num /= 10;
	    }

	while (--i >= 0) {
	   usart2_send_char(buf[i]);
	}
}

void usart2_send_string(const char *str){
    while (*str) {
        usart2_send_char(*str++);
    }
}
