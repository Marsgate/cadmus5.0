#include "main.h"

#define MAX 127;

const double fc = 1; //friction coefficient

static int driveMode = 1;
static int driveTarget = 0;
static int turnTarget = 0;
static int maxSpeed = MAX;
static int slant = 0;



//motors
Motor left1(LEFTFRONT, MOTOR_GEARSET_18, 0, MOTOR_ENCODER_DEGREES);
Motor left2(LEFTREAR, MOTOR_GEARSET_18, 0, MOTOR_ENCODER_DEGREES);
Motor right1(RIGHTFRONT, MOTOR_GEARSET_18, 1, MOTOR_ENCODER_DEGREES);
Motor right2(RIGHTREAR, MOTOR_GEARSET_18, 1, MOTOR_ENCODER_DEGREES);

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
  left(0);
  right(0);
}

int drivePos(){
  return (left1.get_position() + right1.get_position())/2;
}

/**************************************************/
//slew control
const int accel_step = 9;
const int deccel_step = 256; // no decel slew
static int leftSpeed = 0;
static int rightSpeed = 0;

void leftSlew(int leftTarget){
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

  left(leftSpeed);
}

//slew control
void rightSlew(int rightTarget){
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

  right(rightSpeed);
}

/**************************************************/
//slop correction
void slop(int sp){
  driveMode = 2;
  if(sp < 0){
    right(-30);
    delay(100);
  }
  driveMode = 1;

}

/**************************************************/
//feedback
bool isDriving(){
  static int count = 0;
  static int last = 0;
  static int lastTarget = 0;

  int curr = left2.get_position();

  int target = turnTarget;
  if(driveMode == 1)
    target = driveTarget;

  if(abs(last-curr) < 3)
    count++;
  else
    count = 0;

  if(target != lastTarget)
    count = 0;

  lastTarget = target;
  last = curr;

  //not driving if we haven't moved
  if(count > 4)
    return false;
  else
    return true;

}

/**************************************************/
//autonomous functions
void driveAsync(int sp){
  reset();
  driveTarget = sp;
  driveMode = 1;
}

void turnAsync(int sp){
  if(mirror)
    sp = -sp; // inverted turn for blue auton
  reset();
  turnTarget = sp;
  driveMode = 0;
}

void drive(int sp){
  driveAsync(sp);
  delay(450);
  while(isDriving()) delay(20);
}

void turn(int sp){
  turnAsync(sp);
  delay(450);
  while(isDriving()) delay(20);
}

void slowDrive(int sp, int dp){
  driveAsync(sp);

  if(sp > 0)
    while(drivePos() < dp) delay(20);
  else
    while(drivePos() > dp) delay(20);

  setSpeed(60);
  while(isDriving()) delay(20);
}

/**************************************************/
//drive modifiers
void setSpeed(int speed){
  maxSpeed = speed;
}

void setSlant(int s){
  if(mirror)
    s = -s;

  slant = s;
}

void setCurrent(int mA){
  left1.set_current_limit(mA);
  left2.set_current_limit(mA);
  right1.set_current_limit(mA);
  right2.set_current_limit(mA);
}

void setBrakeMode(int mode){
  motor_brake_mode_e_t brakeMode;
  switch(mode){
    case 0:
      brakeMode = MOTOR_BRAKE_COAST;
      break;
    case 1:
      brakeMode = MOTOR_BRAKE_BRAKE;
      break;
    case 2:
      brakeMode = MOTOR_BRAKE_HOLD;
      break;
  }

  left1.set_brake_mode(brakeMode);
  left2.set_brake_mode(brakeMode);
  right1.set_brake_mode(brakeMode);
  right2.set_brake_mode(brakeMode);
}
/**************************************************/
//task control
void driveTask(void* parameter){
  int prevError = 0;

  while(1){
    delay(20);

    if(driveMode != 1)
      continue;

    int sp = driveTarget;

    double kp = .3;
    double kd = .5;

    //read sensors
    int sv = left2.get_position();

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

    if(driveMode != 0)
      continue;

    int sp = turnTarget;

    if(sp > 0)
      sp *= 2.35;
    else
      sp *= 2.3;

    double kp = .9*fc;
    double kd = 3.5/fc;

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
  setCurrent(2500);
  setBrakeMode(0);
  int lJoy = master.get_analog(ANALOG_LEFT_Y);
  int rJoy = master.get_analog(ANALOG_RIGHT_Y);
  left(lJoy);
  right(rJoy);
}
