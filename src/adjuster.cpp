#include "main.h"

static int d = -1;

//motors
Motor adjuster1(5, MOTOR_GEARSET_6, 1);

void adjuster(int vel){
  adjuster1.move(vel);
}

void autoAdjust(int direction){
  d = direction;
  delay(300);
}

void adjusterOp(){
  static int vel = 0;
  static int t = 0;

  if(t <= 15)
    t++;

  adjuster(vel);

  if(master.get_digital_new_press(DIGITAL_L2))
    vel = 127*d, t = 0, d = -d;
  else if(t > 15)
    adjuster(0);

}


//tasks
void adjustTask(void* parameter){
  int lastDirection = d;
  while(1){
    delay(20);
    if(lastDirection == d)
      continue;

    lastDirection = d;
    adjuster(127*d);
    delay(300);
    adjuster(0);
  }
}

void startAdjust(int direction){
  d = direction;
}
