#include "main.h"

//definition of a tile in encoder ticks
#define TL *680

//jumpers
ADIDigitalIn auton('B');

static int park = false;

void close(){
  //launch the ball
  shoot();
  ratchetAsync();

  //toggle the low flag
  loadBallAsync();
  drive(2.3 TL);

  //backup to align with next cap
  drive(-1 TL);

  //line up with the wall
  turn(-90);
  drive(-.4 TL);

  //flip next cap
  intake(-80);
  driveAsync(1.6 TL);
  while(drivePos() < .5 TL) delay(20);
  setSpeed(60);
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
  //needs reprogrammed
}

void bigBoi(){
  //intake ball under the nearest cap
  intake(127);
  driveAsync(3 TL);
  while(drivePos() < 1.5 TL) delay(20);
  setSpeed(60);
  intakeBallAsync();
  while(drivePos() < 1.9 TL) delay(20);

  //back up against wall
  drive(-2 TL);
  setSpeed(60);
  while(drivePos() > -.2 TL) delay(20);
  setSpeed(127);
  while(drivePos() > -1.6 TL) delay(20);
  setSpeed(60);
  while(isDriving()) delay(20);

  //align with flags
  drive(.3 TL);
  turn(90);

  //launch the balls
  shoot();
  ratchetAsync();
  intake(127);
  adjust();
  while(!isLoaded()) delay(20);

  close();

  drive(-.3 TL);

  //align with flags in the center
  adjustAsync();
  turn(34);

  //drive and shoot
  driveAsync(2 TL);
  setSlant(40);
  delay(250);
  shootAsync();
  delay(700);
  ratchetAsync();
  setSlant(0);
  delay(800);
  reset();
}

void skills(){
  //intake ball and flip cap
  intake(-60);
  driveAsync(2.5 TL);
  while(drivePos() < 1.7 TL) delay(20);
  setSpeed(60);
  while(drivePos() < 1.9 TL) delay(20);
  setSpeed(40);
  intakeBallAsync();
  while(drivePos() < 2.2 TL) delay(20);
  reset();
  driveAsync(-1 TL);
  while(drivePos() > -.3 TL) delay(20);

  //back up against wall
  drive(-2 TL);
  setSpeed(60);
  while(drivePos() > -.2 TL) delay(20);
  setSpeed(127);
  while(drivePos() > -1.6 TL) delay(20);
  setSpeed(60);
  while(isDriving()) delay(20);

  //align with flags
  drive(.3 TL);
  turn(87);
  drive(2 TL);
  turn(-90);
  drive(-.5 TL);
  drive(.35 TL);
  turn(90);

  //shoot both flags
  shoot();
  ratchetAsync();
  intake(127);
  adjust();
  while(!isLoaded()) delay(20);
  shoot();
  ratchetAsync();

  //toggle the low flag
  loadBallAsync();
  drive(2.3 TL);

  //backup to align with next cap
  drive(-2 TL);
  intake(-127);
  delay(1000);
  turn(-90);
  drive(-.5 TL);

  //intake ball and flip cap
  intake(-60);
  driveAsync(3 TL);
  while(drivePos() < 1.7 TL) delay(20);
  setSpeed(60);
  while(drivePos() < 2 TL) delay(20);
  intakeBallAsync();
  while(drivePos() < 2.1 TL) delay(20);
  driveAsync(-.1 TL);
  while(isDriving()) delay(20);

  //align with flags
  turn(85);

  //shoot both flags
  shoot();
  ratchetAsync();
  intake(127);
  adjust();
  while(!isLoaded()) delay(20);
  shoot();
  ratchetAsync();

  //toggle the low flag
  turn(6);
  loadBallAsync();
  drive(2.3 TL);

  //align with last cap
  drive(-1 TL);
  turn(90);

  //flip cap
  intake(-80);
  driveAsync(1.6 TL);
  while(drivePos() < .3 TL) delay(20);
  setSpeed(60);
  while(isDriving()) delay(20);
  intake(0);

  //line up for last flag
  drive(-1.1 TL);
  turn(-90);
  drive(-1.5 TL);
  drive(.3 TL);
  adjustAsync();
  turn(-54);

  //shoot flag
  shoot();
  ratchetAsync();

  //line up for park
  turn(54);
  drive(-.5 TL);
  drive(.3 TL);
  turn(90);
  intake(127);
  drive(1.8 TL);
  drive(-.3 TL);
  turn(90);
  drive(1 TL);
  turn(90);
  drive(-.5 TL);
  drive(1.1 TL);

  /*
  //line up for parking
  drive(-.1 TL);
  turn(65);
  drive(2.1 TL);
  turn(110);
  drive(-.8 TL);
  drive(1.1 TL);*/

  //alliance park
  driveAsync(1.5 TL);
  while(isDriving()) delay(20);

  //center park
  driveAsync(1.6 TL);
  while(drivePos() < .8 TL) delay(20);
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
