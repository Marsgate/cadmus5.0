#include "main.h"

//motors
Motor adjuster1(5, MOTOR_GEARSET_6);

void adjuster(int vel){
  adjuster1.move(vel);
}

void adjusterOp(){
  static int vel = 0;
  static int d = 1;
  static int t = 0;
  t++;

  adjuster(vel);

  if(master.get_digital_new_press(DIGITAL_L2))
    vel = 127*d, t = 0, d = -d;
  else if(t > 15)
    adjuster(0);
}
