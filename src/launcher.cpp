#include "main.h"

static int launcherTarget = 0;
const int ratchetDistance = 50;

//motors
Motor launcher1(14, MOTOR_GEARSET_36, 1, MOTOR_ENCODER_DEGREES);

//line sensors
ADIAnalogIn line('E');

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
  while(launcher1.get_position() < 50) delay(20);
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
  static bool first = true;

  launcher(vel);

  if(master.get_digital(DIGITAL_R2)){
    vel = 127;
    first = false;
  }else
    vel = 0;


  static int panic = false;
  if(master.get_digital_new_press(DIGITAL_UP))
    panic = !panic;


  //auto ratcheting
  if(isFired() && !panic && !first){
    ready = false;
    launcher1.tare_position();
  }

  if(launcher1.get_position() > 50)
    ready = true;

  if(!ready)
    vel = 127;

}
