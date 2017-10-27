#include "stm32f446xx.h"
#include "LCD2x16_piotrek.h"
	void RTC_init (void);
uint8_t buffer[30];
uint8_t buffer1[30];
	void show_date(void);
	
	
	
	void RTC_init (void) {
	RCC->APB1ENR |= RCC_APB1ENR_PWREN;

PWR->CR |=PWR_CR_DBP;	
	
	RCC->BDCR |= ((uint32_t)RCC_BDCR_LSEON);                     /* Enable LSE */
  while ((RCC->BDCR & RCC_BDCR_LSERDY) == 0);
RCC->BDCR |=(1<<8);
RCC->BDCR |=(1<<8);
RCC->BDCR |=(1<<15);
  RTC->WPR =0xCA;
	RTC->WPR =0x53;
	RTC->ISR |=RTC_ISR_INIT;
	
	 while ((RTC->ISR & RTC_ISR_INITF) == 0);
	RTC->TR |=(2<<20)|(1<<16)|(4<<12)|(5<<8);
	RTC->DR |=(1<<20)|(7<<16)|(5<<13)|(0<<12)|(7<<8)|(2<<4)|(5<<0);
	
	
	RTC->ISR &= ~RTC_ISR_INIT;
	RTC->WPR = 0xFF;
	while ((RTC->ISR & RTC_ISR_RSF) == 0);      
};
	

	
	
	void show_date(void){
volatile uint16_t a,b,c,d,e,f,g,h,i,j,k,l,m;
	a=((RTC->TR)&((1<<21)|(1<<20)))>>20;
b=((RTC->TR)&((1<<19)|(1<<18)|(1<<17)|(1<<16)))>>16;
c=((RTC->TR)&((1<<14)|(1<<13)|(1<<12)))>>12;
d=((RTC->TR)&((1<<11)|(1<<10)|(1<<9)|(1<<8)))>>8;
e=((RTC->TR)&((1<<6)|(1<<5)|(1<<4)))>>4;
f=((RTC->TR)&((1<<3)|(1<<2)|(1<<1)|(1<<0)));
g=((RTC->DR)&((1<<23)|(1<<22)|(1<<21)|(1<<20)))>>20;
h=((RTC->DR)&((1<<19)|(1<<18)|(1<<17)|(1<<16)))>>16;
i=((RTC->DR)&((1<<15)|(1<<14)|(1<<13)))>>13;
j=((RTC->DR)&(1<<12))>>12;
k=((RTC->DR)&((1<<11)|(1<<10)|(1<<9)|(1<<8)))>>8;
l=((RTC->DR)&((1<<5)|(1<<4)))>>4;
m=((RTC->DR)&((1<<3)|(1<<2)|(1<<1)|(1<<0)));

sprintf(buffer, "%d%d %d%d %d%d",a,b,c,d,e,f);
sprintf(buffer1, "20%d%d %d %d%d %d%d",g,h,i,j,k,l,m);

	LCD_string(0,0,buffer);
	LCD_string(0,1,buffer1);
	
};
	
	
	
	
	
	
