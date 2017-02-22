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
#define   CNT_FREQ          50000000                             // TIM6 counter clock (prescaled APB1)
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

LCD_init();

LCD_clear();
USART_init();
	RCC->AHB1ENR |=  (1<<0);
	
  GPIOA->MODER  |= (1<<10)|(11<<8)|(11<<10);
	RCC->APB1ENR  |= 1<<29; // DAC 
	RCC->AHB1ENR  |= 1<<21; // DMA1 
	//NVIC_EnableIRQ(TIM7_IRQn);
	RCC->APB1ENR  |= 1<<4;  // Enable clock for TIM6
  TIM6->PSC = 0;
  TIM6->ARR =(uint16_t)TIM_PERIOD;
	//TIM7->DIER |=0x01;
TIM6->CR2 |= 1<<5;
TIM6->CR1 |= TIM_CR1_CEN;


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

void USART1_IRQHandler(void)
{ if ( USART1->SR & USART_SR_RXNE){
USART1->SR &= ~USART_SR_RXNE;
	uint8_t tmp;
	tmp = USART1->DR;
	o=tmp;
};
};










	//LED_Initialize();
		//RCC->AHB1ENR |=  (1ul << 0);                  /* Enable GPIOA clock         */


 // GPIOA->MODER   |=(1<<1)|(1<<3)|(1<<5)|(1<<7);
	//GPIOA->MODER   |=1<<13;

	//GPIOA->AFR[0] |= (1<<1)|(1<<5)|(1<<9)|(1<<13);
	//GPIOA->AFR[0] |= 1<<25;

	//RCC->APB1ENR  |= 0x01;  // Enable clock for TIM2
	//RCC->APB1ENR  |= 0x02;  // Enable clock for TIM3
	//RCC->APB1ENR  |= 1<<3;;  // Enable clock for TIM5
  //TIM5->PSC = 1;
  //TIM5->ARR =2400;
	//TIM5->CCMR1 |= 0x6060; // Toggle output 1 & 2 on compare match
	//TIM5->CCMR2 |= 0x6060;
	//TIM5->CCR1 |= 400;
	//TIM5->CCR2 |= 1200;
	//TIM5->CCR3 |= 400;
	//TIM5->CCR4 |= 1200;
  //TIM2->SMCR |= 0x5;
	//TIM2->SMCR |= 0x20;
	//TIM5->CCER |= TIM_CCER_CC1E|TIM_CCER_CC2E|TIM_CCER_CC3E|TIM_CCER_CC4E;
	//TIM5->CR1 |= TIM_CR1_CEN; // Enable timer
//
  //TIM3->PSC = 1;
  //TIM3->ARR =1200;
	//TIM3->CR2 |= 1<<6;
	
//TIM3->CCR1 |= 20000;
	//TIM3->SMCR |= 1<<7;
	//TIM3->CCMR1 |= 0x30;
	//TIM3->CCER |= TIM_CCER_CC1E;

  //TIM3->CR1 |= TIM_CR1_CEN;
	
	/*sprintf(buffer, "%u \n",i);
		LCD_string(0,0,buffer);
		USART_send(buffer);*/

	
		






//sprintf(buffer, "%u \n",b);
//USART_init();
	  /*RCC->AHB1ENR |=  (1ul << 0); // Enable clock for GPIOA
	
	//GPIOA->MODER  |= (1<<19)|(1<<21);  // PA9, PA10 => AF mode
	GPIOA->MODER  |= (1<<10);
	
  GPIOA->AFR[1] |= 0x770;   // select AF7 (USART1) for PA9, PA10 
	GPIOA->PUPDR  |= (1<<18)|(1<<20)|(1<<0);
  
	RCC->APB2ENR  |= 1<<4;  // Enable clock for USART1
  USART1->BRR     = 100000000/9600;      // 9600 baud 

  USART1->CR1    |= USART_CR1_TE | USART_CR1_RE|USART_CR1_UE|USART_CR1_RXNEIE;      // Enable UART for TX, RX
	NVIC_EnableIRQ(USART1_IRQn);*/	
	
	//NVIC_EnableIRQ(TIM7_IRQn);
	
	//RCC->APB1ENR  |= 0x020;  // Enable clock for TIM7
 // TIM7->PSC = 400;
	//TIM7->ARR =15000;
	//TIM7->DIER |=0x01;
	
  //TIM7->CR1 |= 0x05;

		//USART_CR1_RXNEIE
//USART_CR1_UE
	//mrugaj();
//LCD_init();

//LCD_clear();
//LCD_string(0,0,"molek");


/*
void USART1_IRQHandler(void)
{ if ( USART1->SR & USART_SR_RXNE){
USART1->SR &= ~USART_SR_RXNE;
uint8_t tmp;
tmp = USART1->DR;
	switch(tmp){
		case 'a':
			GPIOA->BSRR = 1 << 5; //reset bit
		
		USART_send("zapalona ");
		o=10;
		break;
		case 'b':
			
      GPIOA->BSRR = 1 << 21; //set bit
		USART_send("zgaszona ");
		o=20;

			break;
		
		
		
		default:
		GPIOA->BSRR = 1 << 21; //set bit
		
		break;
		};
};
};


*/

/*void TIM7_IRQHandler(void)
{ if(TIM7->SR & TIM_SR_UIF) // if UIF flag is set
{ TIM7->SR &= ~TIM_SR_UIF; // clear UIF flag
if ((GPIOA->IDR&0x01)==0){
	b+=1;
}
	if(b==3){
	
 USART_send("nacisniety ");
		a=1;
		
		b=0;
	}
	
};
};*/
