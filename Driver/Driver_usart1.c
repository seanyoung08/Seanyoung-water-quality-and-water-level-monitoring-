#include "Driver_usart1.h"

void Driver_USART1_Init(void)
{
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;

    /* PA9: USART1_TX alternate-function push-pull, PA10: USART1_RX floating input. */
    GPIOA->CRH &= ~(GPIO_CRH_MODE9 | GPIO_CRH_CNF9 | GPIO_CRH_MODE10 | GPIO_CRH_CNF10);
    GPIOA->CRH |= (GPIO_CRH_MODE9 | GPIO_CRH_CNF9_1 | GPIO_CRH_CNF10_0);

    /* PCLK2 = 72 MHz, baudrate = 115200. */
    USART1->BRR = 0x0271;

    /* 8 data bits, no parity, 1 stop bit, TX and RX enabled. */
    USART1->CR1&=~USART_CR1_M;

    //Receive enable
    USART1->CR1 |= USART_CR1_TE;

}

void Driver_USART1_Start(void)
{
    USART1->CR1 |= USART_CR1_UE;
}

void Driver_USART1_Stop(void)
{
    USART1->CR1 &= ~USART_CR1_UE;
}

void Driver_USART1_SendChar(uint8_t ch)
{
    while ((USART1->SR & USART_SR_TXE) == 0)
    {
    }

    USART1->DR = ch;
}

void Driver_USART1_SendString(uint8_t data[], uint16_t len)
{
    uint16_t i;

    for (i = 0; i < len; i++)
    {
        Driver_USART1_SendChar(data[i]);
    }
}

int fputc(int ch, FILE *file)
{
     
    Driver_USART1_SendChar((uint8_t)ch);
    return ch;
}
