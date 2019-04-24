#include "main.h"

static int intakeTarget = 0;
static bool intakeTargetUpdate = false;

//motors
Motor intake1(INTAKE, MOTOR_GEARSET_36, 1, MOTOR_ENCODER_DEGREES);

//line sensors
ADILineSensor line_L('F');
ADILineSensor line_R('E');
ADILineSensor line_I('H');


/**************************************************/
//basic control
void intake(int vel){
  intake1.move_velocity(vel);
  intake1.set_brake_mode(MOTOR_BRAKE_BRAKE);
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
  if(line_I.get_value() < 1800 && line_I.get_value() != 0)
    return true;
  else
    return false;
}

/**************************************************/
//autonomous control
void intakeBallAsync(){
  intakeTarget = 1;
  intakeTargetUpdate = true;
}

void loadBallAsync(){
  intakeTarget = 2;
  intakeTargetUpdate = true;
}

void loadAndClearAsync(){
  intakeTarget = 3;
  intakeTargetUpdate = true;
}

void indexBallAsync(){
  intakeTarget = 4;
  intakeTargetUpdate = true;
}

void unindexBallAsync(){
  intakeTarget = 5;
  intakeTargetUpdate = true;
}

void intakeBall(){
  intake(127);
  while(!hasBall() && !intakeTargetUpdate) delay(20);
  intake(0);
}

void loadBall(){
  intake(127);
  while(!isLoaded() && !intakeTargetUpdate) delay(20);
  intake(0);
}

void loadAndClear(){
  loadBall();
  if(!intakeTargetUpdate)
    intake(-127);
}

void indexBall(){
  loadBall();
  intake(127);
  delay(1500);
  adjust();
}

void unindexBall(){
  intake(-40);
  adjust();
  while(!hasBall() && !intakeTargetUpdate) delay(20);
  intake(0);
}

/**************************************************/
//task control
void intakeTask(void* parameter){
  while(1){
    delay(20);
    intakeTargetUpdate = false;

    switch(intakeTarget){
      case 1:
        intakeBall();
        break;
      case 2:
        loadBall();
        break;
      case 3:
        loadAndClear();
        break;
      case 4:
        indexBall();
        break;
      case 5:
        unindexBall();
        break;
    }

    intakeTarget = 0;
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
    vel = -60;
  else
    vel = 0;
}
