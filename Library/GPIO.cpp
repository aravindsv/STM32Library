#include "GPIO.h"

GPIO::GPIO(GPIO_TypeDef* port, int num, PinMode mode){
    this->m_port = port;
    this->m_pinNum = num;
    this->m_mode = mode;
    int port_offset = port == GPIOA ? 0 :
                      port == GPIOB ? 1 :
                      port == GPIOC ? 2 :
                      port == GPIOD ? 3 :
                      port == GPIOE ? 4 :
                      port == GPIOF ? 5 :
                      port == GPIOG ? 6 :
                      port == GPIOH ? 7 :
                      port == GPIOI ? 8 :
                          /*Default*/ 9;

    RCC->AHB1ENR    |= ((1UL << port_offset) ); //Enable Clock for GPIO port
    if (mode==DigitalOut) {
        this->m_port->MODER     &= ~((3UL) << 2*m_pinNum); //Clear pin [num]
        this->m_port->MODER     |=  ((1UL) << 2*m_pinNum); //Set mode of pin [num] as output
        this->m_port->OTYPER    &= ~((1UL) << m_pinNum); //Set Output type of pin [num] to Push-Pull
        this->m_port->OSPEEDR   &= ~((3UL) << 2*m_pinNum); //Clear Output Speed
        this->m_port->OSPEEDR   |=  ((2UL) << 2*m_pinNum); //Set Output speed to High Speed (Can make 3 for Very high speed)
        this->m_port->PUPDR     &= ~((3UL) << 2*m_pinNum); //Set no pull-up, no pull-down
    }
    else if (mode==DigitalIn) {
        this->m_port->MODER     &= ~((3UL) << 2*m_pinNum); //Set pin as digital input
        this->m_port->OTYPER    &= ~((1UL) << 2*m_pinNum); //Set Output type of pin [num] to Push-Pull
        this->m_port->OSPEEDR   &= ~((3UL) << 2*m_pinNum); //Clear Output Speed
        this->m_port->OSPEEDR   |=  ((2UL) << 2*m_pinNum); //Set Output speed to High Speed (Can make 3 for Very high speed)
        this->m_port->PUPDR     &= ~((3UL) << 2*m_pinNum); //Set no pull-up, no pull-down
    }
    else if (mode==AnalogIn) {
        this->m_port->MODER     |=  ((3UL) << 2*m_pinNum); //Set pin as Analog input
        this->m_port->OTYPER    &= ~((1UL) << 2*m_pinNum); //Set Output type of pin [num] to Push-Pull
        this->m_port->OSPEEDR   &= ~((3UL) << 2*m_pinNum); //Clear Output Speed
        this->m_port->OSPEEDR   |=  ((2UL) << 2*m_pinNum); //Set Output speed to High Speed (Can make 3 for Very high speed)
        this->m_port->PUPDR     &= ~((3UL) << 2*m_pinNum); //Clear Pull state
    }
    else {
        this->m_port->MODER     &=  ~((3UL) << 2*m_pinNum); //Clear pin [num]
        this->m_port->MODER     |=  ((2UL) << 2*m_pinNum); //Set mode of pin [num] as alternate function
        this->m_port->OTYPER    &= ~((1UL) << 2*m_pinNum); //Set Output type of pin [num] to Push-Pull
        this->m_port->OSPEEDR   &= ~((3UL) << 2*m_pinNum); //Clear Output Speed
        this->m_port->OSPEEDR   |=  ((2UL) << 2*m_pinNum); //Set Output speed to High Speed (Can make 3 for Very high speed)
        this->m_port->PUPDR     &= ~((3UL) << 2*m_pinNum); //Set no pull-up, no pull-down
    }
}

int GPIO::changeMode(PinMode newMode) {
    if (newMode==DigitalOut) {
        this->m_port->MODER     &= ~((3UL) << 2*m_pinNum); //Clear pin [num]
        this->m_port->MODER     |=  ((1UL) << 2*m_pinNum); //Set mode of pin [num] as output
    }
    else if (newMode==DigitalIn) {
        this->m_port->MODER     &= ~((3UL) << 2*m_pinNum); //Set pin as digital input
    }
    else if (newMode==AnalogIn) {
        this->m_port->MODER     |=  ((3UL) << 2*m_pinNum); //Set pin as Analog input
    }
    else if (newMode==AlternateFunction) {
        this->m_port->MODER     &=  ~((3UL) << 2*m_pinNum); //Clear pin [num]
        this->m_port->MODER     |=  ((2UL) << 2*m_pinNum); //Set mode of pin [num] as alternate function
    }
    else return 0;
    return 1;
}

int GPIO::writeOut(int state) {
    if (state)  this->m_port->BSRRL = m_setMask;
    else        this->m_port->BSRRH = m_setMask;
    return 1;
}

int GPIO::readIn() {
    return (this->m_port->IDR >> m_pinNum) & 1;// & GPIO_IDR_0;
}
