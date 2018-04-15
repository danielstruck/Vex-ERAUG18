#include "motion.h"

task usercontrol() {
	while (true) {
		driveControl();

		liftControl();

		drumControl();

		pistonControl();

		mobileControl();
	}
}

void driveControl(){
	// Y component, X component, Rotation
	int strafeVal = STRAFE_AXIS;
	if (abs(strafeVal) < 20)
		strafeVal = 0;

	motor[frontLeft] =    DIVE_AXIS + strafeVal + ROTATE_AXIS;
	motor[frontRight] =  -DIVE_AXIS + strafeVal + ROTATE_AXIS;
	motor[backRight] =    DIVE_AXIS + strafeVal - ROTATE_AXIS;
	motor[backLeft] =    -DIVE_AXIS + strafeVal - ROTATE_AXIS;
}

void liftControl(){
	if(LIFT_UP_BTN)
		liftSpeed(LIFT_UP);
	else if(LIFT_DOWN_BTN)
		liftSpeed(LIFT_DOWN);
	else
		lockLift();
}

void drumControl(){
	static bool shouldIdle = false;
	if(DRUM_PULL_BTN) {
		drumSpeed(DRUM_PULL);
		shouldIdle = true;
	}
	else if(DRUM_PUSH_BTN) {
		drumSpeed(DRUM_PUSH);
		shouldIdle = false;
	}
	else {
		if (shouldIdle)
			drumSpeed(DRUM_HOLD);
		else
			drumSpeed(0);
	}
}

void pistonControl(){
	if (PISTON_RETRACT_BTN)
		setPistons(PISTON_RETRACT);
	else if (PISTON_EXTEND_BTN)
		setPistons(PISTON_EXTEND);
}

void mobileControl(){
	if (MOBILE_LOCK_BTN && !mobileCaptureIsLocked){
		startTask(lockMobile);
	}
	else {
		if (abs(MOBILE_AXIS) > 50) {
			mobileCaptureIsLocked = false;
			mobileCaptureSpeed(MOBILE_AXIS);
		}
		else if (!mobileCaptureIsLocked) {
			mobileCaptureSpeed(0);
		}
	}
}
