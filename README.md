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