#include "main.h"

#define MAX 127;

static bool driveMode = true;
static int driveTarget = 0;
static int turnTarget = 0;
static int maxSpeed = MAX;
static int slant = 0;


//motors
Motor left1(20, MOTOR_GEARSET_18, 0, MOTOR_ENCODER_DEGREES);
Motor left2(19, MOTOR_GEARSET_18, 0, MOTOR_ENCODER_DEGREES);
Motor right1(12, MOTOR_GEARSET_18, 1, MOTOR_ENCODER_DEGREES);
Motor right2(11, MOTOR_GEARSET_18, 1, MOTOR_ENCODER_DEGREES);

/**************************************************/
//basic control
void left(int vel){
  left1.move(vel);
  left2.move(vel);
}

void right(int vel){
  right1.move(vel);
  right2.move(vel);
}

void reset(){
  maxSpeed = MAX;
  slant = 0;
  driveTarget = 0;
  turnTarget = 0;
  left1.tare_position();
  left2.tare_position();
  right1.tare_position();
  right2.tare_position();
}

int drivePos(){
  return (left1.get_position() + right1.get_position())/2;
}

/**************************************************/
//slew control
const int accel_step = 8;
const int deccel_step = 256;

void leftSlew(int leftTarget){
  static int leftSpeed = 0;
  int step;

  if(abs(leftSpeed) < abs(leftTarget))
    step = accel_step;
  else
    step = deccel_step;

  if(leftTarget > leftSpeed + step)
    leftSpeed += step;
  else if(leftTarget < leftSpeed - step)
    leftSpeed -= step;
  else
    leftSpeed = leftTarget;

  //set motors
  left(leftSpeed);
}

//slew control
void rightSlew(int rightTarget){
  static int rightSpeed = 0;
  int step;

  if(abs(rightSpeed) < abs(rightTarget))
    step = accel_step;
  else
    step = deccel_step;

  if(rightTarget > rightSpeed + step)
    rightSpeed += step;
  else if(rightTarget < rightSpeed - step)
    rightSpeed -= step;
  else
    rightSpeed = rightTarget;

  //set motors
  right(rightSpeed);
}

/**************************************************/
//feedback
bool isDriving(){
  static int count = 0;
  static int last = 0;
  static int lastTarget = 0;

  int curr = right1.get_position();
  int thresh = 3;
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
  if(count > 10){
    return false;
  }
  else
    return true;

}

/**************************************************/
//autonomous functions
void driveAsync(int sp){
  reset();
  driveTarget = sp;
  driveMode = true;
}

void turnAsync(int sp){
  reset();
  turnTarget = sp;
  driveMode = false;
}

void drive(int sp){
  driveAsync(sp);
  while(isDriving()) delay(20);
}

void turn(int sp){
  turnAsync(sp);
  while(isDriving()) delay(20);
}

/**************************************************/
//drive modifiers
void setSpeed(int speed){
  maxSpeed = speed;
}

void setSlant(int s){
  if(!mirror.get_value())
    s = -s;

  if(s < 0)
    s += 5;

  slant = s;
}

/**************************************************/
//task control
void driveTask(void* parameter){
  int prevError = 0;

  while(1){
    delay(20);

    if(!driveMode)
      continue;

    int sp = driveTarget;

    double kp = .3;
    double kd = .5;

    //read sensors
    int ls = left1.get_position();
    int rs = right1.get_position();
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
    leftSlew(speed - slant);
    rightSlew(speed + slant);
  }
}

void turnTask(void* parameter){
  int prevError;

  while(1){
    delay(20);

    if(driveMode)
      continue;

    int sp = turnTarget;



    if(!mirror.get_value())
      sp = -sp; // inverted turn speed for blue auton


    if(sp > 0)
      sp *= 2.48;
    else
      sp *= 2.55;

    double kp = .9;
    double kd = 3.5;

    int sv = (right1.get_position() - left1.get_position())/2;
    int error = sp-sv;
    int derivative = error - prevError;
    prevError = error;
    int speed = error*kp + derivative*kd;

    if(speed > maxSpeed)
      speed = maxSpeed;
    if(speed < -maxSpeed)
      speed = -maxSpeed;

    leftSlew(-speed);
    rightSlew(speed);
    }
}

/**************************************************/
//operator control
void driveOp(){
  int lJoy = master.get_analog(ANALOG_LEFT_Y);
  int rJoy = master.get_analog(ANALOG_RIGHT_Y);
  left(rJoy);
  right(rJoy);
}
