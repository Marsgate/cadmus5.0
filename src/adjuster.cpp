#include "main.h"

static int adjusterTarget = 0;
int d = 1;

//motors
Motor adjuster1(ADJUSTER, MOTOR_GEARSET_6, 1);

/**************************************************/
//basic control
void adjuster(int vel){
  adjuster1.set_brake_mode(MOTOR_BRAKE_BRAKE);
  adjuster1.move(vel);
}

/**************************************************/
//autonomous control
void adjustAsync(){
  adjusterTarget = 1;
}

void adjust(){
  d = -d;
  adjuster(127*d);
  delay(600);
  adjuster(0);
}

/**************************************************/
//task control
void adjustTask(void* parameter){
  while(1){
    delay(20);

    switch(adjusterTarget){
      case 1:
        adjust();
        break;
    }

    adjusterTarget = 0;
  }
}

/**************************************************/
//operator control
void adjusterOp(){
  static int vel = 0;
  static int t = 0;
  int amount = 30;

  if(t <= amount)
    t++;

  adjuster(vel);

  if(master.get_digital_new_press(DIGITAL_L2))
    d = -d, vel = 127*d, t = 0;
  else if(t > amount)
    vel = 0;
}
