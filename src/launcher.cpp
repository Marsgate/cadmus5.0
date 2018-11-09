#include "main.h"

//motors
Motor launcher1(4, MOTOR_GEARSET_36, 1, MOTOR_ENCODER_DEGREES);

//line sensors
ADIAnalogIn line('D');

void launcher(int vel){
  launcher1.move(vel);
}

bool isFired(){
  if(line.get_value() < 2000)
    return true;
  else
    return false;
}

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

  if(launcher1.get_position() > 150)
    ready = true;

  if(!ready)
    vel = 127;

}

//tasks
void autoRatchetTask(void* parameter){
    launcher(127);
    while(isFired()) delay(20);
    while(!isFired()) delay(20);
    launcher1.tare_position();
    while(launcher1.get_position() > 150) delay(20);
    launcher(0);
}

void autoRatchet(){
  Task ratchetTask(autoRatchetTask);
}



void autoShootTask(void* parameter){
  launcher(127);
  while(!isFired()) delay(20);
  autoRatchet();
}

void autoShoot(){
  Task shootTask(autoShootTask);
}
