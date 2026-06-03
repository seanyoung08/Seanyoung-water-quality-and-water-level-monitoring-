#include "Driver_SPI.h"

void Driver_SPI_Init(void){
    //PA5 SCK 复用推挽输出1011
    //PA6 MISO 浮空输入 0100
    //PA7 MOSI 复用推挽输出1011
    //PC13 cs 通用推挽输出0011

    //  配置时钟
    RCC->APB2ENR |=RCC_APB2ENR_IOPAEN;
    RCC->APB2ENR |=RCC_APB2ENR_IOPCEN;
    RCC->APB2ENR |=RCC_APB2ENR_SPI1EN;

    //配置PA5 SCK 复用推挽输出1011
    GPIOA->CRL &=~GPIO_CRL_CNF5_0;
    GPIOA->CRL |=(GPIO_CRL_CNF5_1|GPIO_CRL_MODE5);

    //配置PA6 MISO 浮空输入 0100
    GPIOA->CRL &=~(GPIO_CRL_CNF6_1|GPIO_CRL_MODE6);
    GPIOA->CRL |=GPIO_CRL_CNF6_0;

    //配置PA7 MOSI 复用推挽输出1011
    GPIOA->CRL &=~GPIO_CRL_CNF7_0; 
    GPIOA->CRL |=(GPIO_CRL_CNF7_1|GPIO_CRL_MODE7);

    //配置PC13 cs 通用推挽输出0011
      GPIOC->CRH &= ~(GPIO_CRH_CNF13 | GPIO_CRH_MODE13);
    GPIOC->CRH |= GPIO_CRH_MODE13;
    CS_HIGH;

    //配置SPI1 相位和极性
    SPI1->CR1 &=~(SPI_CR1_CPOL|SPI_CR1_CPHA);

    //配置主从模式
    SPI1->CR1 |=SPI_CR1_MSTR;

    //配置波特率 010
    SPI1->CR1 &=~(SPI_CR1_BR_2|SPI_CR1_BR_0);
    SPI1->CR1 |=SPI_CR1_BR_1;


    //配置数据帧格式
 
    SPI1->CR1 |=(SPI_CR1_SSM|SPI_CR1_SSI);

    //配置设备管理和设备选择
    SPI1->CR1 &=~SPI_CR1_LSBFIRST;
    SPI1->CR1 &=~SPI_CR1_DFF;
        //SPI1 使能
    SPI1->CR1 |=SPI_CR1_SPE;
    
}

void Driver_SPI_Start(void){
    CS_LOW;
}
void Driver_SPI_Stop(void){
    CS_HIGH;
}
uint8_t Driver_SPI_Swapbyte(uint8_t data){
    //先发数据 =>在时序图之前
    //收数据 =>在时序图之后

    while((SPI1->SR & SPI_SR_TXE) == 0)
    ;
    SPI1->DR = data; //发送一个字节的数据
    //等待发送完成
    while((SPI1->SR & SPI_SR_RXNE) == 0)
    ;
    return SPI1->DR&0xFF; //返回接收到的数据
}
