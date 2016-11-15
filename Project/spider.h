#ifndef _SPIDER_H
#define _SPIDER_H

#include "stm32f10x.h"
#include "servo.h"

typedef struct {
  int init;
  int final;
} Servo;

enum legs {
  FRONT_LEFT = 0,
  FRONT_RIGHT,
  BACK_LEFT,
  BACK_RIGHT
};

void Delayms(u32 m);

void spider_init(void);
void move_leg_forward(int leg, int delay);
void move_leg_backward(int leg, int delay);
void move_robot_forward(void);
void move_robot_backward(void);





#endif
