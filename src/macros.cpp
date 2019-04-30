#include "main.h"

void doubleShot(){
  shoot();
  ratchetAsync();
  intake(127);
  adjust();
  while(!isLoaded()){
    static int count = 0;
    count++;
    if(count > 40)
      break;
    delay(20);
  }
  delay(70);
  shoot();
  ratchetAsync();
}

void park(){
  driveAsync(1.6 TL);
  while(drivePos() < 1.07 TL) delay(20);
  drive(-1);
  reset();
}

void alliancePark(){
  intake(127);
  driveAsync(2 TL);
  while(drivePos() < 1.1 TL) delay(20);
  setSpeed(40);
  while(isDriving()) delay(20);
}

void backToFront(){
  drive(.2 TL);
  turn(86);
  drive(1.91 TL);
  turn(-93);
  drive(-.5 TL);
}

void wallToFlag(){
  drive(.2 TL);
  turn(87);
  doubleShot();
}

void lowFlag(){
  turn(13);
  loadAndClearAsync();
  slowDrive(2.4 TL, 1.5 TL);
  turn(5);
}

void lowFlagIndex(){
  turn(13);
  indexBallAsync();
  slowDrive(2.4 TL, 1.5 TL);
  turn(5);
}

void intakeFlip(){
  intake(-45);
  driveAsync(2.45 TL);
  while(drivePos() < 1 TL) delay(20);
  setSpeed(60);
  while(drivePos() < 1.75 TL) delay(20);
  intake(127);
  while(drivePos() < 2.1 TL) delay(20);
}

void backCap(){
  //back cap
  intake(-50);
  slowDrive(2.2 TL, .6 TL);

  //align with wall
  drive(-1.8 TL);
  turn(32);
  drive(-.6 TL);
}
