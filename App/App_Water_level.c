#include "App_Water_level.h"

double k = 0;
double b = 0;
uint8_t kb_buff[128];
uint8_t kb_len=0;

void App_Water_Level_calibrate(void){
    
    //第一次运行 需要先校验
    //后续使用时 需要先注释掉此代码 不需要校验
    // INF_W25Q32_SectorErase(0);
    
    /**
     * @brief 使用flash 中存储的常量值KB 替代掉校验不需要使用校验
     * 读取flash 中KB_len
     * 
     */
    INF_W25Q32_ReadData(0,&kb_len,1);
    if(kb_len>0&&kb_len<255){
        //读取数据保存到Flash 中的值 给kb赋值
        INF_W25Q32_ReadData(1,kb_buff,kb_len);

        //切分字符k#b =》k和b
        //第一次调用 返回#之前的部分
        Debug_println("%s",strtok((char*)kb_buff,"#"));

        //第二次调用 填写NULL 表示使用之前切分剩下的字符串再切分
        Debug_println("%s",strtok(NULL,"#"));

        //将支付串类型的K =>赋值给double 类型的K
        k=strtod(strtok((char*)kb_buff,"#"),NULL);
        b=strtod (strtok(NULL,"#"),NULL);
        Debug_println("k:%0.4f b:%0.4f",k,b);
        return ;
    }
    App_Display_ASCII(0,0,"start calibrate");

    Delay_s(1);

    App_Display_Clean();

    //不放入水中校验一次
    App_Display_ASCII(0,0,"Please don't put the sensor into water,then press the key1");

    while(Driver_GPIO_key1press()==0)
    ;
    
    //检验到不放入水中的电压值
    int32_t v1=Inf_Water_Level_ReadV();


    //放入水中10cm 的位置校验
    //提示用户放入水中
    App_Display_Clean();
    
    App_Display_ASCII(0,0,"Please put the sensor into water with 10cm depth,then press the key1");
    

    while(Driver_GPIO_key1press()==0)
    ;
    
    //检验到放入水中10cm 的位置的电压值
    int32_t v2=Inf_Water_Level_ReadV();
   


    //计算得出 k  和 b 的值
    b=v1;
    k=(v2-v1)/10.0;

    App_Display_Clean();
    
    App_Display_ASCII(0,0,"calibrate success");

    Debug_println("k:%0.4f b:%0.4f",k,b);

    //如果是整数直接使用
    //如果是double 类型则使用字符串 使用# 拼接
    snprintf((char *)kb_buff, sizeof(kb_buff), "%0.2f#%0.2f", k, b);
    kb_buff[sizeof(kb_buff) - 1] = '\0';
    kb_len = strlen((char *)kb_buff);
    //擦除块区
    INF_W25Q32_SectorErase(0);
    Debug_println("before write len");
    INF_W25Q32_PageProgram(0,&kb_len,1);
    Debug_println("after write len");
    Debug_println("before write buff");
    INF_W25Q32_PageProgram(1,kb_buff,kb_len + 1);
    Debug_println("after write buff");
    Debug_println(":%d:%s", kb_len, (char *)kb_buff);
}
void App_Water_Level_Init(void){
    //底层校验初始化
    Inf_Water_Level_Init();

    //底层Flash 初始化
    INF_W25Q32_Init();
    
    //进行压力校验
    App_Water_Level_calibrate();
}

double App_Water_Level_depth(void ){
    //如果想要校验则按下SW1 键 进行校验
     if(Driver_GPIO_key1press()==1){
        INF_W25Q32_SectorErase(0);
        App_Water_Level_calibrate();
    }

    int32_t v=Inf_Water_Level_ReadV();

    return (v-b)/k;
}

