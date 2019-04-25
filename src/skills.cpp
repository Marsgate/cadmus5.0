#include "main.h"


/*********************************************************/
void newSkills(){
  //cap 1
  intakeFlip();
  drive(-.5 TL);
  adjustAsync();

  //cap 2
  turn(-42);
  intake(-60);
  slowDrive(1.7 TL, .3 TL);

  //cap 3
  drive(-.45 TL);
  turn(-117);
  slowDrive(.7 TL);

  //wall align
  drive(-.3 TL);
  turn(-57);
  drive(2.5 TL);
  turn(28);
  drive(.6 TL);

  // first flag column =============================

  //back to front
  drive(-.3 TL);
  turn(-94);
  drive(1.95 TL);
  unindexBallAsync();
  turn(-93);
  drive(-.6 TL);

  wallToFlag();
  lowFlag();

  // second flag column =============================

  //backup to align with next cap
  drive(-2.05 TL);
  turn(-92);
  drive(-.5 TL);

  //cap 4
  intakeBallAsync();
  delay(20);
  intake(127);
  slowDrive(2.1 TL, .5 TL);

  //shoot both flags
  drive(-.37 TL);
  turn(79);
  doubleShot();

  //toggle the low flag
  turn(11);
  slowDrive(2.7 TL, 1.2 TL);

  // third column low flag ============================

  //cap 5
  drive(-1.3 TL);
  turn(90);
  intake(-40);
  slowDrive(1.1 TL);

  //cap 6
  drive(-.3 TL);
  turn(178);
  slowDrive(3 TL, 1 TL);

  //low flag
  drive(-.45 TL);
  turn(80);
  if(!isLoaded()){
    intake(127);
  }
  slowDrive(1.5 TL, .5 TL);
  turn(5);

  // last flags ==========================================

  //align with cap 7
  drive(-2.15 TL);
  turn(92);

  //intake ball
  intakeBallAsync();
  slowDrive(.9 TL);

  //shoot flags
  drive(-.4 TL);
  turn(-113);
  doubleShot();

  //flip caps
  intake(-60);
  turn(108);
  slowDrive(1.5 TL, .3 TL);


  // park =================================================
  turn(7);
  drive(-2.7 TL);
  turn(88);
  drive(1.1 TL);
  turn(-93);
  drive(.6 TL);

  //alliance park
  alliancePark();

  //center park
  park();
}









// ======================================================================================================
// ======================================================================================================
// ======================================================================================================
// ======================================================================================================







//only the stacking portion of skills. use the rest of the regular skills run to finish this
/*********************************************************/
void stackSkills(){
  /*
  //cap 1
  intakeFlip();

  //lift cap 2
  drive(-.3 TL);
  turn(88);
  drive(-.6 TL);
  liftFast(100);
  delay(700);
  drive(-.6 TL);

  //align with post
  drive(.85 TL);
  turn(95);

  //align to stack cap
  liftSlow(110);
  slowDrive(2.2 TL, 1 TL);
  liftSlow(187);
  drive(-.1 TL);
  delay(400);

  //reset cap stacker
  drive(-.5 TL);
  liftFast(2);
  delay(800);

  // first flag column =============================

  //back to front
  ratchetAsync();
  turn(-90);
  loadBallAsync();
  drive(2.8 TL);
  turn(-94);
  drive(-.5 TL);
  wallToFlag();
  lowFlag();
  */
}
