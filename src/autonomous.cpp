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
  driveAsync(1.5 TL);
  while(drivePos() < .45 TL) delay(20);
  setSpeed(50);
  while(drivePos() < .9 TL) delay(20);
  setSpeed(80);
  while(isDriving()) delay(20);
  intake(0);

  //shoot flags in the center
  drive(-.3 TL);
  if(highFlag)
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


  //park
  drive(-.22 TL);
  turn(90);
  drive(.5 TL);
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


/*********************************************************/
void skills(){
  //first shot
  shoot();
  ratchetAsync();
  turn(-93);
  drive(-.5 TL);

  // cap 1
  intakeFlip();
  loadBall();

  // cap 2
  drive(-.4 TL);
  turn(-42);
  intake(-60);
  driveAsync(1.5 TL);
  while(drivePos() < .6 TL) delay(20);
  setSpeed(30);
  while(isDriving()) delay(20);

  // cap 3
  turn(115);
  drive(-.8 TL);
  drive(.3 TL);
  turn(90);
  driveAsync(1.2 TL);
  setSpeed(60);
  while(isDriving()) delay(20);

  // align with wall
  turn(-90);
  drive(-.5 TL);
  drive(1.2 TL);
  turn(95);
  intake(-30);
  driveAsync(2.4 TL);
  while(drivePos() < 1 TL);
  setSpeed(60);
  while(drivePos() < 1.5 TL);
  setSpeed(30);
  while(isDriving()) delay(20);

  // first flag column =============================

  //align with flags
  drive(-.25 TL);
  turn(-92);
  drive(2 TL);
  turn(-90);
  drive(-.5 TL);

  //score first flag column

  adjustAsync();
  drive(.22 TL);
  turn(85);
  shoot();
  ratchetAsync();
  lowFlag();

  // second flag column =============================

  //backup to align with next cap
  loadAndClearAsync();
  drive(-2 TL);
  turn(-90);
  drive(-.5 TL);

  //cap 2
  intakeFlip();

  //shoot both flags
  drive(-.3 TL);
  turn(81);
  doubleShot();

  //toggle the low flag
  turn(17);
  loadAndClearAsync();
  drive(2.3 TL);

  // third column low flag ============================

  //cap 3
  drive(-1.15 TL);
  turn(88);
  intake(-80);
  driveAsync(1.25 TL);
  setSpeed(60);
  while(isDriving()) delay(20);

  //cap 4
  drive(-.3 TL);
  turn(173);
  intake(-60);
  driveAsync(3.1 TL);
  while(drivePos() < 1.5 TL) delay(20);
  setSpeed(80);
  while(drivePos() < 1.9 TL) delay(20);
  setSpeed(60);
  while(isDriving()) delay(20);

  //low flag
  drive(-.27 TL);
  intake(127);
  turn(90);
  driveAsync(1.6 TL);
  while(drivePos() < .5 TL) delay(20);
  setSpeed(60);
  while(isDriving()) delay(20);

  // last flags and park ============================

  //shoot flag
  adjustAsync();
  drive(-2 TL);
  turn(-20);
  shoot();

  //align against the wall
  turn(-80);
  intake(-127);
  drive(1.4 TL);

  //align for park
  drive(-.7 TL);
  turn(-90);
  drive(1.0 TL);
  turn(-90);
  drive(.4 TL);

  //alliance park
  intake(127);
  driveAsync(1.9 TL);
  while(drivePos() < 1.4 TL) delay(20);
  setSpeed(20);
  while(isDriving()) delay(20);
  driveAsync(.4 TL);
  setSpeed(40);
  while(isDriving()) delay(20);

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
      bigBoi();
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
  }

  drive_task.remove();
  turn_task.remove();
  adjust_task.remove();
  intake_task.remove();
  launcher_task.remove();

  reset(); // make sure no motors are moving
}
