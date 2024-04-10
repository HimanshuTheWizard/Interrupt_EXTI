#ifndef ADC_H_
#define ADC_H_

#include "stm32f407xx.h"
#include <stdio.h>
#include <stdlib.h>

extern volatile uint32_t data;

void ADC_Callback_Registering(void (*callback)(uint32_t));
void ADC_Pin_Init(GPIO_TypeDef *port, uint8_t pin);
void ADC_Configuration(void);
void ADC_Interrupt_Configuration(void);
void ADC_Start_Conversion(void);

#endif // ADC_H_
