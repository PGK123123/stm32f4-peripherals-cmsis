#include "adc.h"
#include "systick.h"

void adc_init(void) {
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;


    GPIOA->MODER |= (3UL << (1 * 2));


    ADC->CCR |= ADC_CCR_TSVREFE;


    ADC1->SMPR2 |= (4UL << ADC_SMPR2_SMP1_Pos);
    ADC1->SMPR1 |= (7UL << ADC_SMPR1_SMP16_Pos);


    ADC1->SQR1 &= ~ADC_SQR1_L;
    ADC1->SQR1 |= (1UL << ADC_SQR1_L_Pos); // 2 измерения
    ADC1->SQR3 &= ~(ADC_SQR3_SQ1 | ADC_SQR3_SQ2);
    ADC1->SQR3 |= (1UL << ADC_SQR3_SQ1_Pos) | (16UL << ADC_SQR3_SQ2_Pos);


    ADC1->CR1 |= ADC_CR1_SCAN;
    ADC1->CR2 |= ADC_CR2_CONT;

    ADC1->CR2 |= ADC_CR2_DMA | ADC_CR2_DDS;

    ADC1->CR2 |= ADC_CR2_ADON;
    delay_ms(3);

    ADC1->CR2 |= ADC_CR2_SWSTART;
}

float get_temperature(uint16_t adc_val){
	float vsense = (float)adc_val * 3.3f / 4095.0f;
	return ((vsense - 0.76f) / 0.0025f) + 25.0f;
}

uint16_t adc_read_value(uint8_t channel) {

    ADC1->SQR3 = (channel << ADC_SQR3_SQ1_Pos);

    ADC1->CR2 |= (1 << ADC_CR2_SWSTART_Pos);

    while (!(ADC1->SR & (1 << ADC_SR_EOC_Pos))) {
        __NOP();
    }

    ADC1->SR &= ~(1 << ADC_SR_EOC_Pos);

    return ADC1->DR;
}
