#include "Inf_ADS1115.h"

void Inf_ADS1115_Init(void){
    //初始化底层驱动IIC
    Driver_IIC_Init();
    //配置ADS1115的寄存器
    //使用IIC驱动写入 需要设备地址和字节地址 指针寄存器
    //IIC写入数据流程
    Driver_IIC_Start();
    Driver_IIC_SenDADDR(ADS1115_ADDR_W);
    Driver_IIC_SendData(ADS1115_REG_POINTER_CONFIG);
    //写入数据一次一个字节
    uint16_t config=ADS1115_CONFIG_DEFULT;

    //选择通道0
    config&=~ADS1115_REG_CONFIG_MUX_MASK;
    config|=ADS1115_REG_CONFIG_MUX_SINGLE_0;
    //选择4.096V量程
    config&=~ADS1115_REG_CONFIG_PGA_MASK;
    config|=ADS1115_REG_CONFIG_PGA_4_096V;

    //选择连续转换模式
    config&=~ADS1115_REG_CONFIG_MODE_MASK;
    config|=ADS1115_REG_CONFIG_MODE_CONTIN;
    Driver_IIC_SendData((config>>8)&0xFF);
    Driver_IIC_SendData((config>>0)&0xFF);
    Driver_IIC_Stop();
}
int16_t Inf_ADS1115_ReadV(void){
    uint16_t raw=0;
    int16_t adc=0;

    //使用IIC的流程读取电压值
    Driver_IIC_Start();
    //发送设备地址和指针寄存器地址
    Driver_IIC_SenDADDR(ADS1115_ADDR_W);
    Driver_IIC_SendData(ADS1115_REG_POINTER_CONVERT);

    //重复起始，切换为读
    Driver_IIC_Start();
    Driver_IIC_SenDADDR(ADS1115_ADDR_R);

    Driver_IIC_ACK();
    raw|=Driver_IIC_ReceiveData()<<8;
    Driver_IIC_NACK();
    raw|=Driver_IIC_ReceiveData();
    Driver_IIC_Stop();

    adc=(int16_t)raw;
    return (int16_t)((int32_t)adc * 4096 / 32768);
}
