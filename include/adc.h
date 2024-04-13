#ifndef ADC_H_
#define ADC_H_

#include "stm32f407xx.h"
#include <stdio.h>
#include <stdlib.h>

void ADC_Callback_Registering(void (*callback)(uint32_t));
void ADC_Pin_Init(GPIO_TypeDef *port, uint8_t pin);
void ADC1_Configuration(void);
void ADC1_Interrupt_Configuration(void);
void ADC1_Start_Conversion(void);

extern void delay_ms(uint32_t ms);

#endif // ADC_H_
