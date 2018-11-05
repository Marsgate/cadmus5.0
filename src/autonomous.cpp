#include "main.h"

//definition of a tile in encoder ticks
#define TL *644

void autonomous() {
  Task drive_task (driveTask);
  Task turn_task (turnTask);

  autoDrive(2 TL);

  drive_task.remove();
  turn_task.remove();
}
