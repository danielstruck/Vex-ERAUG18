#include "motion.h"
#include "sensors.h"

void depositCone() {
	drumSpeed(DRUM_PUSH);
	wait1Msec(500);
	drumSpeed(0);
}

void collectCone() {
	drumSpeed(DRUM_PULL);
	wait1Msec(500);
	drumSpeed(0);
}

void waitForStabilize() {
	wait1Msec(500);
}
