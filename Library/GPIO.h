#ifndef GPIO_H
#define GPIO_H

#include "../Startup/stm32f4xx.h"


enum PinMode {
        DigitalOut,
        DigitalIn,
        AnalogIn,
        AlternateFunction
};

class GPIO {
public:
    GPIO(GPIO_TypeDef* port, int num, PinMode mode);
    //~GPIO();
    int changeMode(PinMode newMode);
    int writeOut(int state);
    int readIn();

    

private:
    GPIO_TypeDef*   m_port;
    int             m_pinNum;
    PinMode         m_mode;
    int             m_setMask   = (1<<m_pinNum);
};

#endif /*GPIO_H*/
