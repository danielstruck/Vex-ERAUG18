
task autonomous() {
	displayLCDCenteredString(0, "AUTON");
	displayLCDCenteredString(1, autonNames[selectedAuton]);
	
	startTask(LCDControl);
	
	switch (selectedAuton) {
		case 1:
		  autonBlue();
		  break;
		case 2:
		  autonRed();
		  break;
		case 3:
		  autonSkills();
		  break;
		default:
		  autonDefault();
		  break;
	}
}
