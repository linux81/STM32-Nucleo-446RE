#include "spi.h"

void SPI1_init(void){

	RCC->AHB1ENR  |= 0x11;  // Enable clock for GPIOA and GPIOE
	

	GPIOA->MODER  |= (1<<11)|(1<<13)|(1<<15);  //  PA5,PA6, PA7 => AF mode
	GPIOE->MODER  |= (1<<6);  //  PE3 => OUTPUT mode
	GPIOA->AFR[0] |= 0x55500000;  // select AF5 (SPI1) for PA5,PA6, PA7 
	RCC->APB2ENR  |= 1<<12;  // Enable clock for SPI1
  SPI1->CR1 |= SPI_CR1_MSTR | SPI_CR1_SSM | SPI_CR1_SSI | SPI_CR1_BR_1 | SPI_CR1_BR_0 | SPI_CR1_CPHA | SPI_CR1_CPOL;      // SSM

	
  SPI1->CR1    |= 0x040;      // SPI1 ENABLE	
}




void slaveSelect_ctrl(_Bool state){
if(state){
GPIOE->BSRR |= 1<<3;
}
else{
while(SPI1->SR& SPI_SR_BSY);
GPIOE->BSRR |= 1<<3;
}
};

void SPI_send(uint8_t address, uint8_t data)
{
  slaveSelect_ctrl(select);
 uint16_t Data;
	while (!(SPI1->SR & SPI_SR_TXE));	//Wait if TXE cleared, Tx FIFO is full.
	SPI1->DR = address;
	while (!(SPI1->SR & SPI_SR_RXNE));	//Wait if RNE cleared, Rx FIFO is empty.
	Data = SPI1->DR;
 
	while (!(SPI1->SR & SPI_SR_TXE));	//Wait if TXE cleared, Tx FIFO is full.
	SPI1->DR = data;
	while (!(SPI1->SR & SPI_SR_RXNE));	//Wait if RNE cleared, Rx FIFO is empty.
	Data = SPI1->DR;
 
  slaveSelect_ctrl(deselect);
}


uint8_t SPI_read(uint8_t address)
{
  slaveSelect_ctrl(select);
  address = 0x80 | address;                         // 0b10 - reading and clearing status
  uint16_t Data;
	while (!(SPI1->SR & SPI_SR_TXE));	//Wait if TXE cleared, Tx FIFO is full.
	SPI1->DR = address;
	while (!(SPI1->SR & SPI_SR_RXNE));	//Wait if RNE cleared, Rx FIFO is empty.
	Data = SPI1->DR;
 
	while (!(SPI1->SR & SPI_SR_TXE));	//Wait if TXE cleared, Tx FIFO is full.
	SPI1->DR = 0x00;
	while (!(SPI1->SR & SPI_SR_RXNE));	//Wait if RNE cleared, Rx FIFO is empty.
	Data = SPI1->DR;
 
 slaveSelect_ctrl(deselect);
 
  return Data;
}


