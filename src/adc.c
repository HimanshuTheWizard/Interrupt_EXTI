#include <adc.h>

void (*adc_callback_fptr)(uint32_t) = NULL;

void ADC_Callback_Registering(void (*callback)(uint32_t))
{
	adc_callback_fptr = callback;
}

void ADC_Pin_Init(GPIO_TypeDef *port, uint8_t pin)
{
	// Set with no pull-push configuration
	port->MODER   |= (1<<(2*pin));			//11 - Analog -> 2y:2y+1
	port->MODER	  |= (1<<((2*pin)+1));
}

void ADC_Configuration(void)
{
	//00: 12-bit resolution (15 ADCCLK cycles)
	//26 - overrun interrupt enable 5- EOC interrupt enable
	ADC1->CR1 |= (1<<5);//(1<<26)

	//Data alignment - right(default)
	//0 - Enable_ADC 1 - CONT 10-EOC selection
	//timer-1 is selected as timer event by default
	ADC1->CR2 |= (1<<0)|(1<<1)|(1<<10);

	//channel 10 - 480 cycles sampling rate
	ADC1->SMPR1 |= (1<<0)|(1<<1)|(1<<2);

}

void ADC_Interrupt_Configuration(void)
{
	NVIC->IP[18]	 = (1<<4);				// set priority to 1
	NVIC->ISER[0] 	|= (1<<18);				// enable interrupt
}

void ADC_Start_Conversion(void)
{
	//SWSTART bit is set to start conversion
	ADC1->CR2 |= (1<<30);
}

void ADC_IRQHandler(void)
{
	//data_g = (ADC1->DR & 0x0000FFFF);
	uint16_t data_l;
	data_l = (ADC1->DR & 0x0000FFFF);
	adc_callback_fptr(data_l);
	//EOC bit gets cleared on reading DR register
}



