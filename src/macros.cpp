#include "main.h"

void doubleShot(){
  shoot();
  ratchetAsync();
  intake(127);
  adjust();
  while(!isLoaded()){
    static int count = 0;
    count++;
    if(count > 50)
      return;
    delay(20);
  }
  shoot();
  ratchetAsync();
}

void park(){
  driveAsync(1.6 TL);
  while(drivePos() < .89 TL) delay(20);
  drive(-1);
  reset();
}

void alliancePark(){
  intake(127);
  driveAsync(2.9 TL);
  while(drivePos() < 2.4 TL) delay(20);
  setSpeed(20);
  while(isDriving()) delay(20);
  driveAsync(.4 TL);
  setSpeed(40);
  while(isDriving()) delay(20);
}

void backToFront(){
  drive(.2 TL);
  turn(86);
  drive(2.05 TL);
  turn(-90);
  drive(-.5 TL);
}

void wallToFlag(){
  drive(.22 TL);
  turn(85);
  doubleShot();
}

void lowFlag(){
  turn(12);
  loadAndClearAsync();
  driveAsync(2.3 TL);
  while(drivePos() < 1.7 TL) delay(20);
  setSpeed(40);
  while(isDriving()) delay(20);
}

void intakeFlip(){
  intake(-80);
  driveAsync(2.4 TL);
  while(drivePos() < 2 TL) delay(20);
  intakeBallAsync();
  while(drivePos() < 2.2 TL) delay(20);
}
