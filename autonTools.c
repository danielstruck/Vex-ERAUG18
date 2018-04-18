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

void autonDrive(float inches) {
	driveInches(inches);
	waitForStabilize();
}

void autonRotate(float degrees) {
	rotateDeg(degrees);
	waitForStabilize();
}

void autonStrafe(float inches) {
	strafeInches(inches);
	waitForStabilize();
}