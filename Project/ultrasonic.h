
#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_
#include <stm32f10x_gpio.h>
#include <stm32f10x_tim.h>
#include <stm32f10x_rcc.h>
#include <stm32f10x_exti.h>
#include <misc.h>
#include "stm32f10x_it.h"
#include "lcd.h"


#define TRIG_PIN GPIO_Pin_6
#define TRIG_PORT GPIOA
#define ECHO_PORT GPIOA
#define ECHO_PIN GPIO_Pin_7

#define ULTRASONIC_TIM				  TIM3
#define ULTRASONIC_RCC			          RCC_APB1Periph_TIM3
#define ULTRASONIC_IRQn				  TIM3_IRQn
#define ULTRASONIC_IRQHandler			  void TIM3_IRQHandler(void)


typedef enum {
	US_NULL					= 0,
	US_READY				= 1,
	US_TRIGGER 				= 2,
	US_WAITING_FOR_ECHO		        = 3,
	US_ECHO_RAISED				= 4,
	US_ECHO_FALLEN				= 5
	
} US_STATE;

void us_init();
int get_dist();
void us_enable();
void us_disable();
static US_STATE state;
#endif