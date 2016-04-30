#include "Library/Library.h"
#include <stdio.h>

#define DELAY_C 50

/* Interrupt Test Code */


// void EXTI4_IRQHandler(void)
// {
//     EXTI->PR |= (1 << 13);            // ack int
//     // ISR code
//     led.writeOut(0);
//     // flag = !flag;
// }
// int count = 0;



// int main() {
    
//     GPIO tx(GPIOA, 2, AlternateFunction);
//     GPIO rx(GPIOA, 3, AlternateFunction);

//     GPIO led(GPIOB, 6, DigitalOut);
    

//     USART serial(USART2, 9600);
//     serial.setPins(&tx, &rx);
//     serial.sendString("Starting program!\n");


//     GPIO btn(GPIOC, 13, DigitalIn);

//     // RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
//     // SYSCFG->EXTICR[3] |= SYSCFG_EXTICR1_EXTI0_PC;
//     // EXTI->IMR |= 1 << 13;
//     // EXTI->RTSR |= (1 << 13);
//     // // EXTI->FTSR |= (1 << 13);

//     // uint32_t prioritygroup = NVIC_GetPriorityGrouping();
//     // // Highest user int priority (0), 1 sub-pri
//     // uint32_t priority = NVIC_EncodePriority(prioritygroup, 0, 1 );    
//     // NVIC_SetPriority(EXTI4_IRQn, priority);
//     // NVIC_EnableIRQ(EXTI4_IRQn);
//     while(1){
//         char s[50];
//         sprintf(s, "%d\n", count);
//         serial.sendString(s);
//         // led.writeOut(flag);
//         delay_ms(1000);
//         led.writeOut(!led.readIn());
//         count++;
//     }
// }

/* Micromouse Test Code */
int main() {
    GPIO led(GPIOA, 15, DigitalOut);
    GPIO oPin(GPIOA, 3, DigitalOut);
    while(1) {
        led.writeOut(1);
        oPin.writeOut(1);
        delay_ms(500);
        led.writeOut(0);
        oPin.writeOut(0);
        delay_ms(500);
    }
}


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