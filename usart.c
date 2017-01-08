#include "stm32f446xx.h"
#include "usart.h" 




void USART_send(uint8_t *value){
while (*value)
    {
		while ((USART1->SR & USART_SR_TXE) == 0){;}
		if (*value == '\0')
			USART1->DR = ('\r');
		else
			USART1->DR = (*value++);
    }
};


uint8_t USART_rec(void)
{
	char Data;
	
    while ((USART1->SR & USART_SR_RXNE)){
			USART1->SR&= ~USART_SR_RXNE;
			Data = USART1->DR;
			
		}
    
    // read RX data, combine with DR mask (we only accept a max of 9 Bits)
    return Data & 0x1FF;
};


void USART_init(void) {
	
	RCC->AHB1ENR |=  (1ul << 0); // Enable clock for GPIOA
	
	GPIOA->MODER  |= (1<<19)|(1<<21);  // PA9, PA10 => AF mode

	
  GPIOA->AFR[1] |= 0x770;   // select AF7 (USART1) for PA9, PA10 
	//GPIOA->PUPDR  |= (1<<18)|(1<<20)|(1<<0);
  
	RCC->APB2ENR  |= 1<<4;  // Enable clock for USART1
  USART1->BRR     = 100000000/9600;      // 9600 baud 

  USART1->CR1    |= USART_CR1_TE | USART_CR1_RE|USART_CR1_UE|USART_CR1_RXNEIE;      // Enable UART for TX, RX
	NVIC_EnableIRQ(USART1_IRQn);

//USART_CR1_RXNEIE	
	
	
};




