#ifndef BLINKLED_H_
#define BLINKLED_H_

#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"


void LED_Init(GPIO_TypeDef *port, uint8_t pin);
void LED_High(GPIO_TypeDef *port, uint8_t pin);
void Push_Btn_Init(GPIO_TypeDef *port, uint8_t pin);
uint32_t Push_Btn_Status(GPIO_TypeDef *port, uint8_t pin);
void EXTI0_Interrupt_Init(void);
void Interrupt_Initialization(GPIO_TypeDef *port, uint8_t pin);
void LED_Toggle(GPIO_TypeDef *port, uint8_t pin);

extern volatile uint8_t pressed;

#endif // BLINKLED_H_
