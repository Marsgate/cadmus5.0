#include "main.h"

static bool driveMode = true;
static int driveTarget = 0;
static int turnTarget = 0;
static int maxSpeed = 127;
static int slant = 0;
static int mirror;

Motor left1(1);
Motor left2(2);
Motor right1(9, 1);
Motor right2(10, 1);

/**************************************************/
//basic drive functions
void left(int vel){
  left1.move(vel);
  left2.move(vel);
}

void right(int vel){
  right1.move(vel);
  right2.move(vel);
}

void reset(){
  left1.tare_position();
  right1.tare_position();
}

/**************************************************/
//drive tasks
void driveTask(void* parameter){
  while(1){
    static int prevError = 0;

    if(!driveMode)
      return;

    int sp = driveTarget;

    double kp = .2;
    double kd = .5;

    //read sensors
    int ls = left1.get_position();
    int rs = right1.get_position();
    //int sv = (ls+rs)/2;
    int sv = ls;

    //speed
    int error = sp-sv;
    int derivative = error - prevError;
    prevError = error;
    int speed = error*kp + derivative*kd;

    if(speed > maxSpeed)
      speed = maxSpeed;
    if(speed < -maxSpeed)
      speed = -maxSpeed;

    //set motors
    left(speed - slant);
    right(speed + slant);

    printf("sensor value: %d\n", sv);

    delay(20);
  }
}

void turnTask(void* parameter){
  while(1){
    if(driveMode)
      return;

    static int prevError;

    int sp = turnTarget;

    if(mirror)
      sp = -sp; // inverted turn speed for blue auton

    //int ab = abs(sp); //absolute setpoint
    double kp = 1.3;
    double kd = 6;

    int sv = (right1.get_position() + left1.get_position())/6.2;
    int error = sp-sv;
    int derivative = error - prevError;
    prevError = error;
    int speed = error*kp + derivative*kd;

    left(-speed);
    right(speed);

    delay(20);
  }
}


/**************************************************/
//drive settle check
bool isDriving(){
  static int count = 0;
  static int last = 0;
  static int lastTarget = 0;

  int curr = left1.get_position();
  int thresh = 1;
  int target = turnTarget;

  if(driveMode)
    target = driveTarget;


  if(abs(last-curr) < thresh)
    count++;
  else
    count = 0;

  if(target != lastTarget)
    count = 0;

  lastTarget = target;
  last = curr;

  //not driving if we haven't moved
  if(count > 4){
    return false;
  }
  else
    return true;

}

/**************************************************/
//autonomous functions
void startDrive(int sp){
  maxSpeed = 127;
  slant = 0;
  reset();
  driveTarget = sp;
  driveMode = true;
}

void startTurn(int sp){
  reset();
  turnTarget = sp;
  driveMode = false;
}

void autoDrive(int sp){
  startDrive(sp);
  while(isDriving()) delay(20);
}

void autoTurn(int sp){
  startTurn(sp);
  while(isDriving()) delay(20);
}

void setSpeed(int speed){
  maxSpeed = speed;
}

void setSlant(int s){
  if(mirror)
    s = -s;
  slant = s;
}

/**************************************************/
//operator control
void driveOp(){
  int lJoy = master.get_analog(ANALOG_LEFT_Y);
  int rJoy = master.get_analog(ANALOG_RIGHT_Y);
  left(lJoy);
  right(rJoy);
}
