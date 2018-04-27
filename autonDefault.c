#include "motion.h"
#include "sensors.h"
#include "autonTools.h"


void autonDefault() {
// #warning "  autonDefault::autonDefault() is unimplemented"
	drumSpeed(DRUM_HOLD);
	setPistons(PISTON_EXTEND);
	setLiftPos(LIFT_HEIGHT_TOP);
	driveInches(23, .8);

	//--at goal--

	waitForStabilize();
	setLiftPos(LIFT_HEIGHT_HIGH_GOAL);
	depositCone();
	setLiftPos(LIFT_HEIGHT_TOP);

	//--deposited cone--
	
	driveInches(-20, DRIVE_INCHES_MULT);
}

// ====== step definitions ======

// =======other definitions=======
