#include <gpio.h>

void (* EXTI_fptr)(void) = NULL;

void EXTI_Registering_function(void (* callback)(void))
{
	EXTI_fptr = callback;
}

void LED_Init(GPIO_TypeDef *port, uint8_t pin)
{
	port->MODER   |= (1<<(2*pin));			//01 - Output -> 2y:2y+1
	port->MODER	  &= ~(1<<((2*pin)+1));

	port->OSPEEDR |= (1<<((2*pin)+1));		//10 - High Speed -> 2y:2y+1
	port->OSPEEDR &= ~(1<<(2*pin));

	port->PUPDR   |= (1<<((2*pin)+1));		//10 - Pull-down  -> 2y:2y+1
	port->PUPDR   &= ~(1<<(2*pin));
}

void LED_High(GPIO_TypeDef *port, uint8_t pin)
{
	port->ODR	|= (1<<pin);				// LED ON
}

void LED_Low(GPIO_TypeDef *port, uint8_t pin)
{
	port->ODR	&= ~(1<<pin);				// LED ON
}

void LED_Toggle(GPIO_TypeDef *port, uint8_t pin)
{
	port->ODR	^= (1<<pin);				// LED Toggle
}


void EXTI0_Interrupt_Config(void)
{
	SYSCFG->EXTICR[0] &= ~(1<<0);			// External Interrupt Config
	SYSCFG->EXTICR[0] &= ~(1<<1);			// For pin A0
	SYSCFG->EXTICR[0] &= ~(1<<2);
	SYSCFG->EXTICR[0] &= ~(1<<3);

	EXTI->IMR 	|= (1<<0);					// Disable interrupt mask on EXTI line0
	EXTI->FTSR	|= (1<<0);					// Enable falling edge interrupt detection
	EXTI->RTSR	&= ~(1<<0);

	NVIC->IP[6]	   = (1<<4);				// set priority to 1
	NVIC->ISER[0] |= (1<<6);				// enable interrupt
}

void EXTI_Interrupt_Initialization(GPIO_TypeDef *port, uint8_t pin)
{
	port->MODER	  &= ~(1<<((2*pin)+1));		//00 - Input -> 2y:2y+1
	port->MODER	  &= ~(1<<(2*pin));

	port->PUPDR   &= ~(1<<((2*pin)+1));		//01 - Pull-up  -> 2y:2y+1
	port->PUPDR   &= ~(1<<(2*pin));

	port->OSPEEDR   = (1<<((2*pin)+1));		//10 - High Speed -> 2y:2y+1
	port->OSPEEDR  &= ~(1<<(2*pin));
}

void EXTI0_IRQHandler(void)
{
	EXTI_fptr();
	EXTI->PR    |= (1<<0);
}

void Push_Btn_Init(GPIO_TypeDef *port, uint8_t pin)
{
	//pull up 		-> 10 -> IDR - 0
	//pull down 	-> 01 -> IDR - 1
	port->PUPDR   |= (1<<((2*pin)+1));		//pull up
	port->PUPDR   &= ~(1<<(2*pin));
}

uint32_t Push_Btn_Status(GPIO_TypeDef *port, uint8_t pin)
{
	uint32_t ret_val = 0;
	ret_val = ((port->IDR >> pin) & 0x1);
	return ret_val;
}

uint32_t Output_Pin_Status(GPIO_TypeDef *port, uint8_t pin)
{
	uint32_t ret_val = 0;
	ret_val = ((port->ODR >> pin) & 0x1);
	return ret_val;
}






