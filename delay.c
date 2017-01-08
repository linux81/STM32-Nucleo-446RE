#include "delay.h"
__IO uint32_t TimmingDelay;

void Delay(__IO uint32_t time)
{
TimmingDelay = time;
while(TimmingDelay !=0);
};



void SysTick_Handler(void)
{
if(TimmingDelay !=0)
{
TimmingDelay --;
}
};

