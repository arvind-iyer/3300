#include "gpio.h"
void gpio_rcc_init(GPIO_TypeDef* gpio) {
  if(gpio == GPIOA) {
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); 
  } else if(gpio == GPIOB) {
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
  } else if(gpio == GPIOC) {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
  } else if(gpio == GPIOD) {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
  } else if(gpio == GPIOE) {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
  } else if(gpio == GPIOF) {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF, ENABLE);
  } else if(gpio == GPIOG) {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF, ENABLE);
  }
}

// Simplify gpio initialisation code in other routines
// E.g. : gpio_init(GPIOA, GPIO_Pin_10, GPIO_Speed_50MHz, GPIO_Mode_IPU, 0);
void gpio_init(GPIO_TypeDef* gpio,uint16_t gpio_pin, GPIOSpeed_TypeDef speed, GPIOMode_TypeDef mode, u8 rcc_init) {
  if(rcc_init)gpio_rcc_init(gpio);
  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Speed = speed;
  GPIO_InitStructure.GPIO_Mode = mode;
  GPIO_InitStructure.GPIO_Pin = gpio_pin;
  GPIO_Init(gpio, &GPIO_InitStructure);
}
