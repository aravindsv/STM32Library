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
    // GPIO pwmPin(GPIOA, 5, AlternateFunction);
    // Timer outputTimer(TIM2, 1000);
    // outputTimer.setPeriod(1000);
    // outputTimer.initPWM(1, &pwmPin);

    // GPIO inputPin(GPIOA, 7, AlternateFunction);
    // Timer inputTimer(TIM3, 1000);
    // inputTimer.setPeriod(100);
    // inputTimer.initInputCapture(2, &inputPin, Rising);

    GPIO smallLed(GPIOA, 5, AlternateFunction);
    Timer smallTimer(TIM2, 20000);
    // smallTimer.setPeriod(1000);
    smallTimer.initPWM(1, &smallLed);

    GPIO ledPin(GPIOA, 7, AlternateFunction);
    Timer ledTimer(TIM3, 20000);
    ledTimer.setPeriod(100);
    ledTimer.initInputCapture(2, &ledPin, Rising);

    GPIO triggerPin(GPIOA, 0, DigitalOut);
    GPIO btnPin(GPIOC, 13, DigitalIn);
    while(1) {
        // for (TIM3->CCR2 = 0; TIM3->CCR2 < 100; TIM3->CCR2++){
        smallTimer.setDutyCycle(1, TIM3->CCR2);
            // delay_ms(3);
        // }
        triggerPin.writeOut(btnPin.readIn());

        
        // for (int i = 100; i > 0; i--) {
        //     outputTimer.setDutyCycle(1, i);
        //     delay_ms(3);
        // }
        // for (int i = 0; i < 100; i++) {
        //     outputTimer.setDutyCycle(1, i);
        //     delay_ms(1);
        // }
        
    }
}








//Commented out old  test code /*
    // GPIOA->AFR[0] |= ((0b0010) << 28);
    // GPIO btn(GPIOC, 13, DigitalIn);
    //PA5 is supposedly connected to TIM2_CH1
    //For testing PWM, PA7 is connected to TIM3_CH2

    // RCC->APB1ENR |= (1UL << 1); //Enable TIM3 Clock
    // TIM3->PSC = 0; //Set prescaler
    // TIM3->ARR = 1000; //Set Auto-Reload Value
    // TIM3->CR1 = 0b0000000010000000;
    // TIM3->EGR |= 1;
    // TIM3->CCMR1 = 0b0110100000000000;
    // TIM3->CCER = 0b0000000000010000;



    //Check GPIO Alternate Function Register...

    // TIM3->CCMR1 |= TIM_CCMR1_OC2PE | TIM_CCMR1_OC2M_1 | TIM_CCMR1_OC2M_2; //Set Counter Mode
    // TIM3->CR1 |= TIM_CR1_ARPE;
    // TIM3->CCER |= TIM_CCER_CC2E;
    // TIM3->BDTR |= TIM_BDTR_MOE;// | TIM_BDTR_OSSR;


    // TIM3->CR1 |= TIM_CR1_CEN;
    // TIM3->CCR2 = 500;


        // for (int i = 0; i < 1000; i++) {
        //     TIM3->CCR2 = i;
        //     delay_ms(1);
        // }
        // for (int i = 1000; i > 0; i--) {
        //     TIM3->CCR2 = i;
        //     delay_ms(1);
        // }
        // for (int i = 0; i < 30000; i++) {
        //     if (TIM3->CNT < 250) ledPin.writeOut(1);
        //     else ledPin.writeOut(0);
        // }
        // for (int i = 0; i < 30000; i++) {
        //     if (TIM3->CNT < 500) ledPin.writeOut(1);
        //     else ledPin.writeOut(0);
        // }
        // for (int i = 0; i < 30000; i++) {
        //     if (TIM3->CNT < 750) ledPin.writeOut(1);
        //     else ledPin.writeOut(0);
        // }
        // for (int i = 0; i < 30000; i++) {
        //     if (TIM3->CNT < 500) ledPin.writeOut(1);
        //     else ledPin.writeOut(0);
        // }
        // if (TIM3->CNT > TIM3->CCR2) ledPin.writeOut(1);
        // else ledPin.writeOut(0);
        // count++;
        // if (count > 20000) {
        //     TIM3->CCR2 = (TIM3->CCR2 + 250) % 1250;
        //     count = 0;
        // }