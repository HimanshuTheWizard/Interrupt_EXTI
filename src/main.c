#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"
#include "cmsis_device.h"
#include <stdio.h>
#include <stdlib.h>
#include "diag/trace.h"
#include "led.h"
#include "timer.h"

#define PROCESSOR_CLOCK			(16000000)				//16MHz
#define PROCESSOR_CLOCK_MS		(PROCESSOR_CLOCK/1000)

void main(void)
{
#if 0
	/* ===========================================================
	 * EXTI0 Interrupt with LED and Push Button Interface
	 * ==========================================================*/
	//enable clock for LED D3 - PORT-D(12)
	RCC->AHB1ENR 	|= (1<<3);

	//enable clock for SWITCH - PORT-A(0)
	RCC->AHB1ENR 	|= (1<<0);

	//enable clock for SYSCFG
	RCC->APB2ENR 	|= (1<<14);

	//Init LED
	LED_Init(GPIOD, 12);

	//Enable Switch in EXTI interrupt mode
	Interrupt_Initialization(GPIOA, 0);

	while(1)
	{
		if(pressed)
		{
			LED_Toggle(GPIOD, 12);
			pressed = 0;
		}
	}
#endif

#if 0
	/* ===========================================================
	 * LED and Push Button Interface
	 * ==========================================================*/
	//enable clock for LED D3 - PORT-D(12)
	RCC->AHB1ENR 	|= (1<<3);

	//enable clock for SWITCH - PORT-A(0)
	RCC->AHB1ENR 	|= (1<<0);

	//Init LED
	LED_Init(GPIOD, 12);

	//Init Push button
	Push_Btn_Init(GPIOA, 0);

	while(1)
	{
		if((Push_Btn_Status(GPIOA, 0)) && (pressed == 0))
		{
			LED_Toggle(GPIOD, 12);
			pressed = 1;
		}
		else if((Push_Btn_Status(GPIOA, 0) == 0) && (pressed == 1))
		{
			pressed = 0;
		}
	}
#endif

#if 0
	/* ===========================================================
	 * Systick Timer
	 * ==========================================================*/
	uint32_t time_unit = 1000;							//ms

	//enable clock for LED D3 - PORT-D(12)
	RCC->AHB1ENR 	|= (1<<3);

	//Configure systick timer
	SysTick_Timer_Configuration(time_unit*PROCESSOR_CLOCK_MS);

	//Init LED
	LED_Init(GPIOD, 12);

	//start timer
	Start_Timer();

	while(1);
#endif
}








