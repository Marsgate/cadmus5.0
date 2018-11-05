#include "main.h"

Controller master(CONTROLLER_MASTER);

void opcontrol() {
	while (true){
		driveOp();
		if(master.get_digital(DIGITAL_LEFT)){
			autonomous();
		}
		delay(10);
	}
}
