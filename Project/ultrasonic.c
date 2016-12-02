#include "stm32f10x_gpio.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_rcc.h"
#include "misc.h"
#include "stm32f10x_exti.h"
#include "ultrasonic.h"
#include "gpio.h"
int idle;
u32 pulse_width_tmp, pulse_width, idle_width;
volatile u16 trigger_time_us, falling_time_us;
int dist;
int rx_complete;
#define	US_IDLE_RESET_COUNT		60000
#define US_MAX_WIDTH			1000	

  NVIC_InitTypeDef NVIC_InitStructure;
void us_init()
{
  gpio_init(TRIG_PORT, TRIG_PIN, GPIO_Speed_50MHz, GPIO_Mode_Out_PP, 1);
  gpio_init(ECHO_PORT, ECHO_PIN, GPIO_Speed_50MHz, GPIO_Mode_IN_FLOATING, 1);
  pulse_width = 0;
  pulse_width_tmp = 0;
  idle_width = 0;
  idle = 0;
  state = US_NULL;
  //Set trigger to low
  GPIO_ResetBits(TRIG_PORT, TRIG_PIN);
  
  //initialise interrupt 
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure; 
  RCC_APB1PeriphClockCmd(ULTRASONIC_RCC , ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
  
  TIM_TimeBaseStructure.TIM_Period = 1;	           // 60000 us
  TIM_TimeBaseStructure.TIM_Prescaler = 71;     // 72M/1M - 1 = 71
  TIM_TimeBaseInit(ULTRASONIC_TIM, &TIM_TimeBaseStructure);      // this part feeds the parameter we set above

  TIM_ClearITPendingBit(ULTRASONIC_TIM, TIM_IT_Update);	// Clear Interrupt bits
  TIM_ITConfig(ULTRASONIC_TIM, TIM_IT_Update, ENABLE); 
  TIM_ITConfig(ULTRASONIC_TIM, TIM_IT_CC1, ENABLE);													 // Clear Interrupt bits
  TIM_Cmd(ULTRASONIC_TIM, ENABLE);																							 // Counter Enable
  TIM_SetCounter(ULTRASONIC_TIM, 0);
  
  TIM_ARRPreloadConfig(ULTRASONIC_TIM, 0);
  
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_InitStructure.NVIC_IRQChannel = ULTRASONIC_IRQn;
  NVIC_Init(&NVIC_InitStructure);

}
void us_enable() {
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}
void us_disable() {
    NVIC_InitStructure.NVIC_IRQChannelCmd = DISABLE;
  NVIC_Init(&NVIC_InitStructure);
}
int get_dist() {
  return dist;
}

void ultrasonic_it_handler()
{
  if (TIM_GetITStatus(ULTRASONIC_TIM, TIM_IT_Update) != RESET) {  
    TIM_ClearITPendingBit(ULTRASONIC_TIM, TIM_IT_Update);	 
    switch(state) {
    case US_NULL:
      state = US_READY;
      break;
    case US_READY:
      
      GPIO_SetBits(TRIG_PORT, TRIG_PIN);
      state = US_TRIGGER;
      rx_complete = 0;
      break;
    case US_TRIGGER:
      GPIO_ResetBits(TRIG_PORT, TRIG_PIN);
      pulse_width_tmp = 0;
      idle_width = 0;
      state = US_WAITING_FOR_ECHO;
      break;
    case US_WAITING_FOR_ECHO:
      if(GPIO_ReadInputDataBit(ECHO_PORT, ECHO_PIN) == 1) {
        pulse_width_tmp = 0;
        state = US_ECHO_RAISED;
      }
      else if (idle_width++ >= US_IDLE_RESET_COUNT) {
        idle_width = 0;
        state = US_READY;
      }
      break;
    case US_ECHO_RAISED:
      ++pulse_width_tmp;
      if(GPIO_ReadInputDataBit(ECHO_PORT, ECHO_PIN) == 0 || pulse_width_tmp >= US_MAX_WIDTH) {
        pulse_width = pulse_width_tmp;
        pulse_width_tmp = 0;
        //handle get distance
        dist = pulse_width * 34 / 10;
        dist +=200;
                  LCD_DrawChar(2,0, '0' + (dist/1000)%10);
        LCD_DrawChar(2,8, '0' + (dist/100)%10);
        LCD_DrawChar(2,16, '0' + (dist/10)%10);
        LCD_DrawChar(2,24, '0' + (dist%10));        
        state = US_ECHO_FALLEN;
       
//        TIM_Cmd(ULTRASONIC_TIM, DISABLE); 
//        RCC_APB1PeriphClockCmd(ULTRASONIC_RCC , DISABLE);
//  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, DISABLE);
//  TIM_ITConfig(ULTRASONIC_TIM, TIM_IT_Update, DISABLE); 
//  TIM_ITConfig(ULTRASONIC_TIM, TIM_IT_CC1, DISABLE); 
  NVIC_InitStructure.NVIC_IRQChannelCmd = DISABLE;
  NVIC_Init(&NVIC_InitStructure);
      }
      break;
      case US_ECHO_FALLEN:
        state = US_READY;
        break;
    }
    
  }
}