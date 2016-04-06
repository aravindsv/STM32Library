#ifndef USART_H
#define USART_H

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
	void setPeriod(int period);

	//For PWM Mode
	void initPWM(int channel, GPIO *pin);
	void setDutyCycle(int channel, int dc);
	

	//For Input Capture Mode
	void initInputCapture(int channel, GPIO *pin, EdgeMode emode);
	int inputCaptureVal(int channel);

private:
	TIM_TypeDef* m_timer;
	int m_frequency;
	int m_maxVal;
};


#endif /*USART_H*/