#include "motion.h"
#include "sensors.h"

void autonBlue() {
	//last action:
	//position on field:
	//lift location:
	//capture location:
	//drum speed:

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

	//last action:
	//position on field:
	//lift location:
	//capture location:
	//drum speed:
}

// ====== step definitions ======
void b_scorePreloadOnStationaryGoal() {
	setPistons(PISTON_PUSH);
	frictionDrumSpeed(DRUM_HOLD);
	setLiftPos(LIFT_HEIGHT_TOP);
	driveInches(20);
	//--at goal--
	wait1Msec(500);
	setLiftPos(LIFT_HEIGHT_HIGH_GOAL);
	depositCone();
	setLiftPos(LIFT_HEIGHT_TOP);
	frictionDrumSpeed(0);
	//--deposited cone--
}

void b_pickUpRightCone() {
	driveInches(-7);
	setLiftPos(LIFT_HEIGHT_CONE);
	rotateDeg(ROTATE_RIGHT_1_DEG * 45);
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
	driveInches(15);
	// cone is over mobile goal
	liftSpeed(0);
	depositCone();
	setLiftPos(LIFT_HEIGHT_HIGH_GOAL);
	// scored cone on goal
}

void b_scoreMobileBase() {
	setCapturePos(CAPTURE_EXTENDED);
	driveInches(9);
	startTask(lockMobile);
	// base captured
	rotateDeg(ROTATE_LEFT_1_DEG * 45);
	// facing oposite of 20pt goal
	driveInches(-35); // drive part of the way to avoid the cones
	rotateDeg(ROTATE_LEFT_1_DEG * 180);
	// facing 20pt goal
	driveInches(40);
	// at 20pt zone
	setCapturePos(CAPTURE_EXTENDED);
}

// ===== other definitions =====
void depositCone() {
	frictionDrumSpeed(DRUM_PUSH);
	wait1Msec(500);
	frictionDrumSpeed(0);
}
void collectCone() {
	frictionDrumSpeed(DRUM_PULL);
	wait1Msec(500);
	frictionDrumSpeed(0);
}
