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
	timer->EGR |= 0x1;
	timer->ARR = HSI_VALUE/(timer->PSC+1)/frequency;
	int maxVal = 65535;
	if (timer == TIM2 || timer == TIM5) maxVal = 4294967295;
	this->m_maxVal = maxVal;
	while(timer->ARR > maxVal) {
		timer->PSC++;
		timer->ARR = HSI_VALUE/(timer->PSC+1)/frequency;
	}
	this->m_timer->CR1 |= 0x0080; //set ARPE bit (Auto Reload Preload Enable)
	timer->CR1 |= 0x1;
}

void Timer::setFrequency(int frequency) {
	this->m_timer->PSC = 0;
	this->m_timer->ARR = HSI_VALUE/(this->m_timer->PSC+1)/frequency;
	while(this->m_timer->ARR >= this->m_maxVal) {
		this->m_timer->PSC++;
		this->m_timer->ARR = HSI_VALUE/(this->m_timer->PSC+1)/frequency;
	}
}

void Timer::setPeriod(int period) {
	this->m_timer->PSC = 0;
	this->m_timer->ARR = period;
	this->m_frequency = HSI_VALUE/(this->m_timer->PSC+1)/period;
}

void Timer::initInputCapture(int channel, GPIO *pin, EdgeMode eMode) {
	this->m_timer->CCER &= ~ (1UL << 4*(channel-1));
	unsigned char afMode = this->m_timer == TIM1  ? 0b0001 : //set Alternate Function mode for GPIO
						   this->m_timer == TIM2  ? 0b0001 :
						   this->m_timer == TIM3  ? 0b0010 :
						   this->m_timer == TIM4  ? 0b0010 :
						   this->m_timer == TIM5  ? 0b0010 :
						   this->m_timer == TIM9  ? 0b0011 :
						   this->m_timer == TIM10 ? 0b0011 :
					   /*this->m_timer == TIM11 ? */0b0011;
	pin->m_port->AFR[pin->m_pinNum > 7] &= ~((0b1111) << (4*(pin->m_pinNum - 8*(pin->m_pinNum > 7))));	
	pin->m_port->AFR[pin->m_pinNum > 7] |= ((afMode) << (4*(pin->m_pinNum - 8*(pin->m_pinNum > 7)))); //Set alternate function mode for GPIO
	switch(channel) { //Set filter, prescaler, and active input
		case 1:
			this->m_timer->CCMR1 |= 0x0071; //Filter seems to need to be pretty extreme. can set between 7 or 0
			break;
		case 2:
			this->m_timer->CCMR1 |= 0x7100;
			break;
		case 3:
			this->m_timer->CCMR2 |= 0x0071;
			break;
		case 4:
			this->m_timer->CCMR2 |= 0x7100;
			break;
	}
	//Select active edge
	unsigned char edge = eMode == Rising        ? 0b000 :
					     eMode == Falling       ? 0b001 :
					     eMode == RisingFalling ? 0b101 :
					     /*Should never get this*/0;
	unsigned char ccerVal = 1 | (edge << 1);
	this->m_timer->CCER |= (ccerVal << (4*(channel-1)));
}

int Timer::inputCaptureVal(int channel) {
	switch (channel) {
		case 1: return this->m_timer->CCR1;
		case 2: return this->m_timer->CCR2;
		case 3: return this->m_timer->CCR3;
		case 4: return this->m_timer->CCR4;
	}
}

void Timer::initPWM(int channel, GPIO *pin) {
	int enReg = 4*(channel - 1);
	this->m_timer->CCER |= (1UL << enReg); //Enable output channel
	switch(channel) { //Set output mode and preload enable for output channels
		case 1:
			this->m_timer->CCMR1 |= 0x0068;
			break;
		case 2:
			this->m_timer->CCMR1 |= 0x6800;
			break;
		case 3:
			this->m_timer->CCMR2 |= 0x0068;
			break;
		case 4:
			this->m_timer->CCMR2 |= 0x6800;
			break;
	}
	unsigned char afMode = this->m_timer == TIM1  ? 0b0001 : //set Alternate Function mode for GPIO
						   this->m_timer == TIM2  ? 0b0001 :
						   this->m_timer == TIM3  ? 0b0010 :
						   this->m_timer == TIM4  ? 0b0010 :
						   this->m_timer == TIM5  ? 0b0010 :
						   this->m_timer == TIM9  ? 0b0011 :
						   this->m_timer == TIM10 ? 0b0011 :
					   /*this->m_timer == TIM11 ? */0b0011;
	pin->m_port->AFR[pin->m_pinNum > 7] &= ~((0b1111) << (4*(pin->m_pinNum - 8*(pin->m_pinNum > 7))));				   
	pin->m_port->AFR[pin->m_pinNum > 7] |= ((afMode) << (4*(pin->m_pinNum - 8*(pin->m_pinNum > 7))));
	this->m_timer->EGR |= 1;
}

void Timer::setDutyCycle(int channel, int dc) {
	if (dc > 100) return;
	uint32_t val = this->m_timer->ARR*dc/100;
	switch (channel) {
		case 1: 
			this->m_timer->CCR1 = val;
			break;
		case 2:
			this->m_timer->CCR2 = val;
			break;
		case 3:
			this->m_timer->CCR3 = val;
			break;
		case 4:
			this->m_timer->CCR4 = val;
			break;
	}
}