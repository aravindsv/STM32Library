#ifndef ADCONVERTER_H
#define ADCONVERTER_H

#include "../Startup/stm32f4xx.h"


// class ADConverter {
// public:
//     ADConverter(ADC_TypeDef* ADCx);
//     int readIn(int channel);

//     ADC_TypeDef* m_adc;
// };

template<unsigned int T>
class ADConverter
{
public:
    static void initADC()
    {
        ADC_TypeDef *adc = reinterpret_cast<ADC_TypeDef*>(T);
        //Enable Peripheral Clock
        int clkMask = adc == ADC1 ? RCC_APB2ENR_ADC1EN :
                      adc == ADC2 ? RCC_APB2ENR_ADC2EN :
                    /*adc == ADC3*/ RCC_APB2ENR_ADC3EN;
        RCC->APB2ENR |= clkMask;

        //Turn on ADC
        adc->CR2 |= ADC_CR2_ADON;
    }
    
    static int readIn(unsigned int channel)
    {
        ADC_TypeDef *adc = reinterpret_cast<ADC_TypeDef*>(T);
        adc->SQR3 = channel;
        adc->CR2 |= ADC_CR2_SWSTART;
        while((adc->SR & 2) == 0);
        return adc->DR;
    }
};


#endif /*ADCONVERTER_H*/
