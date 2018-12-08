#include "main.h"

Controller master(CONTROLLER_MASTER);

void opcontrol() {
	while (true){
		driveOp();
		intakeOp();
		launcherOp();
		adjusterOp();
    liftOp();

		if(master.get_digital(DIGITAL_LEFT) && !competition::is_connected())
			autonomous();

		delay(10);
	}
}
