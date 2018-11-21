#include "main.h"

static int adjusterTarget = 0;
static int d = -1;

//motors
Motor adjuster1(15, MOTOR_GEARSET_6, 1);

/**************************************************/
//basic control
void adjuster(int vel){
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
  delay(300);
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

  if(t <= 15)
    t++;

  adjuster(vel);

  if(master.get_digital_new_press(DIGITAL_L2))
    d = -d, vel = 127*d, t = 0;
  else if(t > 15)
    vel = 0;
}
