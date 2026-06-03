#include "App_Display.h"

void App_Display_Init(void){
    Driver_LCD_Init();
}


void App_Display_Back(void ){
    //让背景板编程
    Inf_LCD_CleanAll(WHITE);
    
    //展示Logo 
    Inf_LCD_Logo((320-240)/2,16);

    //展示字符
    for(uint16_t i=0;i<6;i++){
        Inf_LCD_Chinese(112+16*i,79,i,GREEN,WHITE);
        // Inf_LCD_WriteChinese(0+32*i,79,i,GREEN,WHITE);
    }
}

void App_Display_ASCII(uint16_t x,uint16_t y,char *data){
        Inf_LCD_WriteASCLLString(x,95+y,data,24,RED,WHITE);
}

void App_Display_Clean(void ){
    //选择要清空的区域
    Inf_LCD_SetArea(0,95,320,385);
    //清空区域
    Inf_LCD_FillColor(320*385,WHITE);
}
