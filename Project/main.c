/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "uart.h"
#include "servo.h"
#include "spider.h"

void LongDelay(u32 nCount)
{
  for(; nCount != 0; nCount--);
}

void Delayms(u32 m)
{
  u32 i;
  
  for(; m != 0; m--)	
       for (i=0; i<50000; i++);
}
GPIO_InitTypeDef GPIO_InitStructure;
TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
TIM_OCInitTypeDef  TIM_OCInitStructure;

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
//up till now in this main function was the given initialization from the labs of elec 3300
  
servo_init();
uart_init(COM3,9600);
//


//
servo_control(12, 90);
Delayms(200);

//servo_control(3, 150);
//Delayms(200);
//
//Delayms(800);
//

//servo_control(2, -30);
//Delayms(200);
//servo_control(1, 90);
//Delayms(200);
//

while(1)
{
  //  u8 rec_data=uart_rx_byte(COM3);
//  servo_control(1,rec_data);
//  uart_tx_byte(COM3,rec_data);

//servo_control(1, 25);
//Delayms(200);
//servo_control(2, 90);
//Delayms(200);
//
//servo_control(1, 120);
//Delayms(200);  
//servo_control(2, -60);
//Delayms(200);

}
 
  


   
}


