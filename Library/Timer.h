#ifndef TIMER_H
#define TIMER_H

#include "../Startup/stm32f4xx.h"
#include "GPIO.h"

enum EdgeMode {
        Rising,
        Falling,
        RisingFalling,
        None
};

class Timer {
public:
	Timer(TIM_TypeDef* timer, int frequency);
	void setFrequency(int frequency);
	void setPeriod(unsigned int period);

	//For PWM Mode
	void initPWM(int channel, GPIO *pin);
	void setDutyCycle(int channel, int dc);
	

	//For Input Capture Mode
	void initInputCapture(int channel, GPIO *pin, EdgeMode emode);
	int inputCaptureVal(int channel);

	//For Encoder Mode
	void initEncoderMode(int channel1, int channel2, GPIO *pin1, GPIO *pin2);
	volatile int readEncoder();
	void reverseEncoderPolarity(int channel1, int channel2);

private:
	TIM_TypeDef* m_timer;
	int m_frequency;
	int m_maxVal;
};


#endif /*TIMER_H*/