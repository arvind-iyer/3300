#include "servo.h"
#include "gpio.h"

void servo_timer_init(void) {
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  TIM_OCInitTypeDef  TIM_OCInitStructure;
  
  TIM_TimeBaseStructure.TIM_Period = 20000-1;// <- TIMx_ARR register .....since 72Mhz/ARR= 3600
  TIM_TimeBaseStructure.TIM_Prescaler = 71; //prescalar -->(72Mhz/ARR)/72= 50Hz
  TIM_TimeBaseStructure.TIM_ClockDivision = 0; 
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; 
  TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);//mapping timebase to TIM1
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);//mapping timebase to TIM2
  TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);//mapping timebase to TIM4 
  TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure);//mapping timebase to TIM8 
  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);//mapping timebase to TIM3
  //setup TIMx output compare
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 
  TIM_OCInitStructure.TIM_Pulse = 1000;  //<- TIMx_CCRx register since duty cycle = CCRx/ARR= 1000/20000=5% duty cycle
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; 
  TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High; 
  TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set; 
  TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset; 

  //enable clock
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
  // OC Init
  TIM_OC1Init(TIM1, &TIM_OCInitStructure);//initialize channel 1 
  TIM_OC1PreloadConfig(TIM1, ENABLE);//enable channel 1 of the timer4
  
  TIM_OC2Init(TIM1, &TIM_OCInitStructure);
  TIM_OC2PreloadConfig(TIM1, ENABLE);//enable TIM1 Channel 2

  TIM_OC3Init(TIM1, &TIM_OCInitStructure);
  TIM_OC3PreloadConfig(TIM1, ENABLE);//enable TIM1 Channel 3
  
  TIM_OC4Init(TIM1, &TIM_OCInitStructure);
  TIM_OC4PreloadConfig(TIM1, ENABLE);//enable TIM1 Channel 4
  
  TIM_ARRPreloadConfig(TIM1, ENABLE);
  //enable timer 1
  TIM_Cmd(TIM1, ENABLE);
  TIM_CtrlPWMOutputs(TIM1, ENABLE); 
  
 //Repeat the same for TIM 8, 4, 3 and 2
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);
  // OC Init
  TIM_OC1Init(TIM8, &TIM_OCInitStructure);
  TIM_OC1PreloadConfig(TIM8, ENABLE);
 
  TIM_OC2Init(TIM8, &TIM_OCInitStructure);
  TIM_OC2PreloadConfig(TIM8, ENABLE);

  TIM_OC3Init(TIM8, &TIM_OCInitStructure);
  TIM_OC3PreloadConfig(TIM8, ENABLE);
  
  TIM_OC4Init(TIM8, &TIM_OCInitStructure);
  TIM_OC4PreloadConfig(TIM8, ENABLE);
  
  TIM_ARRPreloadConfig(TIM8, ENABLE);
  //enable timer
  TIM_Cmd(TIM8, ENABLE); 
  TIM_CtrlPWMOutputs(TIM8, ENABLE);
  
  //enable clock
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
  // OC Init
  TIM_OC1Init(TIM4, &TIM_OCInitStructure);
  TIM_OC1PreloadConfig(TIM4, ENABLE);
  
  TIM_OC2Init(TIM4, &TIM_OCInitStructure);
  TIM_OC2PreloadConfig(TIM4, ENABLE);

  TIM_OC3Init(TIM4, &TIM_OCInitStructure);
  TIM_OC3PreloadConfig(TIM4, ENABLE);
  
  TIM_OC4Init(TIM4, &TIM_OCInitStructure);
  TIM_OC4PreloadConfig(TIM4, ENABLE);
  
  TIM_ARRPreloadConfig(TIM4, ENABLE);
  //enable timer
  TIM_Cmd(TIM4, ENABLE); 

  //setup TIMx output compare
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 
    TIM_OCInitStructure.TIM_Pulse = 1000;  //<- TIMx_CCRx register since duty cycle = CCRx/ARR= 1000/20000=5% duty cycle
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; 
    //
    
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
  // OC Init
  TIM_OC1Init(TIM3, &TIM_OCInitStructure);
  TIM_OC1PreloadConfig(TIM3, ENABLE);
  
  
  TIM_ARRPreloadConfig(TIM3, ENABLE);
  //enable timer
  TIM_Cmd(TIM3, ENABLE); 


    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    TIM_OC4Init(TIM2, &TIM_OCInitStructure);
    TIM_OC4PreloadConfig(TIM2, ENABLE);
    
    TIM_ARRPreloadConfig(TIM2, ENABLE);
    TIM_Cmd(TIM2, ENABLE);

}


void servo_init()
{
   //initialize PB 
  gpio_init(GPIOB, GPIO_Pin_6 | GPIO_Pin_8 | GPIO_Pin_9, GPIO_Speed_50MHz,GPIO_Mode_AF_PP, 1);
  
    //initialize PA 
  gpio_init(GPIOA,GPIO_Pin_3 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 , GPIO_Speed_50MHz,GPIO_Mode_AF_PP, 1);
  
  //initialize  PC
  gpio_init(GPIOC, GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9, GPIO_Speed_50MHz,GPIO_Mode_AF_PP, 1);
  
  servo_timer_init();
}

void servo_control(int servo_id, int val)// val controls the PWM Duty Cycle High Time and hence the servo angle
{
 
  
   switch(servo_id) {
  case 1:
    TIM_SetCompare1(TIM8, val);
    break;
  case 2:
    TIM_SetCompare2(TIM8, val);
    break;
  case 3:
    TIM_SetCompare3(TIM8, val);
    break;
  case 4:
    TIM_SetCompare4(TIM8, val);
    break;
  case 5:
    TIM_SetCompare1(TIM1, val);
    break;
  case 6:
    TIM_SetCompare2(TIM1, val);
    break;
  case 7:
    TIM_SetCompare3(TIM1, val);
    break;
  case 8:
    TIM_SetCompare4(TIM1, val);
    break;
  case 9:
    TIM_SetCompare1(TIM4, val);
    break;
  case 10:
    TIM_SetCompare4(TIM2, val);
    break;
  case 11:
    TIM_SetCompare3(TIM4, val);
    break;
  case 12:
    TIM_SetCompare4(TIM4, val);
    break;
  }
}
