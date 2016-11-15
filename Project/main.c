/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "uart.h"
#include "servo.h"
#include "spider.h"

void LongDelay(u32 nCount)
{
  for(; nCount != 0; nCount--);
}


GPIO_InitTypeDef GPIO_InitStructure;
TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
TIM_OCInitTypeDef  TIM_OCInitStructure;

void go_front() {
   Delayms(150);
 servo_control(7, 90);
 Delayms(60);
 servo_control(9, 0);
 Delayms(60);
 servo_control(7, 230);
   
 servo_control(10, 200);
 Delayms(60);
 servo_control(12, 150);
 Delayms(60);
 servo_control(10, 50);
 Delayms(60);

 
  servo_control(1, 120);
 Delayms(60);
 servo_control(3, 150);
 Delayms(60);
 servo_control(1, 60);
   
 servo_control(4, -100);
 Delayms(60);
 servo_control(6, 110);
 Delayms(60);
 servo_control(4, 0);
 Delayms(60);
 
 //Pull back
 servo_control(6,160);
 servo_control(3,100);
 
 servo_control(12,90);
 servo_control(9,100);
}

int main(void)
{  
  /* Setup the microcontroller system. Initialize the Embedded Flash Interface,  
     initialize the PLL and update the SystemFrequency variable. */
  SystemInit();
  
  /* Configure all unused GPIO port pins in Analog Input mode (floating input
     trigger OFF), this will reduce the power consumption and increase the device
     immunity against EMI/EMC *************************************************/
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB |
                         RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD |
                         RCC_APB2Periph_GPIOE |RCC_APB2Periph_GPIOF | 
                         RCC_APB2Periph_GPIOG, ENABLE);  

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  GPIO_Init(GPIOC, &GPIO_InitStructure);
  GPIO_Init(GPIOD, &GPIO_InitStructure);
  GPIO_Init(GPIOE, &GPIO_InitStructure);
  GPIO_Init(GPIOF, &GPIO_InitStructure);
  GPIO_Init(GPIOG, &GPIO_InitStructure);  

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB |
                         RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD |
                         RCC_APB2Periph_GPIOE | RCC_APB2Periph_GPIOF | 
                         RCC_APB2Periph_GPIOG, DISABLE);  
  
  servo_init();
//  uart_init(COM3,9600);
  spider_init();
 
 

  while(1)
  {
     go_front();
//   Delayms(20);
//    move_robot_backward();
//    Delayms(20);
  }     
}


