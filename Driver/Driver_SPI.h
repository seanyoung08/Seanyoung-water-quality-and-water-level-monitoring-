#ifndef __DRIVER_SPI_C
#define __DRIVER_SPI_C

#include "stm32f10x.h"

#define CS_HIGH (GPIOC->ODR |= GPIO_ODR_ODR13)
#define CS_LOW (GPIOC->ODR &= ~GPIO_ODR_ODR13)
void Driver_SPI_Init(void);
void Driver_SPI_Start(void);
void Driver_SPI_Stop(void);
uint8_t Driver_SPI_Swapbyte(uint8_t data);


#endif /* __DRIVER_SPI_C */
