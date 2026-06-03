#ifndef __APP_DISPLAY_H__
#define __APP_DISPLAY_H__

#include  "Driver_LCD.h"
#include "Delay.h"



void App_Display_Init(void);

void App_Display_Back(void );

void App_Display_ASCII(uint16_t x,uint16_t y,char *data);

void App_Display_Clean(void );
#endif /* __APP_DISPLAY_H__ */
