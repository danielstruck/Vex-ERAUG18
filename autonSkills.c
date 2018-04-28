#include "motion.h"
#include "sensors.h"
#include "autonTools.h"


void autonSkills(int direction) {
#warning "  autonSkills::autonSkills() untested"
	displayLCDCenteredString(0, "AUTON SKILLS");

	s_moveToMobileGoal();
	
	s_collectMobileGoal();
	
	s_moveToFeeder(direction);
	
	s_collectFedCones();
	
	s_scoreMobileGoal(direction);
}

// ====== step definitions ======
void s_moveToMobileGoal() {
	setLiftPos(LIFT_HEIGHT_MOBILE);
	autonDrive(51, DRIVE_INCHES_MULT);
	depositCone();
}

void s_collectMobileGoal() {
	autonDrive(12, DRIVE_INCHES_MULT);
}

void s_moveToFeeder(int direction) {
	setLiftPos(LIFT_HEIGHT_FEEDER_WAIT);
	autonDrive(-20, DRIVE_INCHES_MULT);
	autonRotate(direction * ROTATE_RIGHT_1_DEG * 90, ROTATE_DEGREES_MULT);
}

void s_collectFedCones() {
	static const int CONES_MAX    = 7;
	static const int CONES_STATIC = 3; // cones stacked before lift goes up
	static const int OFFSET       = 100; // height difference for next cone
	
	lockCaptureStop();
	setCapturePos(CAPTURE_RETRACTED);
	int nCones = 1;
	
	// !! asumes that lift is at LIFT_HEIGHT_FEEDER_WAIT  !!
	for (; nCones < CONES_STATIC; ++nCones) {
		setLiftPos(LIFT_HEIGHT_FEEDER);
		collectCone();
		s_depositFeederCone();
	}
	// increase heights for each next cone
	for (; nCones < CONES_MAX; ++nCones) {
		collectCone();
		setLiftPos(LIFT_HEIGHT_FEEDER + OFFSET * (i-CONES_STATIC));
		s_depositFeederCone();
	}
	
	lockCaptureStart();
}

void s_scoreMobileGoal(int direction) {
	autonDrive(-35, DRIVE_INCHES_MULT);
	autonRotate(direction * ROTATE_RIGHT_1_DEG * 55, ROTATE_DEGREES_MULT);
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