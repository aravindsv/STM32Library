#ifndef GPIO_H
#define GPIO_H

#include "../Startup/stm32f4xx.h"


enum PinMode {
        DigitalOut,
        DigitalIn,
        AnalogIn,
        AlternateFunction,
        PWM
};

class GPIO {
public:
    GPIO(GPIO_TypeDef* port, int num, PinMode mode);
    //~GPIO();
    int changeMode(PinMode newMode);
    int writeOut(int state);
    int readIn();

    GPIO_TypeDef*   m_port;
    int             m_pinNum;
    PinMode         m_mode;
    

private:
    int             m_setMask   = (1<<m_pinNum);
};

#endif /*GPIO_H*/
