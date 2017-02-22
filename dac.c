#include "stm32f446xx.h"
#include "delay.h"
#include <stdio.h>
#include "system.h"
#include "LCD2x16_piotrek.h"
#include "usart.h"
//#include "i2c.h"
//#include "spi.h"
#define   OUT_FREQ          5000                                 // Output waveform frequency
#define   SINE_RES          128                                  // Waveform resolution
#define   DAC_DHR12R1_ADDR  0x40007408                           // DMA writes into this reg on every request
#define   CNT_FREQ          100000000                             // TIM6 counter clock (prescaled APB1)
#define   TIM_PERIOD        ((CNT_FREQ)/((SINE_RES)*(OUT_FREQ))) // Autoreload reg value

const uint16_t function[SINE_RES] = { 2048, 2145, 2242, 2339, 2435, 2530, 2624, 2717, 2808, 2897, 
                                      2984, 3069, 3151, 3230, 3307, 3381, 3451, 3518, 3581, 3640, 
                                      3696, 3748, 3795, 3838, 3877, 3911, 3941, 3966, 3986, 4002, 
                                      4013, 4019, 4020, 4016, 4008, 3995, 3977, 3954, 3926, 3894, 
                                      3858, 3817, 3772, 3722, 3669, 3611, 3550, 3485, 3416, 3344, 
                                      3269, 3191, 3110, 3027, 2941, 2853, 2763, 2671, 2578, 2483, 
                                      2387, 2291, 2194, 2096, 1999, 1901, 1804, 1708, 1612, 1517, 
                                      1424, 1332, 1242, 1154, 1068, 985, 904, 826, 751, 679, 
                                      610, 545, 484, 426, 373, 323, 278, 237, 201, 169, 
                                      141, 118, 100, 87, 79, 75, 76, 82, 93, 109, 
                                      129, 154, 184, 218, 257, 300, 347, 399, 455, 514, 
                                      577, 644, 714, 788, 865, 944, 1026, 1111, 1198, 1287, 
                                      1378, 1471, 1565, 1660, 1756, 1853, 1950, 2047 };




	
int main (void) {
SystemInit();
SystemCoreClockUpdate();
SysTick_Config(SystemCoreClock/1000);

//LCD_init();

//LCD_clear();
//USART_init();
	RCC->AHB1ENR |=  (1<<0);
	
  GPIOA->MODER  |= (1<<10)|(11<<8)|(11<<10);
	RCC->APB1ENR  |= 1<<29; // DAC 
	RCC->AHB1ENR  |= 1<<21; // DMA1 
	//NVIC_EnableIRQ(TIM7_IRQn);
	RCC->APB1ENR  |= 1<<4;  // Enable clock for TIM6
  TIM6->PSC = 0;
  TIM6->ARR =(uint16_t)TIM_PERIOD;
	//TIM7->DIER |=0x01;
TIM6->CR2 |= TIM_CR2_MMS_1;
TIM6->CR1 |= TIM_CR1_CEN;
	
DAC->CR |= DAC_CR_TEN1;


DMA1_Stream5->CR |= DMA_SxCR_CHSEL|DMA_SxCR_PL|DMA_SxCR_MSIZE_0|DMA_SxCR_PSIZE_0|DMA_SxCR_MINC|DMA_SxCR_CIRC|DMA_SxCR_DIR_0;
DMA1_Stream5->PAR |=(uint32_t)DAC_DHR12R1_ADDR;
DMA1_Stream5->NDTR |=SINE_RES;
DMA1_Stream5->M0AR |=(uint32_t)&function;
DMA1_Stream5->FCR |=DMA_SxFCR_FTH_0;
DMA1_Stream5->CR |=DMA_SxCR_EN;
DAC->CR |= DAC_CR_EN1;
DAC->CR |= DAC_CR_DMAEN1;
while(1){
}
	}

/*void TIM7_IRQHandler(void)
{ if(TIM7->SR & TIM_SR_UIF) // if UIF flag is set
{ TIM7->SR &= ~TIM_SR_UIF; // clear UIF flag
LCD_string(0,0,"molek");
LCD_string(0,1,"manuk");
};
};*/

/*void USART1_IRQHandler(void)
{ if ( USART1->SR & USART_SR_RXNE){
USART1->SR &= ~USART_SR_RXNE;

};
};*/










	
