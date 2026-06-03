#include "Inf_W25Q32.h"

void INF_W25Q32_Init(void){
    Driver_SPI_Init();
}
void INF_W25Q32_ReadID(uint8_t *id, uint16_t *mid){
    //写一个SPI完整指令
    Driver_SPI_Start();
    Driver_SPI_Swapbyte(0x9F);
    *id = Driver_SPI_Swapbyte(0xFF);
    *mid =0;
    *mid |= Driver_SPI_Swapbyte(0xFF)<<8;
    *mid |= Driver_SPI_Swapbyte(0xFF)<<0;
    Driver_SPI_Stop();

}

void INF_W25Q32_WaitBusy(void ){
    // 状态寄存器第0位为忙状态位，1表示正在执行指令，0表示空闲
    //开始片选
    Driver_SPI_Start();

    //发送写指令
    Driver_SPI_Swapbyte(0x05);
    //循环读取状态寄存器，直到忙状态位为0
    while ((Driver_SPI_Swapbyte(0xFF) & 0x01))
    ;
    //关闭片选
    Driver_SPI_Stop();
}

void INF_W25Q32_WriteEnable(void){
    //1.开始片选
    Driver_SPI_Start();
    //2.发送写使能指令
    Driver_SPI_Swapbyte(0x06);
    //3.结束片选
    Driver_SPI_Stop();
}
//关闭写使能
void INF_W25Q32_WriteDisable(void){
    //1.开始片选
    Driver_SPI_Start();
    //2.发送写使能指令
    Driver_SPI_Swapbyte(0x04);
    //3.结束片选
    Driver_SPI_Stop();
}

void INF_W25Q32_PageProgram(uint32_t addr, uint8_t data[], uint16_t len){
    //1. 等待忙状态
    INF_W25Q32_WaitBusy();
    //2.开始写使能
    INF_W25Q32_WriteEnable();
    //3.开始片选
    Driver_SPI_Start();
    //4.发送写命令
    Driver_SPI_Swapbyte(0x02);

    //5.发送地址
    Driver_SPI_Swapbyte((addr>>16) & 0xFF);
    Driver_SPI_Swapbyte((addr>>8) & 0xFF);
    Driver_SPI_Swapbyte((addr>>0) & 0xFF);
    //6.发送数据
    for (uint16_t i = 0; i < len; i++)
    {
        Driver_SPI_Swapbyte(data[i]);
    }
    //7.结束片选
    Driver_SPI_Stop();
    //8.结束写使能
    INF_W25Q32_WriteDisable();


}

void INF_W25Q32_SectorErase(uint32_t addr){
    //1. 等待忙状态
    INF_W25Q32_WaitBusy();
    //2.开始写使能
    INF_W25Q32_WriteEnable();
    //3.开始片选
    Driver_SPI_Start();
    //4.发送扇区擦除命令
    Driver_SPI_Swapbyte(0x20);
    //5.发送地址
    Driver_SPI_Swapbyte((addr>>16) & 0xFF);
    Driver_SPI_Swapbyte((addr>>8) & 0xFF);
    Driver_SPI_Swapbyte((addr>>0) & 0xFF);
    
    //6.结束片选
    Driver_SPI_Stop();
    //7.结束写使能
    INF_W25Q32_WriteDisable();
}

void INF_W25Q32_ReadData(uint32_t addr, uint8_t data[], uint16_t len){
    //1. 等待忙状态
    INF_W25Q32_WaitBusy();
    //2.开始片选
    Driver_SPI_Start();
    //3.发送读命令
    Driver_SPI_Swapbyte(0x03);
    //4.发送地址
    Driver_SPI_Swapbyte((addr>>16) & 0xFF);
    Driver_SPI_Swapbyte((addr>>8) & 0xFF);
    Driver_SPI_Swapbyte((addr>>0) & 0xFF);
    
    //5.读取数据
    for (uint16_t i = 0; i < len; i++)
    {
        data[i] = Driver_SPI_Swapbyte(0xFF);
    }
    
    //6.结束片选
    Driver_SPI_Stop();
}

