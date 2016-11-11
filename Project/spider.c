#include "spider.h"

#define FOOT 1
#define KNEE 2
#define HIP  3
#define JOINTS 3
#define SPEED 50


Servo servos[12] = {
  {25,120},
  {90,-60},
  {150,0},
  {-40,-100},
  {210,310},
  {160,280},
  {220,90},
  {250,320},
  {120,240},
  {50,200},
  {240,180},
  {90,0}
};


void Delayms(u32 m)
{
  u32 i;
  
  for(; m != 0; m--)	
       for (i=0; i<50000; i++);
}

void spider_init(void) {
  for(int i = 0; i < 12; i++) {
    servo_control(i+1, servos[i].init);
  }
}
void move_leg_forward(int  leg, int delay) {
  int this_leg = leg*JOINTS;
  for(int i = 1; i <= JOINTS; i++) {
    servo_control(this_leg + i, servos[this_leg+i].final);
    Delayms(delay);
  }
}

void move_leg_backward(int leg, int delay) {
  int this_leg = leg*JOINTS;
  for(int i = 1; i <= JOINTS; i++) {
    servo_control(this_leg + i, servos[this_leg+i].init);
    Delayms(delay);
  }
}

void move_robot_forward(void) {
  move_leg_forward(FRONT_LEFT, SPEED);
  move_leg_forward(FRONT_RIGHT, SPEED);
  move_leg_forward(BACK_LEFT, SPEED);
  move_leg_forward(BACK_RIGHT, SPEED);
  
  move_leg_backward(FRONT_LEFT,0);
  move_leg_backward(FRONT_RIGHT, 0);
  move_leg_backward(BACK_LEFT, 0);
  move_leg_backward(BACK_RIGHT, 0);
}

void move_robot_backward(void) {
  
  move_leg_backward(BACK_LEFT, SPEED);
  move_leg_backward(BACK_RIGHT, SPEED);
  move_leg_backward(FRONT_LEFT, SPEED);
  move_leg_backward(FRONT_RIGHT, SPEED);
  
  
  move_leg_forward(BACK_LEFT, 0);
  move_leg_forward(BACK_RIGHT, 0);
  move_leg_forward(FRONT_LEFT,0);
  move_leg_forward(FRONT_RIGHT, 0);
}
