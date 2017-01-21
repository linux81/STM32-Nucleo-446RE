#include "stm32f446xx.h"
#include "delay.h"
#include <stdio.h>
#include "system.h"
#include "LCD2x16_piotrek.h"
#include "usart.h"

void mrugaj(void);
void zap(uint16_t znak);
void I2C3_init(void);
uint8_t buffer[8];
uint8_t d;
	
int main (void) {
SystemInit();
SystemCoreClockUpdate();
SysTick_Config(SystemCoreClock/1000);
LCD_init();

LCD_clear();
USART_init();
GPIOA->MODER  |= (1<<10);
I2C3_init();
while(1){
		switch(d){
		case 10:
   LCD_string(0,0,"zapalona");
		break;
		case 20:
			
LCD_string(0,0,"zgaszona");

			break;
		
		default:
		LCD_string(0,0,"czekanie");
		
		break;
		};
}
	}

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

void USART1_IRQHandler(void)
{ if ( USART1->SR & USART_SR_RXNE){
USART1->SR &= ~USART_SR_RXNE;
uint8_t tmp;
tmp = USART1->DR;
	switch(tmp){
		case 'a':
			GPIOA->BSRR = 1 << 5; //reset bit
		
		USART_send("zapalona");
		d=10;
		break;
		case 'b':
			
      GPIOA->BSRR = 1 << 21; //set bit
		USART_send("zgaszona");
		d=20;

			break;
		
		
		
		default:
		GPIOA->BSRR = 1 << 21; //set bit
		
		break;
		};
};
};




void I2C3_WriteChar (char Adr, char Dat)    { 
  I2C3->CR1         |= 0x0100;       // send START bit 
  while (!(I2C3->SR1 & 0x0001)) {};  // wait for START condition (SB=1)  
  I2C3->DR           = 0x20;         // slave address   -> DR & write 
  while (!(I2C3->SR1 & 0x0002)) {};  // wait for ADDRESS sent (ADDR=1)  
  int Status2        = I2C3->SR2;    // read status to clear flag 
  I2C3->DR           = Adr;          // Address in chip -> DR & write 
  while (!(I2C3->SR1 & 0x0080)) {};  // wait for DR empty (TxE) 
  I2C3->DR           = Dat;          // Dat -> DR & write 
  while (!(I2C3->SR1 & 0x0080)) {};  // wait for DR empty (TxE)  
  while (!(I2C3->SR1 & 0x0004)) {};  // wait for Byte sent (BTF) 
  I2C3->CR1         |= 0x0200;       // send STOP bit 
} 

void I2C3_init(void) {
	
	  ///* Initialize I2C3, SDA: PC9, SCL: PA8 */
  
RCC->AHB1ENR  |= 0x05;  // Enable clock for GPIOC and GPIOA
GPIOA->MODER  |= 1<<17;  // PA8 AF mode
GPIOC->MODER  |= 1<<19;  // PC9 AF mode
GPIOA->AFR[1] |= 1<<2;  // select AF4 (I2C3 SCL) for PA8 
GPIOC->AFR[1] |= 1<<6;  // select AF4 (I2C3 SDA) for PC9
//GPIOA->PUPDR  |= 0x05000;
//GPIOC->PUPDR  |= 0x05000;
GPIOA->OTYPER  |= 1<<8;
GPIOC->OTYPER |= 1<<9;
	
  // initialize I2C block 
  RCC->APB1ENR  |= 1<<23;       // Enable clock for I2C3 
  I2C3->CR2     |= 0x0008;           // clock == 8MHz!    
  I2C3->CCR     |= 0x0040;           // clock control register (270kHz) 
  I2C3->TRISE   |= 0x0009;           // rise time register 
  I2C3->CR1     |= 0x0001;           // I2C3 enable 
	
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
	
	

	
		



void zap(uint16_t znak){

	switch(znak){
		case 'a':
			GPIOA->BSRR = 1 << 5; //reset bit
		
		break;
		case 'b':
			
      GPIOA->BSRR = 1 << 21; //set bit

			break;
		
		
		
		default:
		GPIOA->BSRR = 1 << 21; //set bit
		
		break;
		};
	
		


}


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

/*void send_data_4bit(uint8_t data, uint8_t RS){
	
data=data<<1;

if(RS==1) data=data+1;

uint8_t i,a;

for(i=0;i<5;i++){

a=(data&0x10)>>4;
	
		if (a!= 0) {

		GPIOC->BSRR |= 1<<0;
}
else
{

GPIOC->BSRR |= 1<<16;
}
data=data<<1;
clk;

}
clk;
	
HD44780_E_BLINK;
	
};


void send_data_4bit(uint8_t data, uint8_t RS);
#define HD44780_E_HIGH  GPIOC->BSRR |= 1<<2 //PC2
#define HD44780_E_LOW   GPIOC->BSRR |= 1<<18
#define HD44780_E_BLINK				HD44780_E_HIGH; Delay(2); HD44780_E_LOW; Delay(2);
#define clk GPIOC->BSRR |= 1<<17;Delay(5);GPIOC->BSRR |= 1<<1; //PC1

*/
