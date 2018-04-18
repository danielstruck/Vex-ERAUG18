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
	//lift location:      bottom
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
	driveInches(19.5);
	
	//--at goal--
	
	waitForStabilize();
	setLiftPos(LIFT_HEIGHT_HIGH_GOAL);
	depositCone();
	setLiftPos(LIFT_HEIGHT_TOP);
	
	//--deposited cone--
}

void b_pickUpRightCone() {
	driveInches(-7); // avoid clipping the high goal on turn
	rotateDeg(ROTATE_RIGHT_1_DEG * 53);
	
	// facing cone
	
	driveInches(47.5);
	
	// at cone
	
	setLiftPos(LIFT_HEIGHT_CONE);
	collectCone();
	
	// collected cone
}

void b_putConeOnMobileBase() {
	rotateDeg(ROTATE_RIGHT_1_DEG * 5);
	
	// facing mobile goal
	
	setLiftPos(LIFT_HEIGHT_MOBILE);
	driveInches(15.5);
	
	// cone is over mobile goal
	
	liftSpeed(0);
	depositCone();
	setLiftPos(LIFT_HEIGHT_HIGH_GOAL);
	
	// scored cone on goal
}

void b_scoreMobileBase() {
	driveInches(9);
	startTask(lockCapture); // remember to stop the task
	
	// base captured
	
	rotateDeg(ROTATE_LEFT_1_DEG * 35);
	
	// facing opposite of 20pt goal
	
	driveInches(-35); // drive part of the way to avoid the cones
	waitForStabilize();
	rotateDeg(ROTATE_LEFT_1_DEG * 180);
	waitForStabilize();
	
	// facing 20pt goal
	
	driveInches(40);
	
	// at 20pt zone
	
	stopTask(lockCapture); // remembered to stop the task :)
	setCapturePos(CAPTURE_EXTENDED);
	driveInches(-20);
	
	// deposited mobile goal
}

// =======other definitions=======
