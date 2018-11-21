#include "main.h"


Motor descore1(16, 1);

/**************************************************/
//basic control
void descore(int vel){
  descore1.move(vel);
}

/**************************************************/
//operator control
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
