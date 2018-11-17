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
  turn(4);
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
  drive(-2.3 TL);
  setSpeed(60);
  while(drivePos() > -.2 TL) delay(20);
  setSpeed(127);
  while(drivePos() > -2.1 TL) delay(20);


  //align with flags
  drive(.25 TL);
  turn(84);

  //launch the balls
  shoot();
  ratchetAsync();
  intake(127);
  adjust();
  while(!isLoaded()) delay(20);
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

  drive(-.3 TL);


  //align with flags in the center
  adjustAsync();
  turn(34);

  //drive and shoot
  driveAsync(2 TL);
  setSlant(45);
  delay(100);
  shootAsync();
  delay(500);
  setSlant(0);
  delay(1000);
  reset();
}

void skills(){
  //flip the nearest cap
  intake(-60);
  driveAsync(3 TL);
  while(drivePos() < 1.7 TL) delay(20);
  setSpeed(60);
  while(drivePos() < 1.9 TL) delay(20);
  intakeBallAsync();
  while(drivePos() < 2.2 TL) delay(20);
  driveAsync(-1 TL);
  while(drivePos() > -.3 TL) delay(20);


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
  reset(); // reset the drive encoders

  Task drive_task(driveTask);
  Task turn_task(turnTask);
  Task adjust_task(adjustTask);
  Task intake_task(intakeTask);
  Task launcher_task(launcherTask);

  if(auton.get_value()){
    bigBoi();
  }else{
    skills();
  }

  drive_task.remove();
  turn_task.remove();
  adjust_task.remove();
  intake_task.remove();
  launcher_task.remove();
}
