#include "main.h"

static int intakeTarget = 0;

//motors
Motor intake1(3, MOTOR_GEARSET_36, 1, MOTOR_ENCODER_DEGREES);

//line sensors
ADILineSensor line_L('A');
ADILineSensor line_I('B');
ADILineSensor line_R('C');

/**************************************************/
//basic control
void intake(int vel){
  intake1.move(vel);
}

/**************************************************/
//feedback
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

/**************************************************/
//autonomous control
void intakeBallAsync(){
  intakeTarget = 1;
}

void loadBallAsync(){
  intakeTarget = 2;
}

void intakeBall(){
  intake(127);
  while(!hasBall()) delay(20);
  intake(0);
}

void loadBall(){
  intake(127);
  while(!isLoaded()) delay(20);
  intake(0);
}

/**************************************************/
//task control
void intakeTask(void* parameter){
  while(1){

    switch(intakeTarget){
      case 1:
        intakeBall();
        break;
      case 2:
        loadBall();
        break;
    }

    intakeTarget = 0;
    delay(20);
  }
}

/**************************************************/
//operator control
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
