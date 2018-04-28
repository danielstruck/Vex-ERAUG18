#include "lcdControl.h"


task autonomous() {
	displayLCDCenteredString(0, "AUTON");
	displayLCDCenteredString(1, autonNames[selectedAuton]);
	
	startTask(LCDControl);
	
	setupAuton();
	
	switch (selectedAuton) {
		case 1:
			autonBlue();
			break;
		case 2:
			autonRed();
			break;
		case 3:
			autonSkills(RED);
			break;
		case 4:
			autonSkills(BLUE);
		case 5:
			autonAmbi(RED);
			break;
		case 6:
			autonAmbi(BLUE);
			break;
		default:
			autonDefault();
			break;
	}
}
