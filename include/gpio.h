#ifndef BLINKLED_H_
#define BLINKLED_H_

#include "stm32f407xx.h"
#include <stdio.h>
#include <stdlib.h>

extern volatile uint16_t H;
extern volatile uint16_t L;
extern volatile uint8_t pressed;

void LED_Init(GPIO_TypeDef *port, uint8_t pin);
void LED_High(GPIO_TypeDef *port, uint8_t pin);
void LED_Low(GPIO_TypeDef *port, uint8_t pin);
void Push_Btn_Init(GPIO_TypeDef *port, uint8_t pin);
uint32_t Push_Btn_Status(GPIO_TypeDef *port, uint8_t pin);
void EXTI0_Interrupt_Config(void);
void EXTI_Interrupt_Initialization(GPIO_TypeDef *port, uint8_t pin);
void LED_Toggle(GPIO_TypeDef *port, uint8_t pin);
void EXTI_Registering_function(void (* callback)(void));
uint32_t Output_Pin_Status(GPIO_TypeDef *port, uint8_t pin);

#endif // BLINKLED_H_
