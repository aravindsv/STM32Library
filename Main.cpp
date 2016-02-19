#include "Startup/stm32f4xx.h"
#include "Library/GPIO.h"
#include "Library/Timer.h"

void delay_ms(unsigned int time_del) {
    // delay is about 1 millisecond * time_del
    volatile int t;
    
    while (time_del--) {
        for (t=1000; t>0; t--);
    }
}

int main() {
    GPIO ledPin(GPIOA, 5, DigitalOut);


    while(1) {
        ledPin.writeOut(1);
        delay_ms(500);
        ledPin.writeOut(0);
        delay_ms(500);
    }
}