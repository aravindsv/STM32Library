#include "Motor.h"

Motor::Motor(GPIO* gA, GPIO* gB, Timer* tA, Timer* tB, int channel1, int channel2) {
    this->gA = gA;
    this->gB = gB;
    this->tA = tA;
    this->tB = tB;
    this->cA = channel1;
    this->cB = channel2;
    tA->initPWM(channel1, gA);
    tB->initPWM(channel2, gB);
}
    
void Motor::setSpeed(int speed) {
    if (speed > 0) {
        this->tA->setDutyCycle(this->cA, speed);
        this->tB->setDutyCycle(this->cB, 0);
    }
    else if (speed < 0) {
        speed = -speed;
        this->tA->setDutyCycle(this->cA, 0);
        this->tB->setDutyCycle(this->cB, speed);
    }
    else {
        this->tA->setDutyCycle(this->cA, 100);
        this->tB->setDutyCycle(this->cB, 100);
    }
}