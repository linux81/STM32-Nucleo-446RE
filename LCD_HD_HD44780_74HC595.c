/*
 *	Default pinout
 *	
 *	LCD		STM32F446/74HC595		DESCRIPTION
 *	
 *	GND		GND				Ground
 *	VCC		+5V				Power supply for LCD
 *	V0		Potentiometer	Contrast voltage. Connect to potentiometer
 *	RS		Q0				Register select, can be overwritten in your project’s defines.h file
 *	RW		GND				Read/write
 *	E		PC2				Enable pin, can be overwritten in your project’s defines.h file
 *	D0		-				Data 0 – doesn’t care
 *	D1		-				Data 1 - doesn’t care
 *	D2		-				Data 2 - doesn’t care
 *	D3		-				Data 3 - doesn’t  care
 *	D4		Q1			Data 4, can be overwritten in your project’s defines.h file
 *	D5		Q2			Data 5, can be overwritten in your project’s defines.h file
 *	D6		Q3			Data 6, can be overwritten in your project’s defines.h file
 *	D7		Q4			Data 7, can be overwritten in your project’s defines.h file
 *	A		+3V3			Backlight positive power
 *	K		GND				Ground for backlight

*/

#include "stm32f446xx.h" 
#define HD44780_E_HIGH  GPIOC->BSRR |= 1<<2 //PC2
#define HD44780_E_LOW   GPIOC->BSRR |= 1<<18
#define HD44780_E_BLINK				HD44780_E_HIGH; Delay(1); HD44780_E_LOW; Delay(1); //bylo 2ms
#define clk GPIOC->BSRR |= 1<<17;Delay(1);GPIOC->BSRR |= 1<<1; //PC1
#include "LCD2x16_piotrek.h" 
#include "delay.h"


void send_data_4bit(uint8_t data, uint8_t RS){
	
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


void HD44780_Cmd(uint8_t cmd) {
	//HD44780_RS_LOW;
	
	send_data_4bit((cmd >> 4),0);			//High nibble
	send_data_4bit((cmd & 0x0F),0);			//Low nibble
};

void HD44780_Data(uint8_t data) {
	//HD44780_RS_HIGH;
	
	send_data_4bit((data >> 4),1);			//High nibble
	send_data_4bit((data & 0x0F),1);			//Low nibble
};

//--------------------------------------------------------------
// Ausgabe von einem String auf dem Display an x,y Position
// x : 0 bis 15
// y : 0 bis 1
//--------------------------------------------------------------
void HD44780_Cursor(uint8_t x, uint8_t y)
{
  uint8_t wert;

  if(x>=16) x=0;
  if(y>=2) y=0;

  wert=(y<<6);
  wert|=x;
  wert|=0x80;
  HD44780_Cmd(wert);
};

void LCD_string(uint8_t x, uint8_t y,char *str) {

    HD44780_Cursor(x,y); 
	
	while (*str != '\0') {                // send all characters in a string
    HD44780_Data (*str++);
  }
};







void LCD_init (void) {
  RCC->AHB1ENR |=  (1<<2);      // Enable clock for GPIOC AND GPIOH
  GPIOC->MODER |=  (1<<0)|(1<<2)|(1<<4); 
  //GPIOA->MODER |=  0x5; // MODE Register: lower 6 bits are outputs
GPIOC->PUPDR  |= 0x2A;
  
  
  HD44780_Cmd(0x03);        Delay(5);
  HD44780_Cmd(0x03);        Delay(5);
  HD44780_Cmd(0x03);        Delay(5);
  HD44780_Cmd(0x02);        Delay(5);
  HD44780_Cmd(0x28);
  HD44780_Cmd(0x0c);
  HD44780_Cmd(0x01);
  HD44780_Cmd(0x06);
  Delay(5);       
};


void LCD_clear (void){

HD44780_Cmd(0x01);
Delay(5);
};


void HD44780_ScrollLeft(void) {
	HD44780_Cmd(HD44780_CURSORSHIFT | HD44780_DISPLAYMOVE | HD44780_MOVELEFT);
};

void HD44780_ScrollRight(void) {
	HD44780_Cmd(HD44780_CURSORSHIFT | HD44780_DISPLAYMOVE | HD44780_MOVERIGHT);
};

/*void HD44780_Cmd4bit(  uint8_t cmd) {
	writebit(cmd, 0x08, 0x08);// D7
	writebit(cmd, 0x04, 0x04);
	writebit(cmd, 0x02, 0x02);
	writebit(cmd, 0x01, 0x01);
	HD44780_E_BLINK;
};*/
