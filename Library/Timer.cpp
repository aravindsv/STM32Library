#include "Timer.h"

Timer::Timer(TIM_TypeDef* timer, int frequency) {
	this->m_timer = timer;
	this->m_frequency = frequency;
	int tim_offset = timer == TIM2  ? 0 :
					 timer == TIM3  ? 1 :
					 timer == TIM4  ? 2 :
					 timer == TIM5  ? 3 :
					 timer == TIM6  ? 4 :
					 timer == TIM7  ? 5 :
					 timer == TIM12 ? 6 :
					 timer == TIM13 ? 7 :
				   /*timer == TIM14 */8;
	RCC->APB1ENR |= (1UL << tim_offset);
	timer->CR1 |= 0x0001;
	timer->ARR = HSI_VALUE/timer->PSC/frequency;
	while(timer->ARR > 65536) {
		timer->PSC++;
		timer->ARR = HSI_VALUE/timer->PSC/frequency;
	}
}

void Timer::initPWM(int channel) {
	int enReg = 4*(channel - 1);
	this->m_timer->CCER |= (1UL << enReg);
	switch(channel) {
		case 1:
			this->m_timer->CCMR1 |= 0x0064;
			break;
		case 2:
			this->m_timer->CCMR1 |= 0x6400;
			break;
		case 3:
			this->m_timer->CCMR2 |= 0x0064;
			break;
		case 4:
			this->m_timer->CCMR2 |= 0x6400;
			break;
	}
}

void Timer::setDutyCycle(int channel, int dc) {
	uint32_t ccr = channel == 1 ? this->m_timer->CCR1 :
				   channel == 2 ? this->m_timer->CCR2 :
				   channel == 3 ? this->m_timer->CCR3 :
				 /*channel == 4*/ this->m_timer->CCR4;
	uint32_t val = this->m_timer->ARR*dc/100;
	ccr = val;
}