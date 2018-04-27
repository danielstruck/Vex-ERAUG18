#include "motion.h"
#include "sensors.h"
#include "autonTools.h"


void autonSkills() {
#warning "  autonSkills::autonSkills() untested"
	displayLCDCenteredString(0, "AUTON SKILLS");

	s_moveToMobileGoal();
	
	s_collectMobileGoal();
	
	s_moveToFeeder();
	
	s_collectFedCones();
	
	s_scoreMobileGoal();
}

// ====== step definitions ======
void s_moveToMobileGoal() {
	setLiftPos(LIFT_HEIGHT_MOBILE);
	autonDrive(51, 1);
	depositCone();
}

void s_collectMobileGoal() {
	autonDrive(8, 1);
}

void s_moveToFeeder() {
	setLiftPos(LIFT_HEIGHT_FEEDER_WAIT);
	autonRotate(ROTATE_RIGHT_1_DEG * 90, ROTATE_DEGREES_MULT);
	strafeInches(STRAFE_RIGHT_1_INCH * 20, DRIVE_INCHES_MULT);
}

void s_collectFedCones() {
	static const int CONES_MAX    = 7;
	static const int CONES_STATIC = 3; // cones stacked before lift goes up
	static const int OFFSET       = 100; // height difference for next cone
	
	lockCaptureStop();
	setCapturePos(CAPTURE_RETRACTED);
	int i = 0;
	
	// !! asumes that lift is at LIFT_HEIGHT_FEEDER_WAIT  !!
	for (; i < CONES_STATIC; ++i) {
		setLiftPos(LIFT_HEIGHT_FEEDER);
		collectCone();
		s_depositFeederCone();
	}
	// increase heights for each next cone
	for (; i < CONES_MAX; ++i) {
		collectCone();
		setLiftPos(LIFT_HEIGHT_FEEDER + OFFSET * (i-CONES_STATIC));
		s_depositFeederCone();
	}
	
	lockCaptureStart();
}

void s_scoreMobileGoal() {
	autonDrive(-35, DRIVE_INCHES_MULT);
	autonRotate(ROTATE_RIGHT_1_DEG * 55, ROTATE_DEGREES_MULT);
	driveSpeed(WHEELS_FORWARD);
	wait1Msec(7 * 1000);
	driveSpeed(0);
	lockCaptureStop();
	setCapturePos(CAPTURE_EXTENDED);
	autonDrive(-20, 1);
}

// =======other definitions=======
void s_depositFeederCone() {
		setPistons(PISTON_RETRACT);
		waitForStabilize();
		depositCone();
		setPistons(PISTON_EXTEND);
		setLiftPos(LIFT_HEIGHT_FEEDER_WAIT);
}