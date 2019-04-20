#include "main.h"

bool highFlag;

/*********************************************************/
void bigBoi(){
  adjustAsync(); //start at low angle

  //intake ball under the nearest cap
  intakeBallAsync();
  drive(1.9 TL);

  //back up against wall
  slowDrive(-2 TL, -.8 TL);

  //toggle flag column
  wallToFlag();
  lowFlagIndex();

  //backup to align with next cap
  drive(-1.2 TL);

  //line up with the wall
  turn(-90);
  drive(-.5 TL);

  //flip next cap
  intake(-100);
  slowDrive(1.5 TL, .2 TL);

  //shoot flags in the center
  unindexBallAsync();
  turn(60);
  drive(-.5 TL);
  doubleShot();
  drive(-.5 TL);
}


/*********************************************************/
void biggieCheese(){

  //intake ball under the nearest cap
  intake(127);
  drive(1.95 TL);
  delay(500);
  adjustAsync();

  //cap 2
  drive(-.2 TL);
  turn(-80);
  intake(-127);
  drive(.8 TL);
  unindexBallAsync();

  //align with platform
  drive(-.3 TL);
  turn(-180);
  drive(.7 TL);
  turn(-30);
  slowDrive(.5 TL);

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

void autonomous() {
  d = -1; //set angle adjuster starting height

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
      newSkills();
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
