#include "stm32f10x.h"

#define FL_FOOT  1 //25 -> 120(UP)  B6
#define FL_KNEE  2 //90 -> -60      B7
#define FL_HIP   3 //150 -> 0       B8

#define FR_FOOT  4 //-40 -> -100    B9
#define FR_KNEE  5 //210 -> 310     A6
#define FR_HIP   6 //160 -> 280     A7

#define BL_FOOT  7 //220 -> 90      B0
#define BL_KNEE  8 //250 -> 320     B1
#define BL_HIP   9 //120 -> 240     A0

#define BR_FOOT 10 //50  -> 200     A1
#define BR_KNEE 11 //240 -> 180     A2
#define BR_HIP  12 //90  ->   0     A3



void servo_init(void);
void servo_control(int servo_id, int val);