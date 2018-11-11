#include "main.h"

//motors
Motor descore1(6, 1);

void descore(int vel){
  descore1.move(vel);
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
