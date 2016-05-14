#ifndef MOTOR_H
#define MOTOR_H

#include "../Startup/stm32f4xx.h"
#include "GPIO.h"
#include "Timer.h"

class Motor {
public:
    Motor(GPIO* gA, GPIO* gB, Timer* tA, Timer* tB, int channel1, int channel2); 
    
    void setSpeed(int speed);

private:
    GPIO* gA;
    GPIO* gB;
    Timer* tA;
    Timer* tB;
    int cA;
    int cB;
};


#endif /*MOTOR_H*/