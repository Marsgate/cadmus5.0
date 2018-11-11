#include "main.h"

//definition of a tile in encoder ticks
#define TL *644

//jumpers
ADIDigitalIn auton('G');

static int park = false;

void close(){
  //launch the ball
  launcher(127);
  while(!isFired()) delay(20);
  autoRatchet();
  intake(0);

  //toggle the low flag
  autoTurn(6);
  loadBall();
  autoDrive(2.3 TL);

  //backup to align with next cap
  autoDrive(-1.3 TL);

  //line up with the wall
  autoTurn(-90);
  autoDrive(-.4 TL);

  //flip next cap
  intake(-80);
  startDrive(1.5 TL);
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
  autoTurn(-80);
  autoDrive(1.5 TL);

  //alliance park
  startDrive(2 TL);
  while(drivePos() < .9 TL) delay(20);
  autoDrive(-1);
}

void far(){
  //launch the ball
  launcher(127);
  while(!isFired()) delay(20);
  autoRatchet();

  //align with wall
  autoDrive(-1.3 TL);

  //face cap
  autoDrive(.25 TL);
  autoTurn(-90);

  //align against the wall
  autoDrive(-.5 TL);

  //flip cap
  intake(-127);
  startDrive(3.4 TL);
  while(drivePos() < .9 TL) delay(20);
  setSpeed(60);
  while(drivePos() < 2.1 TL) delay(20);
  intake(0);
  while(drivePos() < 2.3 TL) delay(20);

  //face platform
  autoDrive(-.6 TL);
  intake(0);
  autoTurn(84);

  //drive to platform
  autoDrive(1.4 TL);

  // if auto is not a parking auton, exit
  if(!park)
    return;

  //alliance park
  startDrive(2 TL);
  while(drivePos() < .9 TL) delay(20);
  autoDrive(-1);
}

void doubleShot(){
  //back up against wall
  startDrive(-2.1 TL);
  printf("5");
  setSpeed(60);
  while(drivePos() > -.2 TL) delay(20);
  setSpeed(127);
  while(isDriving()) delay(20);

  //align with flags
  autoDrive(.35 TL);
  autoTurn(89);

  //launch the balls
  launcher(127);
  while(!isFired()) delay(20);
  intake(127);
  autoAdjust(1);
}

void bigBoi(){
  //flip the nearest cap
  intake(127);
  startDrive(3 TL);
  while(drivePos() < 1.5 TL) delay(20);
  printf("1");
  setSpeed(60);
  printf("2");
  intakeBall();
  printf("3");
  while(drivePos() < 1.9 TL) delay(20);
  printf("4");

  doubleShot();

  close();

  //align with flags in the center
  startAdjust(-1);
  autoTurn(45);
  autoShoot();
  startDrive(1.8 TL);
  setSlant(40);
  delay(1500);
}

void skills(){
  //flip the nearest cap
  intake(-60);
  startDrive(3 TL);
  while(drivePos() < 1.5 TL) delay(20);
  setSpeed(60);
  while(drivePos() < 1.9 TL) delay(20);
  intakeBall();
  while(drivePos() < 2.2 TL) delay(20);
  startDrive(-1 TL);
  while(drivePos() > -.5 TL) delay(20);


  doubleShot();

  close();

  //align against wall
  autoDrive(-1.6 TL);
  autoDrive(.4 TL);

  //align for park
  autoTurn(-90);
  autoDrive(2.15 TL);
  autoTurn(90);
  autoDrive(.7 TL);

  //alliance park
  startDrive(2 TL);
  while(drivePos() < .9 TL) delay(20);
  autoDrive(-1);

  //center park
  autoDrive(.3 TL);
  startDrive(2 TL);
  while(drivePos() < .9 TL) delay(20);
  autoDrive(-1);
}

void autonomous() {
  Task drive_task(driveTask);
  Task turn_task(turnTask);
  Task adjust_task(autoAdjustTask);
  Task intake_task(intakeTask);
  Task launcher_task(launcherTask);

  if(auton.get_value()){
    bigBoi();
  }else{
    //skills();
  }


  drive_task.remove();
  turn_task.remove();
  adjust_task.remove();
  intake_task.remove();
  launcher_task.remove();
}
