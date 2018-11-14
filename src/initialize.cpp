#include "main.h"

void initialize(){
  Task drive_task(driveTask);
  Task turn_task(turnTask);
  Task adjust_task(adjustTask);
  Task intake_task(intakeTask);
  Task launcher_task(launcherTask);
}

void disabled() {}

void competition_initialize() {}
