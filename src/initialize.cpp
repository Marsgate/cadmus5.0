#include "main.h"

int auton = 0; // keeps track of what auton is selected
bool mirror = false;

ADIButton nav('C');
ADIButton enter('D');

void autonSelector(void* parameter){
  delay(200); // prevent the bug where buttons trigger randomly on startup

  const int autoCount = 4;
  const char *autoNames[autoCount] = {
    "big boi",
    "skills",
    "back",
    "delayed back"
  };

  //auton selector
  lcd::initialize();
  bool state = true;
  lcd::set_text(0, "Select an Auton");
  while(1){
    //display auton
    lcd::print(2, "%s%s", autoNames[auton], state ? "<" : "");
    lcd::print(4, "%s%s", mirror ? "blue" : "red", state ? "" : "<");

    if(state){
      if(nav.get_new_press()){
        auton++;
        if(auton == autoCount)
          auton = 0;
      }
    }else{
      if(nav.get_new_press())
          mirror = !mirror;
    }

    if(enter.get_new_press())
      state = !state;

    delay(50);
  }
}

void initialize() {
  Task lcd_task(autonSelector);
}

void disabled() {}

void competition_initialize() {}
