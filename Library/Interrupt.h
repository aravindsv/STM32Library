#ifndef INTERRUPT_H
#define INTERRUPT_H

#include "../Startup/stm32f4xx.h"

#define RISING 0
#define FALLING 1
#define CHANGE 2

template<unsigned int P, unsigned int L>
class ExternalInterrupt
{
public:
    static void initInterrupt(int Edge)
    {
        //   //Interrupt
  // //   In order to use an I/O pin as an external interrupt source, follow
  // // *          steps below:
  // // *            1- Configure the I/O in input mode using GPIO_Init()
  // // *            2- Select the input source pin for the EXTI line using SYSCFG_EXTILineConfig()
  // // *            3- Select the mode(interrupt, event) and configure the trigger 
  // // *               selection (Rising, falling or both) using EXTI_Init()
  // // *            4- Configure NVIC IRQ channel mapped to the EXTI line using NVIC_Init()
  // // *   
  // // *  @note  SYSCFG APB clock must be enabled to get write access to SYSCFG_EXTICRx
  // // *         registers using RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
        //1. Configure a Gpio object as Input. Enable RCC Clock.
        Gpio<P, L>::mode(GPIO_INPUT);
        RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
        

        //2. Select the input source and enable it as an interrupt in SYSCFG->EXTICR
        int Port =   P == GPIOA_BASE  ? 0b0000 :
                     P == GPIOB_BASE  ? 0b0001 :
                     P == GPIOC_BASE  ? 0b0010 :
                     P == GPIOD_BASE  ? 0b0011 :
                     P == GPIOE_BASE  ? 0b0100 :
                     P == GPIOF_BASE  ? 0b0101 :
                   /*P == GPIOG_BASE*/  0b0110;
        SYSCFG->EXTICR[L >> 0x02] &= ~(((uint32_t)0x0F) << (0x04 * (L & (uint8_t)0x03)));
        SYSCFG->EXTICR[L >> 0x02] |= (((uint32_t)Port) << (0x04 * (L & (uint8_t)0x03)));

        //3. Set the mode to interrupt and configure the trigger
        EXTI->IMR |= (1<<L);
        if (Edge != RISING) //Falling or Both edges
        {
            EXTI->FTSR |= (1<<L);
        }
        if (Edge != FALLING) //Rising or Both edges
        {
            EXTI->RTSR |= (1<<L);
        }

        //4. Configure NVIC
        IRQn_Type irqn =   L == 0  ? EXTI0_IRQn :
                     L == 1  ? EXTI1_IRQn :
                     L == 2  ? EXTI2_IRQn :
                     L == 3  ? EXTI3_IRQn :
                     L == 4  ? EXTI4_IRQn :
                     (L >= 5 && L <= 9) ? EXTI9_5_IRQn :
                     /*EXTI lines 10-15*/ EXTI15_10_IRQn;
        NVIC_SetPriority(irqn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 0, 1));
        NVIC_EnableIRQ(irqn);
    }
};
 //External Interrupt Handler Functions
// extern "C" void EXTI0_Handler(void)
// {
//     if (EXTI->PR & (1<<0))
//     {
//         EXTI->PR |= (1<<0);
//         /* Add ISR code here, or name desired function to be run */
//     }
// }

// extern "C" void EXTI`_Handler(void)
// {
//     if (EXTI->PR & (1<<1))
//     {
//         EXTI->PR |= (1<<1);
//         /* Add ISR code here, or name desired function to be run */
//     }
// }

// extern "C" void EXTI2_Handler(void)
// {
//     if (EXTI->PR & (1<<2))
//     {
//         EXTI->PR |= (1<<2);
//         /* Add ISR code here, or name desired function to be run */
//     }
// }

// extern "C" void EXTI3_Handler(void)
// {
//     if (EXTI->PR & (1<<3))
//     {
//         EXTI->PR |= (1<<3);
//         /* Add ISR code here, or name desired function to be run */
//     }
// }

// extern "C" void EXTI4_Handler(void)
// {
//     if (EXTI->PR & (1<<4))
//     {
//         EXTI->PR |= (1<<4);
//         /* Add ISR code here, or name desired function to be run */
//     }
// }

// extern "C" void EXTI9_5_Handler(void)
// {
//     if (EXTI->PR & (1<<5))
//     {
//         EXTI->PR |= (1<<5);
//         /* Add ISR code here, or name desired function to be run */
//     }
//     else if (EXTI->PR & (1<<6))
//     {
//         EXTI->PR |= (1<<6);
//         /* Add ISR code here, or name desired function to be run */
//     }
//     else if (EXTI->PR & (1<<7))
//     {
//         EXTI->PR |= (1<<7);
//         /* Add ISR code here, or name desired function to be run */
//     }
//     else if (EXTI->PR & (1<<8))
//     {
//         EXTI->PR |= (1<<8);
//         /* Add ISR code here, or name desired function to be run */
//     }
//     else if (EXTI->PR & (1<<9))
//     {
//         EXTI->PR |= (1<<9);
//         /* Add ISR code here, or name desired function to be run */
//     }
// }

// extern "C" void EXTI15_10_Handler(void)
// {
//     if (EXTI->PR & (1<<10))
//     {
//         EXTI->PR |= (1<<10);
//         /* Add ISR code here, or name desired function to be run */
//     }
//     else if (EXTI->PR & (1<<11))
//     {
//         EXTI->PR |= (1<<11);
//         /* Add ISR code here, or name desired function to be run */
//     }
//     else if (EXTI->PR & (1<<12))
//     {
//         EXTI->PR |= (1<<12);
//         /* Add ISR code here, or name desired function to be run */
//     }
//     else if (EXTI->PR & (1<<13))
//     {
//         EXTI->PR |= (1<<13);
//         /* Add ISR code here, or name desired function to be run */
//     }
//     else if (EXTI->PR & (1<<14))
//     {
//         EXTI->PR |= (1<<14);
//         /* Add ISR code here, or name desired function to be run */
//     }
//     else if (EXTI->PR & (1<<15))
//     {
//         EXTI->PR |= (1<<15);
//         /* Add ISR code here, or name desired function to be run */
//     }
// }

template <uint32_t F>
class SystickInterrupt
{
public:
    static void initSysTick()
    {
        // SystemInit();
        // SystemCoreClockUpdate();
        if (SysTick_Config(16000000/F)) //Use 8000000 if SystemInit and SystemCoreClockHandler are commented out//This 8500000 number is kinda arbitrary, but it seems to let the SysTick run at F Hz. At some point, need to go back and figure out what the actual systemclock value is
            while(1); //Problem initializing SysTick, hopefully this problem can be debugged in gdb
        
    }
};

#endif /*INTERRUPT_H*/