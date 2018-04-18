#include "motion.h"
#include "sensors.h"
#include "autonTools.h"

void autonDefault() {
// #warning "  autonDefault::autonDefault() is unimplemented"
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

// ====== step definitions ======

// =======other definitions=======
