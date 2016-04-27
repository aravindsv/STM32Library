#ifndef USART_H
#define USART_H

#include "../Startup/stm32f4xx.h"
#include "GPIO.h"

class USART {
public:
	USART(USART_TypeDef *usart, int baudrate);
	void setPins(GPIO *txPin, GPIO *rxPin);
	void sendChar(char c);
	void sendString(char *s);

private:
	USART_TypeDef* m_usart;
};



#endif /*USART_H*/