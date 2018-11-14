#include "main.h"

//definition of a tile in encoder ticks
#define TL *644

//jumpers
ADIDigitalIn auton('G');

static int park = false;

void close(){
  //launch the ball
  shoot();
  ratchetAsync();

  //toggle the low flag
  turn(6);
  loadBallAsync();
  drive(2.3 TL);

  //backup to align with next cap
  drive(-1.3 TL);

  //line up with the wall
  turn(-90);
  drive(-.4 TL);

  //flip next cap
  intake(-80);
  driveAsync(1.5 TL);
  while(drivePos() < .3 TL) delay(20);
  setSpeed(40);
  while(drivePos() < .6 TL) delay(20);
  setSpeed(70);
  while(isDriving()) delay(20);
  intake(0);

  // if auto is not a parking auton, exit
  if(!park)
    return;

  //align with platform
  turn(-80);
  drive(1.5 TL);

  //alliance park
  driveAsync(2 TL);
  while(drivePos() < .9 TL) delay(20);
  drive(-1);
}

void far(){
  //launch the ball
  shoot();
  ratchetAsync();

  //align with wall
  drive(-1.3 TL);

  //face cap
  drive(.25 TL);
  turn(-90);

  //align against the wall
  drive(-.5 TL);

  //flip cap
  intake(-127);
  driveAsync(3.4 TL);
  while(drivePos() < .9 TL) delay(20);
  setSpeed(60);
  while(drivePos() < 2.1 TL) delay(20);
  intake(0);
  while(drivePos() < 2.3 TL) delay(20);

  //face platform
  drive(-.6 TL);
  intake(0);
  turn(84);

  //drive to platform
  drive(1.4 TL);

  // if auto is not a parking auton, exit
  if(!park)
    return;

  //alliance park
  driveAsync(2 TL);
  while(drivePos() < .9 TL) delay(20);
  drive(-1);
}

void doubleShot(){
  //back up against wall
  drive(-2.1 TL);
  setSpeed(60);
  while(drivePos() > -.2 TL) delay(20);
  setSpeed(127);
  while(isDriving()) delay(20);

  //align with flags
  drive(.35 TL);
  turn(89);

  //launch the balls
  shoot();
  intake(127);
  adjust();
}

void bigBoi(){
  //flip the nearest cap
  intake(127);
  driveAsync(3 TL);
  while(drivePos() < 1.5 TL) delay(20);
  setSpeed(60);
  intakeBallAsync();
  while(drivePos() < 1.9 TL) delay(20);

  doubleShot();

  close();

  //align with flags in the center
  adjustAsync();
  turn(45);
  shootAsync();
  driveAsync(1.8 TL);
  setSlant(40);
  delay(1500);
}

void skills(){
  //flip the nearest cap
  intake(-60);
  driveAsync(3 TL);
  while(drivePos() < 1.5 TL) delay(20);
  setSpeed(60);
  while(drivePos() < 1.9 TL) delay(20);
  intakeBallAsync();
  while(drivePos() < 2.2 TL) delay(20);
  driveAsync(-1 TL);
  while(drivePos() > -.5 TL) delay(20);


  doubleShot();

  close();

  //align against wall
  drive(-1.6 TL);
  drive(.4 TL);

  //align for park
  turn(-90);
  drive(2.15 TL);
  turn(90);
  drive(.7 TL);

  //alliance park
  driveAsync(2 TL);
  while(drivePos() < .9 TL) delay(20);
  drive(-1);

  //center park
  drive(.3 TL);
  driveAsync(2 TL);
  while(drivePos() < .9 TL) delay(20);
  drive(-1);
}

void autonomous() {
  if(auton.get_value()){
    bigBoi();
  }else{
    skills();
  }
}
