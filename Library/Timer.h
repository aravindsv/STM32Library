#ifndef TIMER_H
#define TIMER_H

#include "../Startup/stm32f4xx.h"
#include "GPIO.h"

void configureTimerRCC(TIM_TypeDef* timer)
{
	int tim_offset = timer == TIM2  ? 0 :
					 timer == TIM3  ? 1 :
					 timer == TIM4  ? 2 :
					 timer == TIM5  ? 3 :
					 timer == TIM6  ? 4 :
					 timer == TIM7  ? 5 :
					 timer == TIM12 ? 6 :
					 timer == TIM13 ? 7 :
				   /*timer == TIM14 */8 ;
		RCC->APB1ENR |= (1UL << tim_offset);
}


template<unsigned int T>
class Timer
{
public:

	/**
	 * @brief      Sets the frequency. Needed for initialization
	 *
	 * @param[in]  f     { Frequency of timer }
	 */
	static void setFrequency(unsigned int f)
	{
		TIM_TypeDef* timer = reinterpret_cast<TIM_TypeDef*>(T);
		configureTimerRCC(timer);
		timer->ARR = HSI_VALUE/(timer->PSC+1)/f;
		int maxVal = 65535;
		if (timer == TIM2 || timer == TIM5) maxVal = 4294967295;
		timer->PSC = 0;
		while(timer->ARR > maxVal) 
		{
			timer->PSC++;
			timer->ARR = HSI_VALUE/(timer->PSC+1)/f;
		}
		timer->CR1 |= 0x81; //ARPE and EN bits
	}
	/**
	 * @brief      Sets the period. Needed for initialization
	 *
	 * @param[in]  p     { Period of timer }
	 */
	static void setPeriod(unsigned int p)
	{
		TIM_TypeDef* timer = reinterpret_cast<TIM_TypeDef*>(T);
		configureTimerRCC(timer);
		timer->ARR = p;
		timer->CR1 |= 0x81; //ARPE and EN bits
	}

	static void initPWM(unsigned int channel)
	{
		TIM_TypeDef* timer = reinterpret_cast<TIM_TypeDef*>(T);
		int enReg = 4*(channel - 1);
		timer->CCER |= (1UL << enReg); //Enable output channel
		switch(channel) //Set output mode and preload enable for output channels
		{ 
			// 0x0060 sets output mode to PWM1
			// 0x0008 enables preloading 
			case 1:
				timer->CCMR1 |= 0x0068;
				break;
			case 2:
				timer->CCMR1 |= 0x6800;
				break;
			case 3:
				timer->CCMR2 |= 0x0068;
				break;
			case 4:
				timer->CCMR2 |= 0x6800;
				break;
		}
		timer->EGR |= 1;
	}

	static void setDutyCycle(unsigned int channel, unsigned int duty)
	{
		TIM_TypeDef* timer = reinterpret_cast<TIM_TypeDef*>(T);
		if (duty > 100) return;
		uint32_t val = timer->ARR*duty/100;
		switch (channel) 
		{
			case 1: 
				timer->CCR1 = val;
				break;
			case 2:
				timer->CCR2 = val;
				break;
			case 3:
				timer->CCR3 = val;
				break;
			case 4:
				timer->CCR4 = val;
				break;
		}
	}

	

};


#endif /*TIMER_H*/