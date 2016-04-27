#ifndef ADCONVERTER_H
#define ADCONVERTER_H

#include "../Startup/stm32f4xx.h"


class ADConverter {
public:
    ADConverter(ADC_TypeDef* ADCx);
    int readIn(int channel);

    ADC_TypeDef* m_adc;
};

#endif /*ADCONVERTER_H*/
