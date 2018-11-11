#include "main.h"

//motors
Motor intake1(3, MOTOR_GEARSET_36, 1, MOTOR_ENCODER_DEGREES);

//line sensors
ADILineSensor line_L('A');
ADILineSensor line_I('B');
ADILineSensor line_R('C');


void intake(int vel){
  intake1.move(vel);
}

bool hasBall(){
  if(line_L.get_value() < 2000 || line_R.get_value() < 2000)
    return true;
  else
    return false;
}

bool isLoaded(){
  if(line_I.get_value() < 2000)
    return true;
  else
    return false;
}

void intakeOp(){
  static int vel;

  intake(vel);

  if(master.get_digital(DIGITAL_R1))
    vel = 127;
  else if(master.get_digital(DIGITAL_L1))
    vel = -127;
  else
    vel = 0;
}


//task
static int intakeTarget = 0;

void intakeTask(void* parameter){
  while(1){
    delay(20);

    printf("intakeTarget: %d\n", intakeTarget);

    if(intakeTarget == 1){
      intake(127);
      while(!hasBall()) delay(20);
      intake(0);
      intakeTarget = 0;
    }

    if(intakeTarget == 2){
      intake(127);
      while(!isLoaded()) delay(20);
      intake(0);
      intakeTarget = 0;
    }
  }
}

void intakeBall(){
  intakeTarget = 1;
}

void loadBall(){
  intakeTarget = 2;
}
