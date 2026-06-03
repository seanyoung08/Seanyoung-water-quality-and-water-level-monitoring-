#include "Debug.h"

void Debug_init(void)
{
    Driver_USART1_Init();
    Driver_USART1_Start();
}

