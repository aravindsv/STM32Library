#ifndef IRSENSOR_H
#define IRSENSOR_H

#include "../Startup/stm32f4xx.h"
#include "GPIO.h"
#include "ADConverter.h"

class IRSensor {
public:
	IRSensor(GPIO* emitter, GPIO* receiver, ADConverter* adconvert, int channel);
	volatile int readVal();

private:
	GPIO* m_emitter;
	GPIO* m_receiver;
	ADConverter *m_adc;
	int m_channel;
};


#endif /*IRSENSOR_H*/