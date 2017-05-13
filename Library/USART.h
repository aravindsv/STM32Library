#ifndef USART_H
#define USART_H

#include "../Startup/stm32f4xx.h"
#include "GPIO.h"

// class USART {
// public:
// 	USART(USART_TypeDef *usart, int baudrate);
// 	void setPins(GPIO *txPin, GPIO *rxPin);
// 	void sendChar(char c);
// 	void sendString(char *s);

// private:
// 	USART_TypeDef* m_usart;
// };

template<unsigned int U>
class USART
{
public:

    // static void setBaudrate(unsigned int baudrate) //Currently not necessary because only 9600 baud is supported
    // {

    // }
    static void initUsart()
    {
        USART_TypeDef* usart = reinterpret_cast<USART_TypeDef*>(U);
        if (usart == USART2 || usart == USART3 || usart == UART4 || usart == UART5) 
        {
            RCC->APB1ENR |= usart == USART2 ? RCC_APB1ENR_USART2EN :
                            usart == USART3 ? RCC_APB1ENR_USART3EN :
                            usart == UART4  ? RCC_APB1ENR_UART4EN  :
                          /*usart == UART5*/  RCC_APB1ENR_UART5EN;
        }
        else 
        {
            RCC->APB2ENR |= usart == USART1 ? RCC_APB2ENR_USART1EN :
                          /*usart == USART6*/ RCC_APB2ENR_USART6EN;
        }

        //Enable USART by writing UE bit in CR1
        usart->CR1 |= USART_CR1_UE;

        usart->BRR = 0x683; //9600 Baud
    }

    static void sendChar(char c) 
    {
        USART_TypeDef* usart = reinterpret_cast<USART_TypeDef*>(U);
        while(!(usart->SR >> 6) & 1);
        usart->CR1 |= USART_CR1_TE;
        usart->DR |= c;
        while(!(usart->SR >> 6) & 1);
    }

    static void sendString(char *s)
    {
        USART_TypeDef* usart = reinterpret_cast<USART_TypeDef*>(U);
        while(!(usart->SR >> 6) & 1);
        usart->CR1 |= USART_CR1_TE;
        while(*s)
        {
            sendChar((char)*s);
            s++;
        }
    }

};


#endif /*USART_H*/