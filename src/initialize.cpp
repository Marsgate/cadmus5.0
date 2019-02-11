#include "main.h"

int auton = 0; // keeps track of what auton is selected
bool mirror = false;

ADIButton nav('C');
ADIButton color('D');

void autonSelector(void* parameter){
  delay(200); // prevent the bug where buttons trigger randomly on startup

  const int autoCount = 5;
  const char *autoNames[autoCount] = {
    "big boi",
    "skills",
    "back",
    "zaccAttack",
    "big boi high flag"
  };

  //auton selector
  lcd::initialize();
  lcd::set_text(0, "Select an Auton");
  while(1){
    //display auton
    lcd::print(2, "%s", autoNames[auton]);
    lcd::print(4, "%s", mirror ? "blue" : "red");

    if(nav.get_new_press()){
      auton++;
      if(auton == autoCount)
        auton = 0;
    }

    if(color.get_new_press())
      mirror = !mirror;

    delay(50);
  }
}

void initialize() {
  Task lcd_task(autonSelector);
}

void disabled() {}

void competition_initialize() {}
