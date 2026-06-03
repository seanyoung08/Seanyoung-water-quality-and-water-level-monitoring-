#ifndef __DRIVER_GPIO_H__
#define __DRIVER_GPIO_H__


#include "stm32f10x.h"
#include "Delay.h"

#define SCK_HIGH (GPIOB->ODR|=GPIO_ODR_ODR12)
#define SCK_LOW (GPIOB->ODR&=~GPIO_ODR_ODR12)
#define OUT_READ (GPIOB->IDR&GPIO_IDR_IDR13)
#define INF_WATER_LEVEL_DLEAY Delay_us(10)

void Driver_GPIO_Init(void);

uint8_t Driver_GPIO_key1press(void);
#endif /* __DRIVER_GPIO_H__ */
