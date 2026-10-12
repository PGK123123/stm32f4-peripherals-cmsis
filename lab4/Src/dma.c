#include "dma.h"

volatile uint16_t adc_result[DMA_DATA_COUNT];

void dma_init(void){
	RCC->AHB1ENR |= RCC_AHB1ENR_DMA2EN;

	DMA2_Stream0->CR &= ~DMA_SxCR_EN;
	while (DMA2_Stream0->CR & DMA_SxCR_EN);

	DMA2->LIFCR = DMA_LIFCR_CTCIF0 | DMA_LIFCR_CHTIF0 |
	              DMA_LIFCR_CTEIF0 | DMA_LIFCR_CDMEIF0 |
	              DMA_LIFCR_CFEIF0;

	DMA2_Stream0->CR |= (
			( 0 << DMA_SxCR_CHSEL_Pos  )  |
			( 3UL  << DMA_SxCR_PL_Pos  )  |
			( 1UL << DMA_SxCR_MSIZE_Pos)  |
			( 1UL << DMA_SxCR_PSIZE_Pos ) |
			( 1UL << DMA_SxCR_MINC_Pos )  |
			( 0UL << DMA_SxCR_PINC_Pos )  |
			( 1UL << DMA_SxCR_CIRC_Pos )
	);
	DMA2_Stream0->NDTR = DMA_DATA_COUNT;

	DMA2_Stream0->PAR = (uint32_t) &ADC1->DR;

	DMA2_Stream0->M0AR = (uint32_t) adc_result;

	DMA2_Stream0->CR |= DMA_SxCR_EN;
}
