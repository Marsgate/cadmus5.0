#include "main.h"

Controller master(CONTROLLER_MASTER);

void opcontrol() {
	while (true){
    enableSlew(false);

		driveOp();
		intakeOp();
		launcherOp();
		adjusterOp();
		descoreOp();

		if(master.get_digital(DIGITAL_LEFT) && !competition::is_connected())
			autonomous();

		delay(10);
	}
}
