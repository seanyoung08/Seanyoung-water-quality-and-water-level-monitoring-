#ifndef __APP_WATER_LEVEL_H__
#define __APP_WATER_LEVEL_H__

#include "Inf_water_level.h"
#include "App_Display.h"
#include "Delay.h"
#include "Debug.h"
#include "stdio.h"
#include "Inf_W25Q32.h"
#include "string.h"
#include"stdlib.h"
void App_Water_Level_calibrate(void);
void App_Water_Level_Init(void);

double App_Water_Level_depth(void );

#endif /* __APP_WATER_LEVEL_H__ */
