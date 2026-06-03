#include "Delay.h"

//延迟多少微秒
void Delay_us(uint16_t us){
	//设置倒计时起始值
	SysTick->LOAD=72*us;
	//补充，手动清空value
	SysTick->VAL=0;
	//配置滴哒寄存器选择系统时钟控制置1、中断置0开始计数置1
	SysTick->CTRL|=SysTick_CTRL_CLKSOURCE;
	SysTick->CTRL&=~SysTick_CTRL_TICKINT;
	SysTick->CTRL|=SysTick_CTRL_ENABLE;

	//循环计数计到0停下，如果COUNTFLAT标志位是0就继续循环直到是1
	while ((SysTick->CTRL&SysTick_CTRL_COUNTFLAG)==0&&SysTick->CTRL&SysTick_CTRL_ENABLE);
	//关闭定时器
	SysTick->CTRL&=~SysTick_CTRL_ENABLE;

}

//延迟多少毫秒
void Delay_ms(uint16_t ms){
	while (ms--){
		Delay_us(1000);
	}
}

//延迟多少秒
void Delay_s(uint16_t s){
	while (s--){
		Delay_ms(1000);
	}
}

