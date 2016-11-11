#include "spider.h"
#define FOOT 1
#define KNEE 2
#define HIP  3
#define JOINTS 3
#define SPEED 100

void move_leg_forward(enum leg, int delay) {
  int this_leg = leg*JOINTS;
  for(int i = 1; i <= JOINTS; i++) {
    servo_control(this_leg + i, legs[this_leg+i].final);
    Delayms(delay);
  }
}

void move_leg_backward(enum leg, int delay) {
  int this_leg = leg*JOINTS;
  for(int i = 1; i <= JOINTS; i++) {
    servo_control(this_leg + i, legs[this_leg+i].init);
    Delayms(delay);
  }
}

void move_robot_forward(void) {
  move_leg_forward(FRONT_LEFT, 100);
  move_leg_forward(FRONT_RIGHT, 100);
  move_leg_forward(BACK_LEFT, 100);
  move_leg_forward(BACK_RIGHT, 100);
  
  move_leg_backward(FRONT_LEFT,0);
  move_leg_backward(FRONT_RIGHT, 0);
  move_leg_backward(BACK_LEFT, 0);
  move_leg_backward(BACK_RIGHT, 0);
}
