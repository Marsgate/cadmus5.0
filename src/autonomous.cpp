#include "main.h"

//definition of a tile in encoder ticks
#define TL *545

ADIDigitalIn bypass('A');

/*********************************************************/
void bigBoi(){
  //intake ball under the nearest cap
  intakeBallAsync();
  drive(1.9 TL);

  //back up against wall
  drive(-2 TL);

  //align with flags
  if(!mirror)
    drive(.22 TL);
  else
    drive(.26 TL);
    
  turn(84);

  //launch the balls
  shoot();
  ratchetAsync();
  intake(127);
  adjust();
  while(!isLoaded()) delay(20);
  shoot();
  ratchetAsync();

  //toggle low flag
  turn(12);
  loadBallAsync();
  driveAsync(2.3 TL);
  while(drivePos() < 1.7 TL) delay(20);
  setSpeed(40);
  while(isDriving()) delay(20);

  //backup to align with next cap
  drive(-1.1 TL);

  //line up with the wall
  turn(-90);
  drive(-.5 TL);

  //flip next cap
  intake(-80);
  driveAsync(1.5 TL);
  while(drivePos() < .45 TL) delay(20);
  setSpeed(50);
  while(drivePos() < .9 TL) delay(20);
  setSpeed(80);
  while(isDriving()) delay(20);
  intake(0);

  drive(-.3 TL);

  //shoot flags in the center
  turn(50);
  shoot();

  driveAsync(1.8 TL);
  while(drivePos() < .9 TL) delay(20);
  setSlant(35);
  delay(400);
}



/*********************************************************/
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

  //align with flags
  drive(.3 TL);
  turn(87);
  drive(1.9 TL);
  turn(-90);
  drive(-.5 TL);
  drive(.25 TL);
  turn(88);

  //shoot both flags
  shoot();
  ratchetAsync();
  intake(127);
  adjust();
  while(!isLoaded()) delay(20);
  shoot();
  ratchetAsync();

  //toggle the low flag
  turn(3);
  loadBallAsync();
  driveAsync(2.2 TL);
  while(drivePos() < 1.8 TL) delay(20);
  setSpeed(40);
  while(isDriving() ) delay(20);

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
  while(drivePos() < 2.05 TL) delay(20);
  intakeBallAsync();
  while(drivePos() < 2.18 TL) delay(20);
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
  turn(-56);

  //shoot flag
  shoot();
  ratchetAsync();

  //line up for park
  turn(56);
  drive(-.5 TL);
  drive(.3 TL);
  turn(90);
  intake(127);
  drive(1.8 TL);
  drive(-.3 TL);
  turn(90);
  drive(1.2 TL);
  turn(90);
  drive(-.6 TL);
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

  if(!competition::is_connected() && bypass.get_value()){
    auton = -1;
    drive(-2 TL);
    turn(-90);
    turn(-90);
    drive(-2 TL);
  }

  switch(auton){
    case 0:
      bigBoi();
      break;
    case 1:
      skills();
      break;
  }

  drive_task.remove();
  turn_task.remove();
  adjust_task.remove();
  intake_task.remove();
  launcher_task.remove();
}
