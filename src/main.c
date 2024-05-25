#include <gpio.h>
#include <stdio.h>
#include <stdlib.h>
#include "diag/trace.h"
#include "timer.h"
#include "adc.h"
#include "spi.h"

/*local macros*/
#define PROCESSOR_CLOCK			(16000000)				//16MHz
#define PROCESSOR_CLOCK_MS		(PROCESSOR_CLOCK/1000)


/*global variable definition*/
volatile uint16_t H = 100;
volatile uint16_t L = 900;
volatile uint8_t pressed = 0;
volatile uint32_t ADC_data = 0;
volatile uint32_t sysTickCounter = 0;

/*function prototype*/
void EXTI_Button_Press_Callback(void);
void SysTick_Led_Toggle_Callback(void);
void SysTick_PWM_Callback(void);
void ADC_Data_Read_callback(uint32_t data);
void delay_ms_callback(void);
void delay_ms(uint32_t ms);

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
	EXTI_Interrupt_Initialization(GPIOA, 0);

	//configure EXTI0 interrupt
	EXTI0_Interrupt_Config();

	while(1)
	{
		if(pressed)
		{
			LED_Toggle(GPIOD, 12);
			pressed = 0U;
		}
	}
#endif

#if 0
	/* ===========================================================
	 * LED and Push Button Interface - polling mode
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
	 * Toggle LED with SysTick Timer
	 * ==========================================================*/
	uint32_t time_unit = 1000;							//ms

	//enable clock for LED D3 - PORT-D(12)
	RCC->AHB1ENR 	|= (1<<3);

	//Callback registering
	Timer_Registering_Function(&SysTick_Led_Toggle_Callback);

	//Configure systick timer
	SysTick_Timer_Configuration(time_unit*PROCESSOR_CLOCK_MS);

	//Init LED
	LED_Init(GPIOD, 12);

	//start timer
	Start_Timer();

	while(1);
#endif

#if 0

	/* ===========================================================
	 * Timer, PWM, GPIO and push button interface
	 * ==========================================================*/

	// L = 500ms H = 500ms
	// Duty Cycle = H+L = 1000ms

	//enable clock for LED D3 - PORT-D(12)
	RCC->AHB1ENR 	|= (1<<3);

	//enable clock for SWITCH - PORT-A(0)
	RCC->AHB1ENR 	|= (1<<0);

	//Callback registering
	EXTI_Registering_function(&EXTI_Button_Press_Callback);
	Timer_Registering_Function(&SysTick_PWM_Callback);

	//Init LED
	LED_Init(GPIOD, 12);

	//Configure systick timer
	SysTick_Timer_Configuration((H+L)*PROCESSOR_CLOCK_MS);

	//Enable Switch in EXTI interrupt mode
	EXTI_Interrupt_Initialization(GPIOA, 0);
	EXTI0_Interrupt_Config();

	while(1)
	{
		if(pressed == 1)
		{
			if(H < 1000)
			{
				H = H + 100;
				L = 1000 - H;
			}
			else
			{
				H = 100;
				L = 1000 - H;
			}
			pressed = 0;
		}
	}

#endif

#if 0

	/* ===========================================================
	 * ADC - Interrupt mode
	 * ==========================================================*/

	uint32_t time_unit = 1000;							//ms

	//Enable clock for GPIOC - PC0 to be used as ADC1_10
	RCC->AHB1ENR |= (1<<2);

	//Enable clock for ADC1
	RCC->APB2ENR |= (1<<8);

	//configure sysTick with 1 ms frequency
	SysTick_Timer_Configuration(time_unit*PROCESSOR_CLOCK_MS);

	//callback registering function
	Timer_Registering_Function(&delay_ms_callback);
	ADC_Callback_Registering(&ADC_Data_Read_callback);

	//enable ADC pins
	ADC_Pin_Init(GPIOC, 0);

	//ADC interrupt configure through NVIC
	ADC1_Interrupt_Configuration();

	//ADC interrupt configure
	ADC1_Configuration();

	//start ADC conversion
	ADC1_Start_Conversion();

	while(1);

#endif

#if 1
	uint32_t time_unit = 1000;							//ms

	//Enable clock for SPI1
	RCC->APB2ENR |= (1<<12);

	//Enable clock for port A
	RCC->AHB1ENR |= (1<<0);

	//configure sysTick with 1 ms frequency
	SysTick_Timer_Configuration(time_unit*PROCESSOR_CLOCK_MS);

	//callback registering function
	Timer_Registering_Function(&delay_ms_callback);

	SPI_GPIO_Init();

	SPI_Init();

	acc_init();

	GPIOE->BSRR |= GPIO_BSRR_BS3;

	while(1)
	{
		acc_read();
		delay_ms(20);
	}
#endif

}

void EXTI_Button_Press_Callback(void)
{
	pressed = 1;
}

void SysTick_Led_Toggle_Callback(void)
{
	LED_Toggle(GPIOD, 12);
}

void SysTick_PWM_Callback(void)
{
	if(Output_Pin_Status(GPIOD, 12) == 1)		//LED == high
	{
		LED_Low(GPIOD, 12);
		SysTick->LOAD = ((L*PROCESSOR_CLOCK_MS) - 1);
	}
	else										//LED == low
	{
		LED_High(GPIOD, 12);
		SysTick->LOAD = ((H*PROCESSOR_CLOCK_MS) - 1);
	}
}
void ADC_Data_Read_callback(uint32_t data)
{
	ADC_data = data;
}

void delay_ms_callback(void)
{
	if(sysTickCounter != 0)
	{
		sysTickCounter--;
	}
}

void delay_ms(uint32_t ms)
{
	sysTickCounter = ms;
	while(sysTickCounter!=0);
}






