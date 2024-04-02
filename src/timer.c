#include "stm32f4xx.h"
#include "led.h"

void SysTick_Timer_Configuration(uint32_t ticks)
{
	SysTick->CTRL = 0x3;		//bit-1: TICKIINT - sysTick exception enable
								//bit-2: CLKSRC	 - Processor clock
	SysTick->LOAD = (ticks - 1);
	SysTick->VAL  = 0x0;
}

void Start_Timer(void)
{
	SysTick->CTRL |= (1<<0);	//Enable Counter
}

void SysTick_Handler(void)
{
	LED_Toggle(GPIOD, 12);
}
