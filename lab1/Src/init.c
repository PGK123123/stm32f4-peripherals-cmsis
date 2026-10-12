#include "init.h"

uint32_t SystemCoreClock = 16000000;

void Clock_Init(ClockSource_t source) {
    switch (source) {

        case CLOCK_HSI:
            RCC->CR |= RCC_CR_HSION; // включение тактирования
            while (!(RCC->CR & RCC_CR_HSIRDY)); // ждем пока флаг не сработает
            RCC->CFGR &= ~RCC_CFGR_SW; // очистка регистра
            RCC->CFGR |= RCC_CFGR_SW_HSI; // установка флага SW_HSI
            while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_HSI); // проверка на подтверждение
            SystemCoreClock = 16 * 1000000UL;
            break;

        case CLOCK_HSE:
            RCC->CR |= RCC_CR_HSEON;
            while (!(RCC->CR & RCC_CR_HSERDY));
            RCC->CFGR &= ~RCC_CFGR_SW;
            RCC->CFGR |= RCC_CFGR_SW_HSE;
            while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_HSE);
            SystemCoreClock = 25 * 1000000UL;
            break;

        case CLOCK_PLL:
            RCC->CR |= RCC_CR_HSEON;
            while (!(RCC->CR & RCC_CR_HSERDY));
            // 3. Настройка делителей шин: APB1 max 42 МГц (делим на 2)
            RCC->CFGR |= RCC_CFGR_PPRE1_DIV2; // APB1 = 42 МГц
            RCC->CFGR |= RCC_CFGR_PPRE2_DIV1; // APB2 = 84 МГц
            RCC->CFGR |= RCC_CFGR_HPRE_DIV1;  // AHB  = 84 МГц
            // 4. Конфигурация PLL: Вход 25 МГц -> /25 (M) * 336 (N) / 4 (P) = 84 МГц
            RCC->PLLCFGR = (25 << RCC_PLLCFGR_PLLM_Pos)      |  // M = 25 (25MHz / 25 = 1MHz)
                           (336 << RCC_PLLCFGR_PLLN_Pos)     |  // N = 336 (1MHz * 336 = 336MHz)
                           (3 << RCC_PLLCFGR_PLLP_Pos)       |  // P = 8 (3 это 11 соответствует /8 -> 336/8 = MHz)
                           (7 << RCC_PLLCFGR_PLLQ_Pos)       |  // Q = 7 (для USB 48MHz)
                           RCC_PLLCFGR_PLLSRC_HSE;              // Источник - HSE
            RCC->CR |= RCC_CR_PLLON;
            while (!(RCC->CR & RCC_CR_PLLRDY));
            RCC->CFGR &= ~RCC_CFGR_SW;
            RCC->CFGR |= RCC_CFGR_SW_PLL;
            while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL);
            SystemCoreClock = 42 * 1000000UL;
            break;
    }
}
