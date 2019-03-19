#include "main.h"

int auton = 0; // keeps track of what auton is selected
bool mirror = false;

ADILineSensor nav('C');
ADILineSensor color('D');

void autonSelector(void* parameter){
  delay(200); // prevent the bug where buttons trigger randomly on startup

  const int autoCount = 5;
  const char *autoNames[autoCount] = {
    "big boi",
    "skills",
    "biggie cheese",
    "zaccAttack",
    "big boi high flag"
  };

  //auton selector
  lcd::initialize();
  lcd::set_text(0, "Select an Auton");
  lcd::print(2, "%s", autoNames[auton]);
  lcd::print(4, "%s", mirror ? "blue" : "red");

  while(1){
    //display auton

    if(nav.get_value() < 2100){
      auton++;
      if(auton == autoCount)
        auton = 0;

      lcd::print(2, "%s", autoNames[auton]);
      while(nav.get_value() < 2100) delay(20);
      delay(300);
    }

    if(color.get_value() < 2100){
      mirror = !mirror;
      lcd::print(4, "%s", mirror ? "blue" : "red");
      while(color.get_value() < 2100) delay(20);
      delay(300);
    }

    delay(50);
  }
}

void initialize() {
  Task lcd_task(autonSelector);
}

void disabled() {}

void competition_initialize() {}
