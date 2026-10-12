#include "i2c.h"

void i2c_init(void){
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOBEN;
	RCC->APB1ENR |= RCC_APB1ENR_I2C3EN;

	GPIOA->MODER &= ~GPIO_MODER_MODE8;
	GPIOA->MODER |= GPIO_MODER_MODE8_1;

	GPIOA->OTYPER |= GPIO_OTYPER_OT8;

	GPIOA->PUPDR |= GPIO_PUPDR_PUPD8_0;

	GPIOB->MODER &= ~GPIO_MODER_MODE4;
	GPIOB->MODER |= GPIO_MODER_MODE4_1;

	GPIOB->OTYPER |= GPIO_OTYPER_OT4;

	GPIOB->PUPDR |= GPIO_PUPDR_PUPD4_0;

	GPIOA->AFR[1] &= ~GPIO_AFRH_AFRH0;
	GPIOA->AFR[1] |= 4UL;

	GPIOB->AFR[0] &= ~GPIO_AFRL_AFRL4;
	GPIOB->AFR[0] |= (9UL << GPIO_AFRL_AFSEL4_Pos);

	I2C3->CR1 |= I2C_CR1_SWRST;
	I2C3->CR1 &= ~I2C_CR1_SWRST;

	uint32_t pclk1 = (SystemCoreClock > 42000000UL) ? (SystemCoreClock / 2) : SystemCoreClock;
	uint32_t freq_mhz = pclk1 / 1000000UL;


	I2C3->CR2 &= ~I2C_CR2_FREQ;
	I2C3->CR2 |= (freq_mhz << I2C_CR2_FREQ_Pos);

	// 2. CCR для 100 кГц
	I2C3->CCR &= ~I2C_CCR_CCR;
	I2C3->CCR |= ((pclk1 / 200000UL) << I2C_CCR_CCR_Pos);

	I2C3->TRISE = freq_mhz + 1;

	I2C3->CR1 |= I2C_CR1_PE;
}

uint8_t i2cWriteRegister(uint8_t dev_addr, uint8_t reg_addr, uint8_t *data, uint16_t len){

	while (I2C3->SR2 & I2C_SR2_BUSY);

	I2C3->CR1 |= I2C_CR1_START;
	while (!(I2C3->SR1 & I2C_SR1_SB ));

	I2C3->DR = (dev_addr << 1); // 0x3C -> 0x78
	while (!(I2C3->SR1 & I2C_SR1_ADDR));

	(void)I2C3->SR1;
	(void)I2C3->SR2;

	I2C3->DR = reg_addr;
	while (!(I2C3->SR1 & I2C_SR1_TXE));

	for (uint16_t i = 0; i < len; i++) {
	    I2C3->DR = data[i];
	    while (!(I2C3->SR1 & I2C_SR1_TXE));
	}
	while(!(I2C3->SR1 & I2C_SR1_BTF));

	I2C3->CR1 |= I2C_CR1_STOP;
    while (I2C3->CR1 & I2C_CR1_STOP);

	return 0;
}
