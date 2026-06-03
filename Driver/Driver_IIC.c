#include "Driver_IIC.h"

void Driver_IIC_Init(void){
    //配置时钟
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN; //使能GPIOB时钟
    RCC->APB1ENR |= RCC_APB1ENR_I2C2EN; //使能I2C2时钟

    //配置GPIO PB10（SCL）和PB11（SDA）为复用开漏输出1111
    GPIOB->CRH &= ~(GPIO_CRH_MODE10 | GPIO_CRH_CNF10 | GPIO_CRH_MODE11 | GPIO_CRH_CNF11);
    GPIOB->CRH |= (GPIO_CRH_MODE10 | GPIO_CRH_CNF10 | GPIO_CRH_MODE11 | GPIO_CRH_CNF11);

    //配置IIC 模式
    I2C2->CR1 &=~ I2C_CR1_SMBUS; //使能SMBus

    //配置IIC时钟频率
    I2C2->CR2 &=~ I2C_CR2_FREQ; //清除频率位
    I2C2->CR2 |= 36; //设置APB1时钟频率为36MHz

    //选择标准模式
    I2C2->CCR &=~ I2C_CCR_FS; //选择标准模式

    //配置IIC时钟频率
    I2C2->CCR &=~ I2C_CCR_CCR; //清除时钟频率位
    I2C2->CCR |= 180; //设置时钟频率为100kHz

    //最大上升时间
    I2C2->TRISE &=~ I2C_TRISE_TRISE; //清除上升时间位
    I2C2->TRISE |= 37; //设置最大上升时间为1000ns

    //IIC2使能
    I2C2->CR1 |= I2C_CR1_PE; //使能IIC2
}

uint8_t Driver_IIC_Start(void ){
    uint32_t timeout=0xffff;
    //置为启动信号
    I2C2->CR1 |=I2C_CR1_START;
    while(!(I2C2->SR1&I2C_SR1_SB)&&timeout){
        timeout--;
    }
    if (timeout>0)
    {
        return 1;
    }else{
        return 0;
    }
    
}
void Driver_IIC_Stop(void){
    I2C2->CR1 |=I2C_CR1_STOP;
}

void Driver_IIC_ACK(void){
    I2C2->CR1|=I2C_CR1_ACK;
}

void Driver_IIC_NACK(void){
    I2C2->CR1&=~I2C_CR1_ACK;
    
}

uint8_t Driver_IIC_SenDADDR(uint8_t addr){
    uint32_t timeout=0xffff;
    volatile uint32_t temp;

    I2C2->DR=addr;
    while(!(I2C2->SR1&I2C_SR1_ADDR)&&timeout){
        timeout--;
    }

    if (timeout>0)
    {
        temp = I2C2->SR1;
        temp = I2C2->SR2;
        (void)temp;
        return 1;
    }

    return 0;
}
uint8_t Driver_IIC_SendData(uint8_t data){
    uint32_t timeout=0xffff;
    //等待TXE为1
    while(!(I2C2->SR1&I2C_SR1_TXE)&&timeout){
        timeout--;
    }
    if (timeout>0)
    {   
        I2C2->DR=data;
        timeout=0xffff;
        while(!(I2C2->SR1&I2C_SR1_TXE)&&timeout){
        timeout--;
        }
        if (timeout>0)
        {
            return 1;
        }  
    }
        return 0;
}

uint8_t Driver_IIC_ReceiveData(void){
    uint32_t timeout=0xffff;
    //等待RXNE为1
    while(!(I2C2->SR1&I2C_SR1_RXNE)&&timeout){
        timeout--;
    }
    if (timeout>0)
    {
        return I2C2->DR;
    }else{
        return 0;
    }
}
