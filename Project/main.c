/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_conf.h"
#include "stm32f10x.h"
#include "uart.h"
#include "servo.h"
#include "spider.h"
#include "ultrasonic.h"
#include "lcd.h"


void LongDelay(u32 nCount)
{
  for(; nCount != 0; nCount--);
}
Servo servo[13] = {
  {0,0}, 
  {1200,1200},//1
  {1200,800}, 
  {1400,1000},
  {1000,1000},//4
  {2000,2500},
  {2000,2500},
  {2200,2200}, //7
  {2000,2600},
  {1800,1200},
  {1500,1500}, //10
  {2600,1800},
  {1200,1800}
};

GPIO_InitTypeDef GPIO_InitStructure;
TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
TIM_OCInitTypeDef  TIM_OCInitStructure;

void bot_init(){
    servo_control(1, 1200);
  servo_control(2, 1200);
  servo_control(3, 1400);
  servo_control(4, 1000);
  servo_control(5, 2000);
  servo_control(6, 2000);
  servo_control(7, 2200);
    servo_control(8, 2300);
  servo_control(9, 1400);
  servo_control(10, 1500);
  servo_control(11, 2800);
  servo_control(12, 1300);
}

void leg_forward(int l) {
  assert_param(l < 4);
  int leg = l*3;
  servo_control(leg + 1,servo[leg+1].final);
  servo_control(leg + 2,servo[leg+2].final);
  Delayms(80);
  servo_control(3, 1000);
  Delayms(80);
  servo_control(2,1200);
  Delayms(80);
}
void push_ups()
{
     servo_control(2, 1200);
    servo_control(5, 2000);
    servo_control(8, 2100);
    servo_control(11, 2600);
    Delayms(80);
    servo_control(2, 800);
    servo_control(5, 2500);
    servo_control(8, 2600);
    servo_control(11, 2000);
     Delayms(80);
 

}

void go_front(speed) {
servo_control(1, 1200);
  servo_control(2, 1200);
  servo_control(3, 1400);
  servo_control(4, 1000);
  servo_control(5, 2000);
  servo_control(6, 2000);
  servo_control(7, 2100);
  servo_control(8, 2200);
  servo_control(9, 1800);
  servo_control(10, 1500);
  servo_control(11, 2800);
  servo_control(12, 1300);
  
  Delayms(speed);
   servo_control(1,1200);
  servo_control(2,800);
  Delayms(speed);
  servo_control(3, 1200);
  Delayms(speed);
  servo_control(2,1200);
  Delayms(speed);
  
  servo_control(4, 1000);
  servo_control(5, 2500);
  Delayms(speed);
  servo_control(6, 2300);
  Delayms(speed);
  servo_control(5,2000);
  Delayms(speed);
  servo_control(6,2000);
  
  servo_control(3, 1400);
  
  servo_control(9, 1400);
  servo_control(12, 1600);
  Delayms(speed);
}

void turn_right(speed) {
  servo_control(1, 1200);
  servo_control(2, 1200);
  servo_control(3, 1400);
  servo_control(4, 1000);
  servo_control(5, 2000);
  servo_control(6, 2000);
  servo_control(7, 2100);
  servo_control(8, 2200);
  servo_control(9, 1800);
  servo_control(10, 1500);
  servo_control(11, 2800);
  servo_control(12, 1300);
  
    
  Delayms(speed);
  servo_control(2,800);
  Delayms(speed);
  servo_control(3, 1200);
  Delayms(speed);
  servo_control(2,1200);
  Delayms(speed);
  
  servo_control(5, 2200);
  Delayms(speed);
    
  servo_control(8, 2600);
  Delayms(speed);
  servo_control(9,1200);
  Delayms(speed);
  servo_control(8, 2200);
  Delayms(speed);
  
  
    servo_control(11,1800);
  Delayms(speed);
  servo_control(12,800);
  Delayms(speed);
  servo_control(11,2600);
  Delayms(speed);  
  
  servo_control(3, 1400);
  servo_control(12, 1300);
  Delayms(speed);
  
  
  servo_control(5,2500);
  Delayms(speed);
  servo_control(6,1800);
  Delayms(speed);
  servo_control(5,2000);
  Delayms(speed);

    servo_control(2,800);
  Delayms(speed);
  servo_control(3, 1200);
  Delayms(speed);
  servo_control(2,1200);
  Delayms(speed);

}

void turn_left(speed) {
  servo_control(1, 1200);
  servo_control(2, 1200);
  servo_control(3, 1400);
  servo_control(4, 1000);
  servo_control(5, 2000);
  servo_control(6, 2000);
  servo_control(7, 2100);
  servo_control(8, 2200);
  servo_control(9, 1200);
  servo_control(10, 1500);
  servo_control(11, 2800);
  servo_control(12, 1300);
  
  
  servo_control(5, 2500);
  Delayms(speed);
  servo_control(6, 2300);
  Delayms(speed);
  servo_control(5,2000);
  Delayms(speed);
  
    Delayms(speed);
  servo_control(11,1800);
  Delayms(speed);
  servo_control(12,1800);
  Delayms(speed);
  servo_control(11,2500);
  Delayms(speed);

    Delayms(speed); 
  servo_control(8, 2300);
  Delayms(speed);
  servo_control(9, 1900);
  Delayms(speed);   
  servo_control(8, 2000);
  Delayms(speed);


}


void cross_leg_move_forward(int speed)
{
  
  servo_control(1, 1200);
  servo_control(2, 1200);
  servo_control(3, 1400);
  servo_control(4, 1000);
  servo_control(5, 2000);
  servo_control(6, 2000);
  servo_control(7, 2200);
  servo_control(8, 2300);
  servo_control(9, 1400);
  servo_control(10, 1500);
  servo_control(11, 2800);
  servo_control(12, 1300);
  servo_control(2,800);
  Delayms(speed);
  servo_control(3, 1200);
  Delayms(speed);
  servo_control(2,1200);
  Delayms(speed);
  Delayms(speed); 
  servo_control(8, 2300);
  Delayms(speed);
  servo_control(9, 1900);
  Delayms(speed);   
  servo_control(8, 2000);
  Delayms(speed);
  

  //pull back
  servo_control(3, 1400);
  servo_control(9, 1300); 
  
  servo_control(5, 2500);
  Delayms(speed);
  servo_control(6, 2300);
  Delayms(speed);
  servo_control(5,2000);
  Delayms(speed);
     
     
  servo_control(11,1800);
  Delayms(speed);
  servo_control(12,800);
  Delayms(speed);
  servo_control(11,2600);
  Delayms(speed);  

     
  //pull back
  servo_control(6,2000);  
  servo_control(12, 1200);
}

void left_strafe(int speed) {
 
  servo_control(1, 1200);
  servo_control(2, 1200);
  servo_control(3, 1400);
  servo_control(4, 1000);
  servo_control(5, 2000);
  servo_control(6, 2000);
  servo_control(7, 2200);
  servo_control(8, 2300);
  servo_control(9, 1400);
  servo_control(10, 1500);
  servo_control(11, 2800);
  servo_control(12, 1300);
  
    
  servo_control(2, 1000);
  servo_control(1, 1700);
  Delayms(speed);
  servo_control(2, 1200);
  Delayms(speed);
  
   servo_control(11, 2000);
   Delayms(speed);
  
   servo_control(10, 2000);
   Delayms(speed);
   servo_control(11,2500);
   Delayms(speed); 
   Delayms(speed);
   
   servo_control(10,1500);
   servo_control(11,2600);
   servo_control(1,1200);
   servo_control(2,1200);
   
   servo_control(7, 1600);  
   servo_control(4,600);
   Delayms(speed);
   
   servo_control(5,2500);
   Delayms(speed);
   
   servo_control(4,1000);
   Delayms(speed);
   
   servo_control(8,2600);
   Delayms(speed);
   
   servo_control(7,2200);
   Delayms(speed);
   
   servo_control(1,1000);
   servo_control(10, 1200);
   servo_control(5, 1600);
   servo_control(8, 2000);
}


void right_strafe(int speed) {
 
  servo_control(1, 1200);
  servo_control(2, 1200);
  servo_control(3, 1400);
  servo_control(4, 1000);
  servo_control(5, 2000);
  servo_control(6, 2000);
  servo_control(7, 2200);
  servo_control(8, 2300);
  servo_control(9, 1400);
  servo_control(10, 1500);
  servo_control(11, 2800);
  servo_control(12, 1300);
  
    
  servo_control(5, 2500);
  Delayms(speed);
  servo_control(4, 500);
  Delayms(speed);
  servo_control(5, 2000);
  Delayms(speed);
  
  
  servo_control(8, 2600);
  Delayms(speed);
  servo_control(7, 1600);
  Delayms(speed);
  servo_control(8, 2000);
  Delayms(speed);
  
   servo_control(10,2000);
   servo_control(7,2200);
   servo_control(1,1600);
   servo_control(4,1000);
   Delayms(speed);
   
   servo_control(11, 1800);
   Delayms(speed);
   servo_control(10, 1500);
   Delayms(speed);
   servo_control(11, 2800);
   Delayms(speed);
 
   servo_control(2, 800);
   Delayms(speed);
   servo_control(1, 1200);
   Delayms(speed);
   servo_control(2, 1200);
   Delayms(speed);
}


void go_back(int speed) {
  
  Delayms(speed);
  servo_control(11,1800);
  Delayms(speed);
  servo_control(12,1800);
  Delayms(speed);
  servo_control(11,2500);
  Delayms(speed);
 
  
  

  
  servo_control(8, 2600);
  Delayms(speed);
  servo_control(9,1200);
  Delayms(speed);
  servo_control(8, 2300);
  Delayms(speed);
  servo_control(2,800);
  Delayms(speed);
  servo_control(3,1700);
  Delayms(speed);
  servo_control(2, 1200);
  Delayms(speed);
   servo_control(5,2500);
  Delayms(speed);
  servo_control(6,1800);
  Delayms(speed);
  servo_control(5,2000);
  Delayms(speed);
  servo_control(6,2000);
  servo_control(12,1600);

  servo_control(9,1800);
  servo_control(3, 1400);
  
  Delayms(speed); 
  
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
                         RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOC | 
                         RCC_APB2Periph_GPIOE | RCC_APB2Periph_GPIOF | 
                         RCC_APB2Periph_GPIOG, DISABLE); 
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FSMC, ENABLE);

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOE | RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB |
                         RCC_APB2Periph_GPIOF | RCC_APB2Periph_GPIOG |
                         RCC_APB2Periph_AFIO, ENABLE);
  //initialize LCD
  STM3210E_LCD_Init(); 
  LCD_Clear(); 
  int speed = 20;// speed is the amount of delay in ms between motions  
  servo_init();//initialize the servo pins and timers
  uart_init(COM3,9600);//initialize usart3 and the port of the bluetooth 

  bot_init();//initial spider standing position
  us_init();//Ultrasonic Sensor initialize the interrupt
  u16 last = 50;
  while (1) {
    
    int rec = uart_rx_byte(COM3);
    LCD_DrawChar(4,4, '0' + rec);
    us_enable();// enable the interrupt
    if(get_dist() > 0 && get_dist() < 1000) { // get_dist gets ditance of obstacle from robot
      rec = 0;
    }
    switch (rec) {
    case 0: // If 0 is received from android phone or distance of obstacle<100mm then Initial Standing Position
      bot_init();
      break;
    case 1://If 1 is received from android phone then walk forward
      cross_leg_move_forward(speed);
      break;
    case 2://If 2 is received from android phone then crawl left
      left_strafe(speed);
      break;
    case 3://If 3 is received from android phone then crawl right
      right_strafe(speed);
      break;
    case 4://If 4 is received from android phone then do push ups
      push_ups();
      break;
    case 5://If 5 is received from android phone then turn left
      turn_left(speed);
      break;
    case 6://If 6 is received from android phone then turn right
      turn_right(speed);
      break;
    default:
      break;
      }
    }
    
    Delayms(100);
  }


//1 for front 
//2 for left crawl
//3 for right crawl
//4 for push ups
//5 for left turn
//6 for right turn
//0 for stop and initial position


