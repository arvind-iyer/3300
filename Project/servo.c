#include "servo.h"


void servo_init()//function for initialization defined by me
{
  /* Private typedef -----------------------------------------------------------*/
GPIO_InitTypeDef GPIO_InitStructure;
TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
TIM_OCInitTypeDef  TIM_OCInitStructure;
  //initialize PB 
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
  GPIO_InitStructure.GPIO_Pin= GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9;//Initialize pin 6 and 8
  GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;//initialize to push pull
  GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;//Initialize to 50Mhz
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  
    //initialize PA 
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  GPIO_InitStructure.GPIO_Pin= GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_6 | GPIO_Pin_7;//Initialize pin 6 and 8
  GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;//initialize to push pull
  GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;//Initialize to 50Mhz
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  //Now initialize TIM4 
  //setup TIMx timebase  
    TIM_TimeBaseStructure.TIM_Period = 20000-1;// <- TIMx_ARR register .....since 72Mhz/ARR= 3600
    TIM_TimeBaseStructure.TIM_Prescaler = 71; //prescalar -->(72Mhz/ARR)/72= 50Hz
    TIM_TimeBaseStructure.TIM_ClockDivision = 0; 
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; 
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);//mapping timebase to TIM3
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);//mapping timebase to TIM3 
    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);//mapping timebase to TIM4   
    TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);//mapping timebase to TIM4   
    //setup TIMx output compare
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 
    TIM_OCInitStructure.TIM_Pulse = 1000;  //<- TIMx_CCRx register since duty cycle = CCRx/ARR= 1000/20000=5% duty cycle
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; 
    // TIM_OC1Init(TIM4, &TIM_OCInitStructure);  
    //enable clock
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
    // OC Init
    TIM_OC1Init(TIM4, &TIM_OCInitStructure);//initialize channel 1 
    TIM_OC1PreloadConfig(TIM4, ENABLE);//enable channel 1 of the timer4
    
    TIM_OC2Init(TIM4, &TIM_OCInitStructure);//initialize channel 2
    TIM_OC2PreloadConfig(TIM4, ENABLE);//enable channel 3 of timer4

    TIM_OC3Init(TIM4, &TIM_OCInitStructure);//initialize channel 2
    TIM_OC3PreloadConfig(TIM4, ENABLE);//enable channel 3 of timer4
    
    TIM_OC4Init(TIM4, &TIM_OCInitStructure);//initialize channel 2
    TIM_OC4PreloadConfig(TIM4, ENABLE);//enable channel 3 of timer4
    
    TIM_ARRPreloadConfig(TIM4, ENABLE);
    //enable timer
    TIM_Cmd(TIM4, ENABLE);
    
    //TIM_SetCounter(TIM4,0); //dont know if i should add these
    //TIM_CtrlPWMOutputs(TIM4, ENABLE);
    
    //do the same things for timer 3
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
    // OC Init
    TIM_OC1Init(TIM3, &TIM_OCInitStructure);//initialize channel 1 
    TIM_OC1PreloadConfig(TIM3, ENABLE);//enable channel 1 of the timer4
    
    TIM_OC2Init(TIM3, &TIM_OCInitStructure);//initialize channel 2
    TIM_OC2PreloadConfig(TIM3, ENABLE);//enable channel 3 of timer4

    TIM_OC3Init(TIM3, &TIM_OCInitStructure);//initialize channel 2
    TIM_OC3PreloadConfig(TIM3, ENABLE);//enable channel 3 of timer4
    
    TIM_OC4Init(TIM3, &TIM_OCInitStructure);//initialize channel 2
    TIM_OC4PreloadConfig(TIM3, ENABLE);//enable channel 3 of timer4
    
    TIM_ARRPreloadConfig(TIM3, ENABLE);
    //enable timer
    TIM_Cmd(TIM3, ENABLE);
    
    //same things for tim5
    
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
    TIM_OC4Init(TIM5, &TIM_OCInitStructure);
    TIM_OC4PreloadConfig(TIM5, ENABLE);
    TIM_ARRPreloadConfig(TIM5, ENABLE);
    TIM_Cmd(TIM5, ENABLE);
    //same things for tim2
    
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    TIM_OC1Init(TIM2, &TIM_OCInitStructure);
    TIM_OC1PreloadConfig(TIM2, ENABLE);
    
    TIM_OC2Init(TIM2, &TIM_OCInitStructure);
    TIM_OC2PreloadConfig(TIM2, ENABLE);
    
    TIM_OC3Init(TIM2, &TIM_OCInitStructure);
    TIM_OC3PreloadConfig(TIM2, ENABLE);
    
    TIM_OC4Init(TIM2, &TIM_OCInitStructure);
    TIM_OC4PreloadConfig(TIM2, ENABLE);
    
    TIM_ARRPreloadConfig(TIM2, ENABLE);
    TIM_Cmd(TIM2, ENABLE);
    
    
    
}

void servo_control(int servo_id, int val)// val is the angle of the servo
{
  //the pwm goes from 1000/20000 to 2000/20000 so TIMx_CCRx has 1000 values. over 180 degrees, each degree is 1000/180=5.55 
  if( servo_id == 1 )//servo id 1 is channel 1 of TIM4
  {
      TIM_SetCompare1(TIM4, 900+(6.66*val));// sets TIMx_CCRx value of channel 1 of timer 4 
  }
  if( servo_id == 2 )//channel 2 of TIM4
  {
      TIM_SetCompare2(TIM4, 1000+(5.55*val));// sets TIMx_CCRx value of channel 1 of timer 4 
  }
  if( servo_id == 3 )//channel 3 of TIM4
  {
      TIM_SetCompare3(TIM4, 1000+(5.55*val));// sets TIMx_CCRx value of channel 1 of timer 4 
  }
  if(servo_id==4)//channel 4 of TIM4
  {
      TIM_SetCompare4(TIM4, 1000+(5.55*val));// sets TIMx_CCRx value of channel 3 of timer 4 
  }
  
   if(servo_id==5)//channel 1 of TIM3
  {
      TIM_SetCompare1(TIM3, 1000+(5.55*val));// sets TIMx_CCRx value of channel 3 of timer 4 
  }
   if(servo_id==6)//channel 2 of TIM3
  {
      TIM_SetCompare2(TIM3, 1000+(5.55*val));// sets TIMx_CCRx value of channel 3 of timer 4 
  }
   if(servo_id==7)//channel 3 of TIM3
  {
      TIM_SetCompare3(TIM3, 1000+(5.55*val));// sets TIMx_CCRx value of channel 3 of timer 4 
  }
   if(servo_id==8)//channel 4 of TIM3
  {
      TIM_SetCompare4(TIM3, 1000+(5.55*val));// sets TIMx_CCRx value of channel 3 of timer 4 
  }
  
     if(servo_id==9)//channel 4 of TIM5
  {
      TIM_SetCompare1(TIM2, 1000+(5.55*val));// sets TIMx_CCRx value of channel 3 of timer 4 
  }
       if(servo_id==10)//channel 1 of TIM2
  {
      TIM_SetCompare2(TIM2, 1000+(5.55*val));// sets TIMx_CCRx value of channel 3 of timer 4 
  }
       if(servo_id==11)//channel 3 of TIM2
  {
      TIM_SetCompare3(TIM2, 1000+(5.55*val));// sets TIMx_CCRx value of channel 3 of timer 4 
  }
       if(servo_id==12)//channel 4 of TIM2
  {
      TIM_SetCompare4(TIM2, 1000+(5.55*val));// sets TIMx_CCRx value of channel 3 of timer 4 
  }
}
