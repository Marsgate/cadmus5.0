#include "main.h"

bool highFlag;

/*********************************************************/
void bigBoi(){
  adjustAsync(); //start at low angle

  //intake ball under the nearest cap
  intakeBallAsync();
  drive(1.9 TL);

  //back up against wall
  slowDrive(-2.1 TL, -1.2 TL);

  //toggle flag column
  wallToFlag();
  lowFlagIndex();

  //backup to align with next cap
  drive(-1.18 TL);

  //line up with the wall
  turn(-90);
  drive(-.6 TL);

  //flip next cap
  intake(-70);
  slowDrive(1.3 TL, .2 TL);
  intake(0);

  //shoot flags in the center
  unindexBallAsync();
  turn(57);
  drive(-.4 TL);
  doubleShot();
  // hi micah ur cool
}


/*********************************************************/
void biggieCheese(){

  //intake ball under the nearest cap
  intake(127);
  drive(1.95 TL);
  delay(500);
  adjustAsync();

  //cap 2
  drive(-1.5 TL);
  //turn(-35);
  turn(-38);
  intake(-127);
  slowDrive(1.9 TL, .4 TL);
  unindexBallAsync();

  //align with platform
  drive(-.8 TL);
  //turn(118);
  turn(122);
  slowDrive(1.2 TL, .4 TL);

  //shoot far flags
  drive(-.3 TL);
  //turn(-49);
  turn(-45);
  doubleShot();

  //park
  //turn(49);
  turn(45);
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
  }

  drive_task.remove();
  turn_task.remove();
  adjust_task.remove();
  intake_task.remove();
  launcher_task.remove();

  reset(); // make sure no motors are moving
}
