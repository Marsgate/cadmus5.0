#include "main.h"

bool highFlag;

/*********************************************************/
void bigBoi(){
  //intake ball under the nearest cap
  intakeBallAsync();
  drive(1.9 TL);

  //back up against wall
  drive(-2 TL);

  //toggle flag column
  wallToFlag();
  lowFlag();

  //backup to align with next cap
  drive(-1.1 TL);

  //line up with the wall
  turn(-90);
  drive(-.5 TL);

  //flip next cap
  intake(-60);
  slowDrive(1.6 TL, .4 TL);
  intake(0);

  //shoot flags in the center
  drive(-.3 TL);
  if(!highFlag)
    adjustAsync();
  turn(52);
  shoot();

  //low flag
  driveAsync(1.6 TL);
  while(drivePos() < .5 TL) delay(20);
  setSlant(40);
  delay(300);
  setSlant(0);
  ratchet();
}


/*********************************************************/
void backSquare(){
  //intake ball under the nearest cap
  intakeBallAsync();
  drive(1.9 TL);

  //align with platform
  drive(-.22 TL);
  turn(90);
  drive(.5 TL);

  //shoot flags
  drive(-.5 TL);
  turn(-22);
  doubleShot();

  //align with wall
  turn(10);
  slowDrive(-1.5 TL, -.4 TL);

  //flip cap
  drive(.17 TL);
  turn(-93);
  intake(-80);
  drive(.9 TL);

  //align with wall
  drive(-.6 TL);
  turn(92);
  drive(-.32 TL);

  //align with platform
  intake(127);
  drive(1.6 TL);
  park();
}


/*********************************************************/
void zaccAttack(){
  //intake ball under the nearest cap
  intakeBallAsync();
  drive(1.9 TL);

  //back up against wall
  drive(-1.9 TL);

  delay(1000);

  //align and shoot flags
  backToFront();
  wallToFlag();

  //park
  drive(-1 TL);
  turn(-90);
  alliancePark();
}

void biggieCheese(){
  backCap();

  //intake ball under the nearest cap
  intakeBallAsync();
  drive(1.9 TL);

  //align with platform
  drive(-.21 TL);
  turn(90);
  drive(.6 TL);

  //shoot far flag
  drive(-.5 TL);
  turn(-44);
  shoot();
  ratchetAsync();
  loadBallAsync();

  //shoot mid flag
  turn(44);
  drive(.5 TL);
  drive(-.5 TL);
  turn(-22);
  shoot();
  ratchetAsync();

  //park
  turn(22);
  drive(.5 TL);
  park();
}

/*********************************************************/
void skills(){
  backCap();

  // cap 2
  intakeFlip();
  turn(-8);
  slowDrive(-2.5 TL, -1.3 TL);

  // first flag column =============================

  backToFront();
  wallToFlag();
  lowFlag();

  // second flag column =============================

  //backup to align with next cap
  loadAndClearAsync();
  drive(-1.95 TL);
  turn(-90);
  drive(-.5 TL);

  //cap 3
  intakeBallAsync();
  slowDrive(1.9 TL, 1 TL);

  //shoot both flags
  drive(-.2 TL);
  turn(72);
  doubleShot();

  //toggle the low flag
  drive(1.6 TL);
  turn(27);
  loadAndClearAsync();
  slowDrive(1 TL, .3 TL);

  // third column low flag ============================

  //cap 4
  drive(-1.2 TL);
  turn(89);
  intake(-60);
  slowDrive(1 TL);

  //cap 5
  drive(-.3 TL);
  turn(171);
  intake(-60);
  drive(2.1 TL);
  turn(38);
  slowDrive(.8 TL);

  //low flag
  intake(0);
  drive(-.2 TL);
  turn(64);
  slowDrive(1.7 TL, .5 TL);

  // last flags ==========================================

  //align with cap 6
  turn(-8);
  drive(-2.1 TL);
  turn(90);
  slowDrive(-1.7 TL, -.5 TL);

  //intake ball
  intakeBallAsync();
  drive(1 TL);

  //shoot flags
  drive(-.5 TL);
  turn(-97);
  doubleShot();

  // park =================================================

  //align against the wall
  turn(-93);
  intake(-127);
  slowDrive(1.4 TL, .4 TL);

  //align for park
  drive(-.8 TL);
  turn(-92);
  drive(1 TL);
  turn(-95);
  slowDrive(.6 TL);

  //alliance park
  alliancePark();

  //center park
  park();
}

void autonomous() {
  highFlag = false;
  reset(); // reset the drive encoders

  Task drive_task(driveTask);
  Task turn_task(turnTask);
  Task adjust_task(adjustTask);
  Task intake_task(intakeTask);
  Task launcher_task(launcherTask);

  switch(auton){
    case 0:
      drive(-1 TL);
      //bigBoi();
      break;
    case 1:
      skills();
      break;
    case 2:
      backSquare();
      break;
    case 3:
      zaccAttack();
      break;
    case 4:
      highFlag = true;
      bigBoi();
      break;
    case 5:
      biggieCheese();
      break;
  }

  drive_task.remove();
  turn_task.remove();
  adjust_task.remove();
  intake_task.remove();
  launcher_task.remove();

  reset(); // make sure no motors are moving
}
