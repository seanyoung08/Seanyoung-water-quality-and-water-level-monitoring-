#ifndef __DRIVER_LCD_H__
#define __DRIVER_LCD_H__

#include "Driver_LCD_FSMC.h"
#include "Delay.h"
//推荐使用的FSMC拓展存储器方法
//使用宏定义指针指向
/* 常见颜色 */
#define WHITE 0xFFFF
#define BLACK 0x0000
#define BLUE 0x001F
#define BRED 0XF81F
#define GRED 0XFFE0
#define GBLUE 0X07FF
#define RED 0xF800
#define MAGENTA 0xF81F
#define GREEN 0x07E0
#define CYAN 0x7FFF
#define YELLOW 0xFFE0
#define BROWN 0XBC40 // 棕色
#define BRRED 0XFC07 // 棕红色
#define GRAY 0X8430 // 灰色

#define LCD_BASE 0x6c000000
#define LCD_CMD ((uint16_t *)(LCD_BASE))
#define LCD_DATA (( uint16_t *)(LCD_BASE+(1<<11)))
void Driver_LCD_Init(void);

uint32_t Inf_LCD_ReadID(void);
void Inf_LCD_CleanAll(uint16_t color);
void Inf_LCD_FillRect(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t color);
void Inf_LCD_TestPattern(void);

void Inf_LCD_DrawPoint(uint16_t x,uint16_t y,uint16_t w,uint16_t color);

void Inf_LCD_SetArea(uint16_t x,uint16_t y,uint16_t w,uint16_t h);
void Inf_LCD_DrawLine(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2,uint16_t w,uint16_t color);

void Inf_LCD_DrawCircle(uint16_t xCenter,uint16_t ycenter,uint16_t r,uint16_t w,uint16_t color);

void Inf_LCD_DrawcircleFile(uint16_t xCenter,uint16_t ycenter,uint16_t r,uint16_t w,uint16_t color);

void Inf_LCD_WriteASCLLChar(uint16_t x,uint16_t y, uint16_t ch,uint16_t h,uint16_t fcolor,uint16_t bcolor);

void Inf_LCD_WriteASCLLString(uint16_t x,uint16_t y, char* str,uint16_t h,uint16_t fcolor,uint16_t bcolor);
void Inf_LCD_WriteChinese(uint16_t x,uint16_t y,uint16_t index,uint16_t fcolor,uint16_t bcolor);

void Inf_LCD_POTOT(uint16_t x,uint16_t y);
void Inf_LCD_Logo(uint16_t x,uint16_t y) ;
void Inf_LCD_Chinese(uint16_t x,uint16_t y,uint16_t index,uint16_t fcolor,uint16_t bcolor);

void Inf_LCD_FillColor(uint32_t NUMS,uint16_t color);
#endif
