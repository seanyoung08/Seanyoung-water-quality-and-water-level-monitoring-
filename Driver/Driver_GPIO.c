#include "Driver_GPIO.h"

void Driver_GPIO_Init(void){
    //配置压力传感器引脚PB12 sck PB13  OUT

    //1 配置时钟
    RCC->APB2ENR |=RCC_APB2ENR_IOPBEN;

    //配置PB12为通用推挽输出0011；
    GPIOB->CRH &=~GPIO_CRH_CNF12;
    GPIOB->CRH |=GPIO_CRH_MODE12;

    //配置PB13为浮空输入0100
    GPIOB->CRH &=~(GPIO_CRH_MODE13|GPIO_CRH_CNF13_1);
    GPIOB->CRH |=GPIO_CRH_CNF13_0;

    //配置按键引脚
    //配置时钟
    RCC->APB2ENR |=RCC_APB2ENR_IOPFEN;

    //配置PF8为上拉输入：MODE=00, CNF=10
    GPIOF->CRH &=~(GPIO_CRH_MODE8|GPIO_CRH_CNF8_0);
    GPIOF->CRH |=GPIO_CRH_CNF8_1;

    //配置上拉
    GPIOF->ODR|=GPIO_ODR_ODR8;
    
}

uint8_t Driver_GPIO_key1press(void){
    if(GPIOF->IDR & GPIO_IDR_IDR8){
        return 0;
    }

    Delay_ms(100);
    if((GPIOF->IDR & GPIO_IDR_IDR8) == 0){
        while((GPIOF->IDR & GPIO_IDR_IDR8) == 0);
        Delay_ms(100);
        return 1;
    }

    return 0;
}


