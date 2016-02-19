#ifndef TIMER_H
#define TIMER_H

#include "../Startup/stm32f4xx.h"

class Timer {
public:
	Timer(TIM_TypeDef* timer, int frequency);
	void initPWM(int channel);
	void setDutyCycle(int channel, int dc);

private:
	TIM_TypeDef* m_timer;
	int m_frequency;
};


#endif /*GPIO_H*/