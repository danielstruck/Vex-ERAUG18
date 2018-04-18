
void pre_auton() {
	// Stops all tasks between auton/usercontrol
	bStopTasksBetweenModes = true;

	// Turns on the LCD's Back light
	bLCDBacklight = true;

	resetSensors();

	// start motion+ updater if it has been included
#ifdef _MOTION_PLUS_H_
	startTask(motionPlusUpdater);
#endif // _MOTION_PLUS_H_

	selectAuton();

	displayBatteryLevels();
}

void selectAuton() {
	// values for the LCD buttons
	const int left   = 1;
	const int center = 2;
	const int right  = 4;


	displayLCDCenteredString(0, "Auton:");
	displayLCDCenteredString(1, autonNames[0]);

	selectedAuton = 0;
	bool autonChosen = false;

	while (!autonChosen) {
		// wait for LCD button to be pressed
		while (nLCDButtons == 0)
			wait1Msec(10);
		
		switch ((int)nLCDButtons) {
			case left: // decrement auton
				selectedAuton--;
				break;
			case center: // confirm
				autonChosen = true;
				break;
			case right: // increment auton
				selectedAuton++;
				break;
		}
		
		// lock 'selectedAuton' between 0 (inclusive) and nAutons (exclusive), applies wrap
		if (selectedAuton < 0)
			selectedAuton = nAutons-1;
		else if (selectedAuton > nAutons-1)
			selectedAuton = 0;
		
		// wait for LCD button to be released
		while (nLCDButtons != 0)
			wait1Msec(10);

		clearLCDLine(1);
		displayLCDCenteredString(1, autonNames[selectedAuton]);
	}
}
