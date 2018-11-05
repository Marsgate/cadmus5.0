#include "main.h"

//motors
Motor adjuster_1(5);

void adjuster(int vel){
  adjuster_1.move(vel);
}

void adjusterOp(){
  static int vel = 0;
  static int d = 1;
  static int t = 0;
  t++;

  adjuster(vel);

  if(master.get_digital(DIGITAL_L2))
    vel = 127*d, t = 0, d = -d;
  else if(t > 45)
    adjuster(0);
}
