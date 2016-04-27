#ifndef LIBRARY_H
#define LIBRARY_H

#include "../Startup/stm32f4xx.h"
#include "GPIO.h"
#include "Timer.h"
#include "USART.h"
#include "ADConverter.h"
#include "Interrupt.h"

void delay_ms(unsigned int time_del) {
    // delay is about 1 millisecond * time_del
    volatile int t;
    
    while (time_del--) {
        for (t=1000; t>0; t--);
    }
}

#endif /*LIBRARY_H*/