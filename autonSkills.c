#include "motion.h"
#include "sensors.h"
#include "autonTools.h"


void autonSkills() {
#warning "  autonSkills::autonSkills() untested"
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
	lockCaptureStart();
}

void s_moveToFeeder() {
	setLiftPos(LIFT_HEIGHT_FEEDER_WAIT);
	autonRotate(ROTATE_RIGHT_1_DEG * 90, ROTATE_DEGREES_MULT);
	strafeInches(STRAFE_RIGHT_1_INCH * 20, DRIVE_INCHES_MULT);
}

void s_collectFedCones() {
	static const int CONES_MAX = 7;
	// !! asumes that lift is at LIFT_HEIGHT_FEEDER_WAIT  !!
	setLiftPos(LIFT_HEIGHT_FEEDER);
	int i = 0;
	for (; i < 3; i++) {
		collectCone();
		setPistons(PISTON_RETRACT);
		waitForStabilize();
		wait1Msec(1500);
		setPistons(PISTON_EXTEND);
	}
	// increase heights for each next cone
}

void s_scoreMobileGoal() {
	
}

// =======other definitions=======
