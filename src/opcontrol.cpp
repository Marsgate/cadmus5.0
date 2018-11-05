#include "main.h"

Controller master(CONTROLLER_MASTER);

void opcontrol() {
	while (true){

		driveOp();
		intakeOp();

		if(master.get_digital(DIGITAL_LEFT))
			autonomous();

		delay(10);
	}
}
