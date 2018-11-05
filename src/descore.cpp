#include "main.h"

//motors
Motor descore_1(6);

void descore(int vel){
  descore_1.move(vel);
}

void descoreOp(){
  static int vel;

  descore(vel);

  if(master.get_digital(DIGITAL_X))
    vel = 127;
  else if(master.get_digital(DIGITAL_B))
    vel = -127;
  else
    vel = 0;

}
