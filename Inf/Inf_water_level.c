#include "inf_water_level.h"

void Inf_Water_Level_Init(void){
    Driver_GPIO_Init();
}

int32_t Inf_Water_Level_ReadV(void){
    uint32_t value=0;
    //初始化时钟线显示高电平
    SCK_LOW;
    INF_WATER_LEVEL_DLEAY;
    
    while(OUT_READ)
    ;

    for(uint8_t i=0;i<24;i++){
        SCK_HIGH;
        INF_WATER_LEVEL_DLEAY;
        //下降沿
        SCK_LOW;
        value<<=1;
        if(OUT_READ){
            value|=0x01;
            

        }
        INF_WATER_LEVEL_DLEAY;

    }
    //消耗第25次
    SCK_HIGH;
    INF_WATER_LEVEL_DLEAY;
    SCK_LOW;
    INF_WATER_LEVEL_DLEAY;


    if(value & 0x800000){
        value |= 0xFF000000;
    }

    return (int32_t)value ^0x800000;   
}
