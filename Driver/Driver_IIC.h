#ifndef __DRIVER_IIC_H__
#define __DRIVER_IIC_H__

#include "stm32f10x.h"

void Driver_IIC_Init(void);
uint8_t Driver_IIC_Start(void );
void Driver_IIC_Stop(void);
uint8_t Driver_IIC_SenDADDR(uint8_t addr);
uint8_t Driver_IIC_SendData(uint8_t data);
void Driver_IIC_ACK(void);

void Driver_IIC_NACK(void);

uint8_t Driver_IIC_ReceiveData(void);

#endif /* __DRIVER_IIC_H__ */
