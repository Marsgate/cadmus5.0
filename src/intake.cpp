#include "main.h"

//motors
Motor intake_1(3, 1);

//line sensors
ADIAnalogIn line_L('A');
ADIAnalogIn line_R('B');
ADIAnalogIn line_I('C');

void intake(int vel){
  intake_1.move(vel);
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
void intakeBallTask(void* parameter){
  intake(127);
  while(!hasBall()) delay(20);
  intake(0);
}

void loadBallTask(void* parameter){
  intake(127);
  while(!isLoaded()) delay(20);
  intake(0);
}

void intakeBall(){
  Task intakeTask(intakeBallTask);
}

void loadBall(){
  Task loadTask(loadBallTask);
}
