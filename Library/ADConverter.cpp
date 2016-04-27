#include "ADConverter.h"

ADConverter::ADConverter(ADC_TypeDef* ADCx) {

	this->m_adc = ADCx;

	//Enable Peripheral Clock
	int clkMask = ADCx == ADC1 ? RCC_APB2ENR_ADC1EN :
				  ADCx == ADC2 ? RCC_APB2ENR_ADC2EN :
				/*ADCx == ADC3*/ RCC_APB2ENR_ADC3EN;
	RCC->APB2ENR |= clkMask;

	//Turn on ADC
	ADCx->CR2 |= ADC_CR2_ADON;
}

int ADConverter::readIn(int channel) {
	//Set channel to read
	this->m_adc->SQR3 = channel;
	//Start conversion at selected channel
	this->m_adc->CR2 |= ADC_CR2_SWSTART;
	//Wait until conversion is ready
	while ((this->m_adc->SR & 2) == 0);
	//Read Data value
	int res = this->m_adc->DR;
}