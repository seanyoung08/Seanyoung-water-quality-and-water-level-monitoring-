#ifndef __INF_W25Q32_H__
#define __INF_W25Q32_H__
#include "Driver_SPI.h"

void INF_W25Q32_Init(void);
void INF_W25Q32_ReadID(uint8_t *id, uint16_t *mid);

void INF_W25Q32_PageProgram(uint32_t addr, uint8_t data[], uint16_t len);

void INF_W25Q32_SectorErase(uint32_t addr);

void INF_W25Q32_ReadData(uint32_t addr, uint8_t data[], uint16_t len);

#endif /* __INF_W25Q32_H__ */
