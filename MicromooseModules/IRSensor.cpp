#include "IRSensor.h"

IRSensor::IRSensor(GPIO* emitter, GPIO* receiver, ADConverter* adconvert, int channel) {
	this->m_emitter = emitter;
	this->m_receiver = receiver;
	this->m_adc = adconvert;
	this->m_channel = channel;
}

void delay_us(unsigned int time_del) {
	// delay is about 1 microsecond * time_del
    volatile int t;
    
    while (time_del--) {
        for (t=1; t>0; t--);
    }
}

volatile int IRSensor::readVal() {
	int val = this->m_adc->readIn(this->m_channel);
	this->m_emitter->writeOut(1);
	delay_us(60);
	val = this->m_adc->readIn(this->m_channel) - val;
    this->m_emitter->writeOut(0);
    if (val < 0) val = 0;
    return val;
}