#include "motion.h"
#include "sensors.h"
#include "autonTools.h"


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
	//lift location:     high
	//capture location:  retracted
	//drum speed:        off

	b_scoreMobileBase();
	
	//last action:       scored mobile goal in 20pt zone
	//position on field: near start
	//lift location:     high
	//capture location:  extended
	//drum speed:        off
}

// ====== step definitions ======
void b_scorePreloadOnStationaryGoal() {
	setLiftPos(LIFT_HEIGHT_TOP);
	waitForStabilize();
	autonDrive(23, DRIVE_INCHES_MULT);
	
	//--at goal--
	
	setLiftPos(LIFT_HEIGHT_HIGH_GOAL);
	depositCone();
	
	//--deposited cone--
}

void b_pickUpRightCone() {
	autonDrive(-20, DRIVE_INCHES_MULT); // avoid clipping the high goal on turn
	autonRotate(ROTATE_RIGHT_1_DEG * 55, ROTATE_DEGREES_MULT);
	
	// facing cone
	
	autonDrive(57, DRIVE_INCHES_MULT);
	
	// at cone
	
	setLiftPos(LIFT_HEIGHT_CONE);
	collectCone();
	
	// collected cone
}

void b_putConeOnMobileBase() {
	autonRotate(ROTATE_RIGHT_1_DEG * 20, ROTATE_DEGREES_MULT);
	
	// facing mobile goal
	
	setLiftPos(LIFT_HEIGHT_MOBILE);
	autonDrive(14, DRIVE_INCHES_MULT);
	
	// cone is over mobile goal
	
	depositCone();
	setLiftPos(LIFT_HEIGHT_HIGH_GOAL); // so we dont clip the cone
	
	// scored cone on goal
}

void b_scoreMobileBase() {
	autonDrive(12, DRIVE_INCHES_MULT);
	lockCaptureStart(); // remember to stop lockCapture
	wait1Msec(2 * 1000);
	
	// base captured
	
	//autonRotate(ROTATE_LEFT_1_DEG * 28, ROTATE_DEGREES_MULT);
	
	// facing opposite of 20pt goal
	
	autonDrive(-24, DRIVE_INCHES_MULT); // drive part of the way to avoid the cones
	autonRotate(ROTATE_RIGHT_1_DEG * (180 - 25), ROTATE_DEGREES_MULT);
	
	// facing 20pt goal
	
	driveSpeed(WHEELS_FORWARD);
	wait1Msec(7 * 1000);
	stopWheels();
	
	//autonDrive(65, 1);
	
	// at 20pt zone
	
	lockCaptureStop(); // remembered to stop lockCapture :)
	setCapturePos(CAPTURE_EXTENDED);
	autonDrive(-20, 1);
	
	// deposited mobile goal
}

// =======other definitions=======
