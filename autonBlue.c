
void autonBlue() {
	//last action:       tmpAct
	//position on field: tmpPos
	//lift location:     tmpLift
	//capture location:  tmpCapt
	//drum speed:        tmpDrum

//==================================================

	//last action:       started match
	//position on field: at start
	//lift location:     bottom
	//capture location:  retracted
	//drum speed:        off

	b_scorePreloadOnStationaryGoal();

	//last action:       deposited cone
	//position on field: at high goal
	//lift location:     top
	//capture location:  retracted
	//drum speed:        off

	b_pickUpRightCone();

	//last action:       collected cone
	//position on field: at first cone
	//lift location:     cone
	//capture location:  retracted
	//drum speed:        hold
	
	b_putConeOnMobileBase();

	//last action:       scored cone on mobile base
	//position on field: at mobile base
	//lift location:     high goal
	//capture location:  retracted
	//drum speed:        off

	b_scoreMobileBase();
	
	//last action:       scored mobile goal in 20pt zone
	//position on field: near start
	//lift location:     high goal
	//capture location:  extended
	//drum speed:        off
}

// ====== step definitions ======
void b_scorePreloadOnStationaryGoal() {
	drumSpeed(DRUM_HOLD);
	setPistons(PISTON_EXTEND);
	setLiftPos(LIFT_HEIGHT_TOP);
	autonDrive(19.5);
	
	//--at goal--
	
	setLiftPos(LIFT_HEIGHT_HIGH_GOAL);
	depositCone();
	setLiftPos(LIFT_HEIGHT_TOP);
	
	//--deposited cone--
}

void b_pickUpRightCone() {
	autonDrive(-7); // avoid clipping the high goal on turn
	autonRotate(ROTATE_RIGHT_1_DEG * 53);
	
	// facing cone
	
	autonDrive(47.5);
	
	// at cone
	
	setLiftPos(LIFT_HEIGHT_CONE);
	collectCone();
	
	// collected cone
}

void b_putConeOnMobileBase() {
	autonRotate(ROTATE_RIGHT_1_DEG * 5);
	
	// facing mobile goal
	
	setLiftPos(LIFT_HEIGHT_MOBILE);
	autonDrive(15.5);
	
	// cone is over mobile goal
	
	liftSpeed(0);
	depositCone();
	setLiftPos(LIFT_HEIGHT_HIGH_GOAL);
	
	// scored cone on goal
}

void b_scoreMobileBase() {
	autonDrive(9);
	lockCaptureStart(); // remember to stop lockCapture
	
	// base captured
	
	autonRotate(ROTATE_LEFT_1_DEG * 35);
	
	// facing opposite of 20pt goal
	
	autonDrive(-35); // drive part of the way to avoid the cones
	autonRotate(ROTATE_LEFT_1_DEG * 180);
	
	// facing 20pt goal
	
	autonDrive(40);
	
	// at 20pt zone
	
	lockCaptureStop(); // remembered to stop lockCapture :)
	setCapturePos(CAPTURE_EXTENDED);
	autonDrive(-20);
	
	// deposited mobile goal
}

// =======other definitions=======
