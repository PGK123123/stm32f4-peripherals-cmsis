#include "adc.h"

void adc_init(){
	RCC->AHB1ENR |= (1 << RCC_AHB1ENR_GPIOAEN_Pos);
	RCC->APB2ENR |= (1 << RCC_APB2ENR_ADC1EN_Pos);

	GPIOA->MODER |= (3 << GPIO_MODER_MODE1_Pos | 3 << GPIO_MODER_MODE0_Pos);

	ADC1->CR2 |= (1 << ADC_CR2_ADON_Pos);
	ADC1->SQR3 = (1 << ADC_SQR3_SQ1_Pos);
}

uint16_t adcReadValue(uint8_t channel) {

    ADC1->SQR3 = (channel << ADC_SQR3_SQ1_Pos);

    ADC1->CR2 |= (1 << ADC_CR2_SWSTART_Pos);

    while (!(ADC1->SR & (1 << ADC_SR_EOC_Pos))) {
        __NOP();
    }

    ADC1->SR &= ~(1 << ADC_SR_EOC_Pos);

    return ADC1->DR;
}
