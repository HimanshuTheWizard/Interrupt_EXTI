#ifndef SPI_H_
#define SPI_H_

#include "stm32f407xx.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * Pin Configuration - Master
 * CS 	-	PE3
 * SCK 	- 	PA5
 * MISO -   PA6
 * MOSI -	PA7
 */

void SPI_GPIO_Init(void);
void SPI_Init();
uint8_t SPI_Data_Read(uint8_t addr);
uint8_t Data_Transmit(uint8_t data);
void acc_init(void);
void acc_write(uint8_t addr,uint8_t data);
void acc_read(void);

#endif // SPI_H_
