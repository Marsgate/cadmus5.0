#include "main.h"


Motor lift1(LIFT, MOTOR_GEARSET_36, 1, MOTOR_ENCODER_DEGREES);



/**************************************************/
//basic control
void lift(int vel){
  lift1.set_brake_mode(MOTOR_BRAKE_HOLD);
  lift1.move(vel);
}

void setLiftAsync(int sp){
  sp *= 5; // gear ratio compensation
  lift1.move_absolute(sp, 100);
}

void setLift(int sp){
  setLiftAsync(sp);
  int sv = lift1.get_position();
  while(sv != sp) delay(20);
}

/**************************************************/
//operator control
void liftOp(){
  static int vel;

  lift(vel);

  if(master.get_digital(DIGITAL_X))
    vel = 127;
  else if(master.get_digital(DIGITAL_B))
    vel = -127;
  else
    vel = 0;

}
