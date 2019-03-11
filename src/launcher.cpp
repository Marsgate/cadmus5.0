#include "main.h"

static int launcherTarget = 0;
const int rd = 180;

//motors
Motor launcher1(LAUNCHER, MOTOR_GEARSET_18, 1, MOTOR_ENCODER_DEGREES);

//line sensors
ADIAnalogIn line('G');

/**************************************************/
//basic control
void launcher(int vel){
  launcher1.move(vel);
}

/**************************************************/
//feedback
bool isFired(){
  if(line.get_value() < 2000)
    return true;
  else
    return false;
}

/**************************************************/
//autonomous control
void shootAsync(){
  launcherTarget = 1;
}

void ratchetAsync(){
  launcherTarget = 2;
}

void shoot(){
  launcher(127);
  while(!isFired()) delay(20);
  launcher(0);
}

void ratchet(){
  launcher(127);
  while(isFired()) delay(20);
  launcher1.tare_position();
  while(launcher1.get_position() < rd) delay(20);
  launcher(0);
}

/**************************************************/
//task control
void launcherTask(void* parameter){
  while(1){
    delay(20);

    switch(launcherTarget){
      case 1:
        shoot();
        break;
      case 2:
        ratchet();
        break;
    }

    launcherTarget = 0;
  }
}

/**************************************************/
//operator control
void launcherOp(){
  static int vel = 0;
  static int ready = true;
  static int ratchetEnable = false;
  static int panic;

  if(master.get_digital_new_press(DIGITAL_UP)){
    panic = !panic;
  }

  vel = 0;

  if(master.get_digital(DIGITAL_R2)){
    if(panic){
      vel = 127;
      ratchetEnable = false;
    }else{
      if(isLoaded()){
        vel = 127;
      }
      ratchetEnable = true;
    }
  }else if(master.get_digital(DIGITAL_A)){
    if(!isFired()){
      vel = 127;
    }
    ratchetEnable = false;
  }

  //auto ratcheting
  if(isFired() && ratchetEnable){
    ready = false;
    launcher1.tare_position();
  }

  if(launcher1.get_position() > rd)
    ready = true;

  if(!ready)
    vel = 127;

  launcher(vel);
}
