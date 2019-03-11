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
  intake(0);
  ratchet();
}


/*********************************************************/
void biggieCheese(){
  backCap();

  //intake ball under the nearest cap
  intakeBallAsync();
  drive(1.95 TL);

  //align with platform
  drive(-.13 TL);
  turn(89);
  drive(.6 TL);

  //shoot far flags
  drive(-.32 TL);
  turn(-46);
  doubleShot();

  //park
  turn(47);
  drive(.55 TL);
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
  backCap();

  // cap 2
  intakeFlip();
  turn(-4);
  slowDrive(-2.5 TL, -1.3 TL);

  // first flag column =============================

  backToFront();
  wallToFlag();
  lowFlag();

  // second flag column =============================

  //backup to align with next cap
  turn(2);
  drive(-2.0 TL);
  turn(-90);
  drive(-.5 TL);

  //cap 3
  intakeBallAsync();
  slowDrive(2.1 TL, 1 TL);

  //shoot both flags
  drive(-.26 TL);
  turn(75);
  doubleShot();

  //toggle the low flag
  turn(9);
  slowDrive(2.5 TL, 1.2 TL);

  // third column low flag ============================

  //cap 4
  drive(-1.2 TL);
  turn(89);
  intake(-40);
  slowDrive(1.2 TL);

  //cap 5
  drive(-.3 TL);
  turn(177);
  slowDrive(3 TL, 1 TL);

  //low flag
  drive(-.4 TL);
  turn(80);
  slowDrive(1.4 TL, .5 TL);

  // last flags ==========================================

  //align with cap 6
  turn(-7);
  drive(-2 TL);
  turn(92);

  //intake ball
  intakeBallAsync();
  slowDrive(.9 TL);

  //shoot flags
  drive(-1.05 TL);
  turn(-100);
  doubleShot();


  // park =================================================

  //align against the wall
  turn(-93);
  intake(-127);
  slowDrive(1.4 TL, 1 TL);

  //align for park
  drive(-.8 TL);
  turn(-92);
  drive(1.2 TL);
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
      bigBoi();
      break;
    case 1:
      skills();
      break;
    case 2:
      biggieCheese();
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
