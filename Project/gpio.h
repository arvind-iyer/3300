#ifndef GPIO_H_
#define GPIO_H_

#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
void gpio_rcc_init(GPIO_TypeDef* gpio);
void gpio_init(GPIO_TypeDef* gpio,uint16_t gpio_pin, GPIOSpeed_TypeDef speed, GPIOMode_TypeDef mode, u8 rcc_init);
#endif
