#include"App_TDS.h"



void App_TDS_Init(void){
    Inf_ADS1115_Init();
}

double App_TDS_Read(void){
    double mv=Inf_ADS1115_ReadV();
    double v=mv/1000.0;
    double v2=v*v;

    // TDS公式的输入单位是V，Inf_ADS1115_ReadV返回单位是mV。
    return 66.71 * v2 * v - 127.93 * v2 + 428.7 * v;
}
