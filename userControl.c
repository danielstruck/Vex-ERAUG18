#include "motion.h"
#include "lcdControl.h"
#include "tools.h"


task usercontrol() {
	displayLCDCenteredString(0, "USER CONTROL");
	
	startTask(LCDControl);
	
	startTask(liftSensorControl);
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
	
	motor[frontLeft] =    DIVE_AXIS +                    strafeVal + ROTATE_AXIS;
	motor[frontRight] =  -DIVE_AXIS +                    strafeVal + ROTATE_AXIS;
	motor[backRight] =   -DIVE_AXIS + STRAFE_REAR_MULT * strafeVal - ROTATE_AXIS;
	motor[backLeft] =     DIVE_AXIS + STRAFE_REAR_MULT * strafeVal - ROTATE_AXIS;
}

void liftControl(){
	static bool lockToggle = true, lockToggleActive = false;
	
	if (LIFT_UNPOWER_BTN) {
		if (!lockToggleActive) {
			lockToggleActive = true;
			lockToggle = !lockToggle;
		}
	}
	else
		lockToggleActive = false;
	
	if (!autonomousLiftControl) {
		if (LIFT_UP_BTN)
			liftSpeed(LIFT_UP);
		else if (LIFT_DOWN_BTN)
			liftSpeed(LIFT_DOWN);
		else {
			if (lockToggle)
				lockLift();
			else
				liftSpeed(0);
		}
	}
}

task liftSensorControl() {
	while (1) {
		if (LIFT_HEIGHT_TOP_BTN) {
		clearLCDLine(0);
			displayLCDCenteredString(0, "TOP");
			autonomousLiftControl = true;
			setLiftPos(LIFT_HEIGHT_TOP);
		}
		else if (LIFT_HEIGHT_BOT_BTN) {
		clearLCDLine(0);
			displayLCDCenteredString(0, "BOTTOM");
			autonomousLiftControl = true;
			setLiftPos(LIFT_HEIGHT_BOTTOM);
		}
		else if (LIFT_HEIGHT_MOBILE_BTN) {
		clearLCDLine(0);
			displayLCDCenteredString(0, "MOBILE");
			autonomousLiftControl = true;
			setLiftPos(LIFT_HEIGHT_MOBILE);
		}
		else if (LIFT_HEIGHT_FEEDER_BTN) {
		clearLCDLine(0);
			displayLCDCenteredString(0, "FEEDER");
			autonomousLiftControl = true;
			setLiftPos(LIFT_HEIGHT_FEEDER_WAIT);
		}
		else {
		clearLCDLine(0);
			displayLCDCenteredString(0, "NONE");
			autonomousLiftControl = false;
		}
	}
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
		drumSpeed(shouldIdle? DRUM_HOLD: 0);
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
		lockCaptureStart();
	}
	else {
		if (abs(MOBILE_AXIS) > 75) {
			mobileCaptureIsLocked = false;
			mobileCaptureSpeed(MOBILE_AXIS);
		}
		else if (!mobileCaptureIsLocked) {
			mobileCaptureSpeed(0);
		}
	}
}
