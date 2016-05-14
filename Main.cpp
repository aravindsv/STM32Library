#include "Library/Library.h"
#include <stdio.h>


/* Interrupt Test Code */

// int t = 60;

// void EXTI15_10_IRQHandler(void)
// {
//     //Should do some kind of check for other interrupts. See FuturaProject
//     // ISR code
//     if ((EXTI->PR & (1<<13)) && (EXTI->IMR & (1<<13))) {
//         t = 1000;
//         EXTI->PR = (1 << 13);            // ack int
//     }
// }
// int count = 0;



// int main() {
    
//     GPIO led(GPIOA, 11, DigitalOut);

//     GPIO btn(GPIOC, 13, DigitalIn);

//     RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
//     SYSCFG->EXTICR[3] |= SYSCFG_EXTICR4_EXTI13_PC;
//     EXTI->IMR |= 1 << 13;
//     EXTI->RTSR |= (1 << 13);
//     // EXTI->FTSR |= (1 << 13);

//     uint32_t prioritygroup = NVIC_GetPriorityGrouping();
//     // Highest user int priority (0), 1 sub-pri
//     uint32_t priority = NVIC_EncodePriority(prioritygroup, 0, 1 );    
//     NVIC_SetPriority(EXTI15_10_IRQn, priority);
//     NVIC_EnableIRQ(EXTI15_10_IRQn);
//     while(1){
//         led.writeOut(1);
//         delay_ms(t);
//         led.writeOut(0);
//         delay_ms(t);
//     }
// }

/* Micromouse Test Code */
int main() {
    GPIO led(GPIOA, 7, DigitalOut);
    // GPIO oPin(GPIOB, 3, DigitalOut);
    while(1) {
        led.writeOut(1);
        // oPin.writeOut(1);
        delay_ms(500);
        led.writeOut(0);
        // oPin.writeOut(0);
        delay_ms(500);
    }
}

// #include "MicromooseModules/Motor.h"
// #include "MicromooseModules/IRSensor.h"

// int main() {
//     //Motors
//     //Each motor uses 2 GPIOs in DigitalOutMode, (at least) 1 GPIO in Alternate Function,
//     // and at least 1 Timer. See Motor.cpp for example PWM code
//     GPIO lmotorA(GPIOB, 6, AlternateFunction);
//     Timer motorTim(TIM4, 20000);
//     // motors.initPWM(1, &lmotorA);

//     GPIO lmotorB(GPIOB, 7, AlternateFunction);
//     // motors.initPWM(2, &lmotorB);

//     GPIO rmotorA(GPIOB, 8, AlternateFunction);
//     // motors.initPWM(3, &rmotorA);

//     GPIO rmotorB(GPIOB, 9, AlternateFunction);
//     // motors.initPWM(4, &rmotorB);

//     Motor lmotor(&lmotorA, &lmotorB, &motorTim, &motorTim, 1, 2);
//     Motor rmotor(&rmotorB, &rmotorA, &motorTim, &motorTim, 4, 3);

//     //IR Emitters
//     //Each IR Sensor uses 1 GPIO in DigitalOut mode, 1 GPIO in AnalogIn Mode, and 1 ADC. 
//     GPIO rdemitter(GPIOC, 2, DigitalOut);
//     GPIO rfemitter(GPIOC, 1, DigitalOut);
//     GPIO ldemitter(GPIOA, 7, DigitalOut);
//     GPIO lfemitter(GPIOC, 7, DigitalOut);

//     //IR Receivers
//     GPIO rdreceiver(GPIOA, 4, AnalogIn); //ADC 1/2, In 4
//     GPIO rfreceiver(GPIOA, 5, AnalogIn); //ADC 1/2, In 5
//     GPIO ldreceiver(GPIOB, 0, AnalogIn); //ADC 1/2, In 8
//     GPIO lfreceiver(GPIOB, 1, AnalogIn); //ADC 1/2, In 9
//     ADConverter receiverADC(ADC1);

//     IRSensor lfSensor(&lfemitter, &lfreceiver, &receiverADC, 9);
//     IRSensor ldSensor(&ldemitter, &ldreceiver, &receiverADC, 8);
//     IRSensor rdSensor(&rdemitter, &rdreceiver, &receiverADC, 4);
//     IRSensor rfSensor(&rfemitter, &rfreceiver, &receiverADC, 5);

//     //Encoders
//     //Each encoder uses 2 GPIOs in Alternate Function, each connected on the same Timer
//     //Will currently crash if you try to use any timer other than TIM2 or TIM5, 
//     //but that bug can be fixed in Encoder.cpp
//     GPIO lencgA(GPIOA, 15, AlternateFunction); //TIM2_CH1
//     GPIO lencgB(GPIOB, 3, AlternateFunction); //TIM2_CH2
//     Timer lenc(TIM2, 20000);
//     //lenc.initInputCapture(1, &lencgA, RisingFalling); //if you can't use the built-in encoder modules
//     lenc.initEncoderMode(1, 2, &lencgB, &lencgA);
//     lenc.reverseEncoderPolarity(1, 2);
//     GPIO rencgA(GPIOA, 0, AlternateFunction); //TIM5_CH1
//     GPIO rencgB(GPIOA, 1, AlternateFunction); //TIM5_CH2
//     Timer renc(TIM5, 20000);
//     renc.initEncoderMode(1,2,&rencgA, &rencgB);

//     //Serial
//     //Each serial module requires 2 GPIOs in AlternateFunction mode, and 1 USART.
//     //Currently only works at baud rate of 9600
//     GPIO tx(GPIOA, 9, AlternateFunction);
//     GPIO rx(GPIOA, 10, AlternateFunction);
//     USART serial(USART1, 9600);
//     serial.setPins(&tx, &rx);
//     serial.sendString("Starting Program!\n");


//     //LEDs
//     GPIO led(GPIOC, 11, DigitalOut);



//     //Startup Sequence
//     led.writeOut(1);
//     delay_ms(500);
//     led.writeOut(0);
//     delay_ms(500);
//     led.writeOut(1);
//     delay_ms(500);
//     led.writeOut(0);
//     delay_ms(500);
//     // GPIO oPin(GPIOB, 3, DigitalOut);
//     volatile int lfVal;
//     volatile int ldVal;
//     volatile int rfVal;
//     volatile int rdVal;
//     volatile int lencVal;
//     volatile int rencVal;
//     while(1) {
//         char s[50];
//         /*IR Sensor Test*/
//         // lfVal = lfSensor.readVal();
//         // ldVal = ldSensor.readVal();
//         // rfVal = rfSensor.readVal();
//         // rdVal = rdSensor.readVal();
//         // sprintf(s, "LD: %d\t\tLF: %d\t\tRF: %d\t\tRD:%d\n", ldVal, lfVal, rfVal, rdVal);

//         /*Encoder Test*/
//         lencVal = lenc.readEncoder();
//         rencVal = renc.readEncoder();
//         sprintf(s, "LeftEncoder: %d\tRightEncoder: %d\n", lencVal, rencVal);
//         //Wheels are 3.7 cm diamtere = 11.62 cm circumference
//         //Encoders seem to give 3000 counts per rotation
//         ///3000/11.62 = X/D => 3000*D/11.62 = 258.2*D
//         int target = 4647;
//         int curl = lenc.readEncoder();
//         int curr = renc.readEncoder();
//         while(lenc.readEncoder() - curl < target || renc.readEncoder() - curr < target) {
//             if(lenc.readEncoder() - curl < target) {
//                 lmotor.setSpeed(10);
//                 // lencVal = lenc.readEncoder();
//                 // rencVal = renc.readEncoder();
//                 // sprintf(s, "LeftEncoder: %d\tRightEncoder: %d\n", lencVal, rencVal);
//             }
//             if(renc.readEncoder() - curr < target) {
//                 rmotor.setSpeed(10);
//                 // lencVal = lenc.readEncoder();
//                 // rencVal = renc.readEncoder();
//                 // sprintf(s, "LeftEncoder: %d\tRightEncoder: %d\n", lencVal, rencVal);
//             }
//             lencVal = lenc.readEncoder();
//             rencVal = renc.readEncoder();
//             sprintf(s, "LeftEncoder: %d\tRightEncoder: %d\n", lencVal, rencVal);
//         }
//         // else
//         lmotor.setSpeed(0);
//         rmotor.setSpeed(0);
        
//         serial.sendString(s);
//         delay_ms(1000);
//     }
// }


/*Micromoose Code*/


// int main() {
//     GPIO lIn1(GPIOB, 6, AlternateFunction);
//     GPIO lIn2(GPIOB, 7, AlternateFunction);
//     Timer lTim(TIM4, 16000);
//     Motor lMotor(&lIn1, &lIn2, &lTim, &lTim, 1, 2);
//     while(1) {
//         lMotor.setSpeed(25);
//     }
// }

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