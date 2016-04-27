#include "Library/Library.h"
#include <stdio.h>

#define DELAY_C 50

/* Interrupt Test Code */
int main() {
    GPIO btn(GPIOC, 13, DigitalIn);
    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
    SYSCFG->EXTICR[3] |= SYSCFG_EXTICR1_EXTI0_PC;
    EXTI->IMR |= 1 << 13;
}

/* Micromouse Test Code */
/*int main() {
    GPIO led(GPIOA, 5, DigitalOut);
    while(1) {
        led.writeOut(1);
        delay_ms(1000);
        led.writeOut(0);
        delay_ms(500);
    }
}*/


/* Analog In Example Code*/
/*
int main() {}
    GPIO analogIn(GPIOA, 7, AnalogIn);
    ADConverter anIn(ADC1);

    GPIO analog2(GPIOA, 6, AnalogIn);
    ADConverter an2(ADC1);

    // GPIO output(GPIOA, 6, AlternateFunction);
    // Timer pwmTim(TIM3, 20000);
    // pwmTim.initPWM(1, &output);
    // pwmTim.setDutyCycle(1, 50);

    GPIO tx(GPIOA, 2, AlternateFunction);
    GPIO rx(GPIOA, 3, AlternateFunction);

    USART serial(USART2, 9600);
    serial.setPins(&tx, &rx);
    serial.sendString("Starting program!\n");

    while(1) {
        int val2 = an2.readIn(7);
        int val = anIn.readIn(6);
        char s[50];
        sprintf(s, "PA6 = %d\tPA7 = %d\n", val, val2);
        serial.sendString(s);
        delay_ms(500);
    }
}
*/