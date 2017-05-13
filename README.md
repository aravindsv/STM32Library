# STM32F4XX Library
#### Very much a work in progress

## Setting up the Project

This library can be cloned directly into the top directory of your project (the `git submodule` works well for this).
Create another directory at the same level as the library called `bin`

The following lines must be added to the top of your Makefile:
```
# Change TOPDIR to directory that contains STM32Library submodule
TOPDIR=.

# Change OUTPUT to whatever final bin, hex, and elf files should be called
OUTPUT=main

MODULEDIR=$(TOPDIR)/STM32Library
include $(MODULEDIR)/Makefile_defines
include $(MODULEDIR)/Makefile_std_rules
```

## Usage and Syntax
This version of the library uses a template metaprogramming paradigm to have separate classes for each peripheral
instantiated by the compiler. 
The advantage to this is zero RAM usage for objects (since no objects are ever actually instantiated).
For more info on how this works, refer to http://www.webalice.it/fede.tft/stm32/stm32_gpio_and_template_metaprogramming.html

Following are examples of each peripheral type and how to use them.

### GPIO
```
// To create a GPIO 'object'
typedef Gpio<GPIOA, 0> led; //Template parameters are the GPIO port, and the number on that port

// To set the GPIO object's mode
led::mode(GPIO_OUTPUT); //Full list of possible mode constants are in Library/GPIO.h

// To set GPIO high or low
led::set(1);
led::set(0);

```

### Timers
#### PWM
```
// Create a timer 'object', set the frequency, and initialize it as PWM:
typedef Timer<TIM2_BASE> pwmTimer;
pwmTimer::setFrequency(20000);
pwmTimer::initPWM(1);  //1 is the timer channel

// A GPIO configured to ALTERNATE mode is also required
typedef Gpio<GPIOA_BASE, 7> pwmLed;
pwmLed::mode(GPIO_ALTERNATE | GPIO_AF_TIM2);

//Set Duty cycle with setDutyCycle()
pwmTimer::setDutyCycle(1, 50);

```

### Analog-Digital Converter
```
// First initialize GPIO to INPUT_ANALOG mode
typedef Gpio<GPIOA_BASE, 6> analogIn;
analogIn::mode(GPIO_INPUT_ANALOG);

//Then create ADConverter 'object' and initialize
typedef ADConverter<ADC1_BASE> adc;
adc::initADC();

//To read value, use readIn()
analogValue = adc::readIn(5); //5 is the ADC channel

```

### USART
```
//First initialize two GPIOs
typedef Gpio<GPIOA_BASE, 2> tx;
typedef Gpio<GPIOA_BASE, 3> rx;

// Set both GPIOs to AF_USARTX
tx::mode(GPIO_ALTERNATE | GPIO_AF_USART2);
rx::mode(GPIO_ALTERNATE | GPIO_AF_USART2);

//Create a USART object and initialize it
typedef USART<USART2_BASE> serial;
serial::initUsart();

//Send a string with sendString()
serial::sendString("I have the high ground now\r\n");
```

### Interrupts
#### External Interrupts
```
// First create an ExternalInterrupt 'object' and initialize with desired edge choice. All three edge choices are shown below
typedef ExternalInterrupt<GPIOC_BASE, 13> extInt;
extInt::initInterrupt(RISING);
extInt::initInterrupt(FALLING);
extInt::initInterrupt(CHANGE);

// A function is required for the interrupt, and these functions have particular names. References/examples can be found under the class definition in Interrupt.h
```

#### SysTick
```
//First create the systick 'object' and initialize with the desired frequency in Hz
typedef SystickInterrupt<1000> systick;
systick::initSysTick();

//A function with the following prototype is needed for the SysTick Handler:
extern "C" void SysTick_Handler(void);
```