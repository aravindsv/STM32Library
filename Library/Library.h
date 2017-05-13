#ifndef LIBRARY_H
#define LIBRARY_H

#include "../Startup/stm32f4xx.h"
#include "GPIO.h"
#include "Timer.h"
#include "USART.h"
#include "ADConverter.h"
#include "Interrupt.h"

void delay_ms_hard(unsigned int time_del) {
    // delay is about 1 millisecond * time_del
    volatile int t;
    
    while (time_del--) {
        for (t=1000; t>0; t--);
    }
}

void delay_us_hard(unsigned int time_del)
{
    volatile int t;
    while(time_del--)
    {
        for (t = 1; t > 0; t--);
    }
}

void Systick_User(void);

volatile uint32_t milliseconds = 0;

extern "C" void SysTick_Handler(void)
{
    milliseconds++;
    Systick_User();
    // val = !val;
    // led::set(val);
    // serial::sendChar('A');
}

inline uint32_t millis(void)
{
    return milliseconds;
}

void delay_ms(uint32_t t)
{
    uint32_t start, end;
    start = millis();
    end = start+t;
    if (start < end) 
    {
        while((millis() >= start) && (millis() < end));
    }
    else 
    {
        while((millis() >= start) || (millis() < end));
    }
}

#endif /*LIBRARY_H*/