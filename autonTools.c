#include "motion.h"
#include "sensors.h"


void depositCone() {
	drumSpeed(DRUM_PUSH);
	wait1Msec(1000);
	drumSpeed(0);
}

void collectCone() {
	drumSpeed(DRUM_PULL);
	wait1Msec(1000);
	drumSpeed(DRUM_HOLD);
}

void waitForStabilize() {
	wait1Msec(750);
}

void autonDrive(float inches, float mult) {
	driveInches(inches, mult);
	waitForStabilize();
}

void autonRotate(float degrees, float mult) {
	rotateDeg(degrees, mult);
	waitForStabilize();
}

void autonStrafe(float inches, float mult) {
	strafeInches(inches, mult);
	waitForStabilize();
}

void setupAuton() {
	resetSensors();
	drumSpeed(DRUM_PULL);
	wait1Msec(600);
	drumSpeed(0);
	drumSpeed(DRUM_HOLD);
	setPistons(PISTON_EXTEND);
}
