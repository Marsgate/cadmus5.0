#include "main.h"

//motors
Motor launcher_1(4);

//line sensors
ADIAnalogIn line('D');

void launcher(int vel){
  launcher_1.move(vel);
}

bool isFired(){
  if(line.get_value() < 2000)
    return true;
  else
    return false;
}

void launcherOp(){
  static int vel = 0;
  static int t = 0;

  launcher(vel);

  if(master.get_digital(DIGITAL_R2))
    vel = 127;
  else
    vel = 0;


  static int panic = false;
  if(master.get_digital_new_press(DIGITAL_UP))
    panic = !panic;


  //auto ratcheting
  if(isFired() && !panic)
    t = 20;
  if(t > 0)
    vel = 127;
  t--;

}

//tasks
void autoShootTask(void * parameter){
  launcher(127);
  while(!isFired()) delay(20);
  delay(500);
  launcher(0);
}

void autoShoot(){
  Task shootTask(autoShootTask);
}
