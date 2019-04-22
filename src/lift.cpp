#include "main.h"

static int holdPostion;

Motor lift1(LIFT, MOTOR_GEARSET_18, 1, MOTOR_ENCODER_DEGREES);

/**************************************************/
//basic control
void lift(int vel){
  lift1.set_brake_mode(MOTOR_BRAKE_HOLD);
  lift1.move(vel);
}

void liftFast(int sp){
  sp *= 5; // gear ratio compensation
  lift1.move_absolute(sp, 200);
}

void liftSlow(int sp){
  sp *= 5; // gear ratio compensation
  lift1.move_absolute(sp, 60);
}

/**************************************************/
//operator control
void liftOp(){
  static int vel;

  if(master.get_digital(DIGITAL_Y))
    liftFast(186);
  else
    lift(vel);

  if(master.get_digital(DIGITAL_X)){
    if(lift1.get_position() < 560)
      vel = 127;
    else
      vel = 65;
  }else if(master.get_digital(DIGITAL_B)){
    vel = -127;
  }else{
    vel = 0;
    if(lift1.get_position() > 50 && lift1.get_position() < 550){
      vel = 10;
    }else if(lift1.get_position() > 800){
      vel = -10;
    }
  }

}
