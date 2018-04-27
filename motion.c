#include "sensors.h"


void setPistons(int state) {
	SensorValue[pistonOne] = state;
	SensorValue[pistonTwo] = state;
}

void drumSpeed(int speed) {
	motor[frictionDrum2] = speed;
}

void liftSpeed(int speed) {
	motor[liftLeft]  = speed;
	motor[liftRight] = speed;
}

void mobileCaptureSpeed(int speed) {
	motor[mobileCapture] = speed;
}

void flSpeed(int speed) {
	motor[frontLeft] = speed;
}
void blSpeed(int speed) {
	motor[backLeft] = speed;
}
void frSpeed(int speed) {
	motor[frontRight] = -speed;
}
void brSpeed(int speed) {
	motor[backRight] = -speed;
}

void frontWheels(int speed) {
	flSpeed(speed);
	frSpeed(-speed);
}

void backWheels(int speed) {
	blSpeed(speed);
	brSpeed(-speed);
}

void leftWheels(int speed) {
	flSpeed(speed);
	blSpeed(speed);
}

void rightWheels(int speed) {
	frSpeed(speed);
	brSpeed(speed);
}

void driveSpeed(int speed) {
	leftWheels(speed);
	rightWheels(speed);
}

void strafeSpeed(int speed) {
	frontWheels(speed);
	backWheels(-speed * STRAFE_REAR_MULT);
}

void turnSpeed(int speed) {
	leftWheels(speed);
	rightWheels(-speed);
}

void stopWheels() {
	driveSpeed(0);
}
