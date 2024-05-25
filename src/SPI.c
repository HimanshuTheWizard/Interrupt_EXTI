#include "spi.h"
uint16_t SPI_Data;

/*
 CS        - PE3
 SCK       - PA5
 MOSI      - PA7
 MISO      - PA6
*/

#define WHO_AM_I			(0x0F)
#define Ctrl_Reg1 			(0x30)
#define Ctrl_Reg2			(0x21)
#define Ctrl_Reg3			(0x22)
#define HP_Filter_Reset		(0x23)
#define Status_Reg			(0x27)
#define Out_X				(0x29)
#define Out_Y				(0x2B)
#define Out_Z				(0x2D)

uint16_t xx;
uint16_t yy;
uint16_t zz;

void SPI_Init(void)
{
	//Master configuration
	SPI1->CR1 |= (1<<2);

	//Enable slave select - SSI and SSM
	SPI1->CR1 |= (1<<8)|(1<<9);

	//baud rate = f(pclk)/2
	SPI1->CR1 &= ~(1<<3);
	SPI1->CR1 &= ~(1<<4);
	SPI1->CR1 &= ~(1<<5);

	//SPI peripheral enabled
	SPI1->CR1 |= (1<<6);
}

/*
 * addr - address of the register in slave that has to be read
 */
uint16_t SPI_Data_Read(uint8_t addr)
{
	uint16_t ret_data;

	//reset the PE3(CS) bit to enable connect with slave
	GPIOE->BSRR |= GPIO_BSRR_BR3;

	//Enable write operation by setting MSB to 1
	addr |= 0x80;

	//send the address
	Data_Transmit(addr);

	//send the dummy value to read from slave
	ret_data = Data_Transmit(0);

	//set the PE3(CS) bit to disable connect with slave
	GPIOE->BSRR |= GPIO_BSRR_BS3;

	return ret_data;
}

uint16_t Data_Transmit(uint8_t data)
{
	uint16_t received_data;

	//wait for transmit buffer to get empty
	while(!(SPI1->SR & 0x2));

	//copy the data to data register
	SPI1->DR = data;

	//wait until receive buffer is empty
	while(!(SPI1->SR & 0x1));

	//read the data register
	received_data = SPI1->DR;

	return received_data;
}

void SPI_GPIO_Init()
{
	//Set PA5 to alternate function
	GPIOA->MODER &= ~(1<<10);
	GPIOA->MODER |= (1<<11);

	//Set PA6 to alternate function
	GPIOA->MODER &= ~(1<<12);
	GPIOA->MODER |= (1<<13);

	//Set PA7 to alternate function
	GPIOA->MODER &= ~(1<<14);
	GPIOA->MODER |= (1<<15);

	//Selecting AF5 for PA5
	GPIOA->AFR[0] |= (1<<20)|(1<<22);

	//Selecting AF5 for PA6
	GPIOA->AFR[0] |= (1<<24)|(1<<26);

	//Selecting AF5 for PA7
	GPIOA->AFR[0] |= (1<<28)|(1<<30);

	//Enable clock for port E
	RCC->AHB1ENR |= (1<<4);

	//Configure CS pin in output mode
	GPIOE->MODER |= (1<<6);

	GPIOA->OSPEEDR |= (1<<10)|(1<<12)|(1<<14);

	//configuring pull down for AF pins
	GPIOA->PUPDR |= (1<<10)|(1<<12)|(1<<14);

	// Enable clock for GPIOD and Configure PD12 in output mode
	//RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
	//GPIOD->MODER |= (GPIO_MODER_MODER12_0 | GPIO_MODER_MODER13_0 | GPIO_MODER_MODER14_0 | GPIO_MODER_MODER15_0);
}

void acc_init(void)
{
	acc_write(Ctrl_Reg1, 0x47);
}

void acc_write(uint8_t addr,uint8_t data)
{
	//reset the PE3(CS) bit to enable connect with slave
	GPIOE->BSRR |= GPIO_BSRR_BR3;

	// Send the Register Address
	Data_Transmit(addr);

	// Send the data to be written
	Data_Transmit(data);

	//set the PE3(CS) bit to disable connect with slave
	GPIOE->BSRR |= GPIO_BSRR_BS3;
}

void acc_read(void)
{
	// Reading the data for x-axis
	xx = SPI_Data_Read(Out_X);

	// Reading the data for y-axis
	yy = SPI_Data_Read(Out_Y);

	// Reading the data for z-axis
	zz = SPI_Data_Read(Out_Z);
}








