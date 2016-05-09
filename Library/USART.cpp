#include "USART.h"

USART::USART(USART_TypeDef *usart, int baudrate) {
	this->m_usart = usart;

	//Enable APB Clock
	if (usart == USART2 || usart == USART3 || usart == UART4 || usart == UART5) {
		RCC->APB1ENR |= usart == USART2 ? RCC_APB1ENR_USART2EN :
				        usart == USART3 ? RCC_APB1ENR_USART3EN :
				        usart == UART4  ? RCC_APB1ENR_UART4EN  :
				      /*usart == UART5*/  RCC_APB1ENR_UART5EN;
	}
	else {
		RCC->APB2ENR |= usart == USART1 ? RCC_APB2ENR_USART1EN :
		              /*usart == USART6*/ RCC_APB2ENR_USART6EN;
	}

	//Enable USART by writing UE bit in CR1
	usart->CR1 |= USART_CR1_UE;
	//Program M bit in CR1 to define word length
	//Can leave as 0 for 8 bit words
	//Program number of stop bits in CR2
	//Can leave as 0 for 1 stop bit
	//Select baud rate in BRR. If 9600, BRR should have 104.17
	if (baudrate == 9600) {
		usart->BRR = 0x683;
	}
	else {
		return;
	}
}

void USART::setPins(GPIO* txPin, GPIO* rxPin) {
	unsigned char afMode = this->m_usart == USART1 ? 0b0111 : //set Alternate Function mode for GPIO
						   this->m_usart == USART2 ? 0b0111 :
						   this->m_usart == USART3 ? 0b0111 :
						   this->m_usart == UART4 ? 0b1000 :
						   this->m_usart == UART5 ? 0b0111 :
					  /*this->m_usart == USART6  ?*/ 0b1000;
	txPin->m_port->AFR[txPin->m_pinNum > 7] &= ~((0b1111) << (4*(txPin->m_pinNum - 8*(txPin->m_pinNum > 7))));	
	txPin->m_port->AFR[txPin->m_pinNum > 7] |= ((afMode) << (4*(txPin->m_pinNum - 8*(txPin->m_pinNum > 7)))); //Set alternate function mode for GPIO
	rxPin->m_port->AFR[rxPin->m_pinNum > 7] &= ~((0b1111) << (4*(rxPin->m_pinNum - 8*(rxPin->m_pinNum > 7))));	
	rxPin->m_port->AFR[rxPin->m_pinNum > 7] |= ((afMode) << (4*(rxPin->m_pinNum - 8*(rxPin->m_pinNum > 7)))); //Set alternate function mode for GPIO
}

void USART::sendChar(char c) {
	while(!(this->m_usart->SR >> 6) & 1);
	this->m_usart->CR1 |= USART_CR1_TE;
	this->m_usart->DR |= c;
	while(!(this->m_usart->SR >> 6) & 1);
} 

void USART::sendString(char *s) {
	while(!(this->m_usart->SR >> 6) & 1);
	this->m_usart->CR1 |= USART_CR1_TE;
	while(*s) {
		this->sendChar((char)*s);
		s++;
	}
}