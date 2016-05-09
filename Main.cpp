#include "Library/Library.h"
#include <stdio.h>

#define DELAY_C 50

/* Interrupt Test Code */


// void EXTI4_IRQHandler(void)
// {
//     EXTI->PR |= (1 << 13);            // ack int
//     // ISR code
//     // led.writeOut(0);
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
// int main() {
//     GPIO led(GPIOB, 12, DigitalOut);
//     // GPIO oPin(GPIOB, 3, DigitalOut);
//     while(1) {
//         led.writeOut(1);
//         // oPin.writeOut(1);
//         delay_ms(500);
//         led.writeOut(0);
//         // oPin.writeOut(0);
//         delay_ms(1000);
//     }
// }

int main() {
    GPIO lmotorA(GPIOB, 6, AlternateFunction);
    Timer motors(TIM4, 20000);
    motors.initPWM(1, &lmotorA);

    GPIO lmotorB(GPIOB, 7, AlternateFunction);
    motors.initPWM(2, &lmotorB);

    GPIO rmotorA(GPIOB, 8, AlternateFunction);
    motors.initPWM(3, &rmotorA);

    GPIO rmotorB(GPIOB, 9, AlternateFunction);
    motors.initPWM(4, &rmotorB);

    GPIO led(GPIOC, 11, DigitalOut);
    led.writeOut(1);
    delay_ms(500);
    led.writeOut(0);
    delay_ms(500);
    led.writeOut(1);
    delay_ms(500);
    led.writeOut(0);
    delay_ms(500);
    // GPIO oPin(GPIOB, 3, DigitalOut);
    while(1) {
        for (int i = 0; i < 100; i++) {
            motors.setDutyCycle(1, i);
            motors.setDutyCycle(4, i);
            motors.setDutyCycle(2, 0);
            motors.setDutyCycle(3, 0);
            delay_ms(10);
        }
        delay_ms(1000);
        for (int i = 100; i > 0; i--) {
            motors.setDutyCycle(1, i);
            motors.setDutyCycle(4, i);
            motors.setDutyCycle(2, 0);
            motors.setDutyCycle(3, 0);
            delay_ms(10);
        }
        delay_ms(1000);
    }
}


/*Micromoose Code*/
// class Motor {
// public:
//     Motor(GPIO* gA, GPIO* gB, Timer* tA, Timer* tB, int channel1, int channel2) {
//         this->gA = gA;
//         this->gB = gB;
//         this->tA = tA;
//         this->tB = tB;
//         this->cA = channel1;
//         this->cB = channel2;
//     }
//     // Motor(GPIO_TypeDef* port1, int num1, GPIO_TypeDef* port2, int num2, TIM_TypeDef* timer1, int channel1, TIM_TypeDef* timer2, int channel2) {
//     //     this->gA = GPIO gA(port1, num1, AlternateFunction);
//     //     this->gB = GPIO gB(port2, num2, AlternateFunction);
//     //     this->tA = Timer tA(timer1, 16000);
//     //     this->tB = Timer tB(timer2, 16000);
//     //     this->cA = channel1;
//     //     this->cB = channel2;
//     // }
//     void setSpeed(int speed) {
//         if (speed > 0) {
//             this->tA->setDutyCycle(this->cA, speed);
//             this->tB->setDutyCycle(this->cB, 0);
//         }
//         else if (speed < 0) {
//             speed = -speed;
//             this->tA->setDutyCycle(this->cA, 0);
//             this->tB->setDutyCycle(this->cB, speed);
//         }
//         else {
//             this->tA->setDutyCycle(this->cA, 0);
//             this->tB->setDutyCycle(this->cB, 0);
//         }
//     }

// private:
//     GPIO* gA;
//     GPIO* gB;
//     Timer* tA;
//     Timer* tB;
//     int cA;
//     int cB;
// };

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