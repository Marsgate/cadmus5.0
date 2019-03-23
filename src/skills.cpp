#include "main.h"


/*********************************************************/
void newSkills(){

  //cap 1
  intakeFlip();
  drive(-.6 TL);
  adjustAsync();

  //cap 2
  turn(-43);
  intake(-60);
  slowDrive(1.7 TL, .3 TL);

  //cap 3
  drive(-.5 TL);
  turn(-115);
  slowDrive(.7 TL);

  //wall align
  drive(-.3 TL);
  turn(-55);
  drive(2.3 TL);
  turn(30);
  drive(.7 TL);

  // first flag column =============================

  //back to front
  drive(-.3 TL);
  turn(-93);
  drive(2 TL);
  adjustAsync();
  intake(-20);
  turn(-93);
  intake(0);
  drive(-.6 TL);

  wallToFlag();
  lowFlag();

  // second flag column =============================

  //backup to align with next cap
  turn(2);
  drive(-2.06 TL);
  turn(-90);
  drive(-.5 TL);

  //cap 3
  intakeBallAsync();
  slowDrive(2.1 TL, 1 TL);

  //shoot both flags
  drive(-.25 TL);
  turn(75);
  doubleShot();

  //toggle the low flag
  turn(11);
  slowDrive(2.5 TL, 1.2 TL);

  // third column low flag ============================

  //cap 4
  drive(-1.2 TL);
  turn(89);
  intake(-60);
  slowDrive(1.1 TL);

  //cap 5
  intake(-40);
  drive(-.3 TL);
  turn(175);
  slowDrive(3 TL, 1 TL);

  //low flag
  drive(-.4 TL);
  turn(80);
  slowDrive(1.4 TL, .5 TL);

  // last flags ==========================================

  //align with cap 6
  turn(-6);
  drive(-2.05 TL);
  turn(92);

  //intake ball
  intakeBallAsync();
  slowDrive(.9 TL);

  //shoot flags
  drive(-.45 TL);
  turn(-115);
  doubleShot();

  //flip cap
  intake(-50);
  turn(108);
  slowDrive(1.6 TL);


  // park =================================================

  turn(-9);
  drive(-2.6 TL);
  turn(88);
  drive(1 TL);
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
