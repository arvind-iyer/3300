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

void move_leg_forward(enum leg, int delay);
void move_leg_backward(enum leg, int delay);
void move_robot_forward(void);
