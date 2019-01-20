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
    drive(.24 TL);

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
  turn(13);
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
void backSquare(){
  //cap throw
  driveAsync(-1.9 TL);
  while(drivePos() > -1.7 TL) delay(20);
  setLiftAsync(200);
  while(isDriving()) delay(20);
  turn(-135);
  delay(500);


  //retract lift
  lift(-127);
  delay(800);
  lift(0);

  //align with wall
  turn(-35);
  drive(-1.2 TL);
  turn(90);
  drive(-.6 TL);

  //align with cap
  drive(1.1 TL);
  turn(-90);

  //intake ball under the cap
  intakeBallAsync();
  drive(1 TL);

  //align for park
  drive(-.3 TL);
  turn(90);
  drive(.8 TL);

  //alliance park
  driveAsync(1.6 TL);
  while(drivePos() < .9 TL) delay(20);
  drive(-1);
}


/*********************************************************/
void delayShotBack(){
  //intake ball under the nearest cap
  intakeBallAsync();
  drive(1.9 TL);

  //back up against wall
  drive(-2 TL);

  //align with flags
  drive(.2 TL);
  turn(87);
  drive(2.05 TL);
  turn(-90);
  drive(-.5 TL);
  drive(.22 TL);
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
  turn(13);
  loadBallAsync();
  driveAsync(2.3 TL);
  while(drivePos() < 1.7 TL) delay(20);
  setSpeed(40);
  while(isDriving()) delay(20);

  //align for park
  drive(-3 TL);
  turn(-90);

  //alliance park
  intake(127);
  driveAsync(2.9 TL);
  while(drivePos() < 2.4 TL) delay(20);
  setSpeed(20);
  while(isDriving()) delay(20);
  driveAsync(.4 TL);
  setSpeed(40);
  while(isDriving()) delay(20);
}


/*********************************************************/
void skills(){
  //intake ball and flip cap
  intake(-80);
  driveAsync(2.4 TL);
  while(drivePos() < 2.2 TL) delay(20);
  intakeBallAsync();

  //back up against wall
  drive(-2.5 TL);

  //align with flags
  drive(.2 TL);
  turn(87);
  drive(2.05 TL);
  turn(-90);
  drive(-.5 TL);
  drive(.22 TL);
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
  turn(13);
  loadBallAsync();
  driveAsync(2.3 TL);
  while(drivePos() < 1.7 TL) delay(20);
  setSpeed(40);
  while(isDriving()) delay(20);


  // second flag column =============================

  //backup to align with next cap
  drive(-2.03 TL);
  intake(-127);
  delay(800);
  turn(-90);
  drive(-.5 TL);

  //intake ball and flip cap
  intake(-80);
  driveAsync(2.4 TL);
  while(drivePos() < 2.2 TL) delay(20);
  intakeBallAsync();

  //align with flags
  drive(-.24 TL);
  turn(79);

  //shoot both flags
  shoot();
  ratchetAsync();
  intake(127);
  adjust();
  while(!isLoaded()) delay(20);
  shoot();
  ratchetAsync();

  //toggle the low flag
  turn(12);
  loadBallAsync();
  drive(2.3 TL);

  // third column low flag ============================

  //align with cap
  drive(-1.15 TL);
  turn(88);

  //flip cap
  intake(-80);
  driveAsync(1.25 TL);
  setSpeed(60);
  while(isDriving()) delay(20);

  //flip next cap
  drive(-.3 TL);
  turn(176);
  intake(-60);
  driveAsync(3.1 TL);
  while(drivePos() < 1.5 TL) delay(20);
  setSpeed(80);
  while(drivePos() < 1.9 TL) delay(20);
  setSpeed(60);
  while(isDriving()) delay(20);

  //low flag
  drive(-.2 TL);
  intake(127);
  turn(90);
  driveAsync(1.6 TL);
  while(drivePos() < .5 TL) delay(20);
  setSpeed(60);
  while(isDriving()) delay(20);

  // last flag and park ============================

  //shoot flag
  adjustAsync();
  drive(-2 TL);
  turn(-19);
  shoot();

  //align against the wall
  turn(-81);
  intake(-127);
  drive(1.4 TL);

  //align for park
  drive(-.7 TL);
  turn(-90);
  drive(1.14 TL);
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
  driveAsync(1.6 TL);
  while(drivePos() < .85 TL) delay(20);
  drive(-1);
  delay(3000);
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
    case 2:
      backSquare();
      break;
    case 3:
      delayShotBack();
      break;
  }

  drive_task.remove();
  turn_task.remove();
  adjust_task.remove();
  intake_task.remove();
  launcher_task.remove();
}
