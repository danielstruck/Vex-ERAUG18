#include "sensors.h"

void setPistons(int state) {
	SensorValue[pistonOne] = state;
	SensorValue[pistonTwo] = state;
}

void drumSpeed(int speed) {
	motor[frictionDrum2] = speed;
}

void liftSpeed(int speed) {
	motor[liftLeft] = speed;
	motor[liftRight] = speed;
}

void lockLift() {
	const static float liftMax  = 850, // the encoder value of the lift when it is at its highest point
	liftPow  = 35, // the power imparted to the lift when it is at liftMax
	liftPow0 = 85, // the sensor value at zero power
	abruptness = 3; // !!must be positive and odd!! - the abruptness of the positive/ negetive switch (13+ is basically a step function)

	static const float denominator = liftMax - liftPow0;

	const int x = getLiftEncoder();
	float numerator = x - liftPow0;
	int sign = (numerator == 0)? 0: (abs(numerator/denominator)/(numerator/denominator));
	int speed = liftPow * pow(abs(numerator / denominator), 1.0/abruptness) * sign;

	liftSpeed(speed);
}

void mobileCaptureSpeed(int speed) {
	motor[mobileCapture] = speed;
}

void frontWheels(int speed) {
	motor[frontLeft] = speed;
	motor[frontRight] = speed;
}

void backWheels(int speed) {
	motor[backLeft] = speed;
	motor[backRight] = speed;
}

void leftWheels(int speed) {
	motor[frontLeft] = speed;
	motor[backLeft] = speed;
}

void rightWheels(int speed) {
	motor[frontRight] = -speed;
	motor[backRight] = -speed;
}

void driveSpeed(int speed) {
	leftWheels(speed);
	rightWheels(speed);
}

void strafeSpeed(int speed) {
#warning "  motion::strafeSpeed untested"
	frontWheels(speed);
	backWheels(-speed * STRAFE_REAR_MULT);
}

void turnSpeed(int speed) {
	leftWheels(speed);
	rightWheels(-speed);
}

void stopWheels() {
	motor[frontLeft] = 0;
	motor[frontRight] = 0;
	motor[backRight] = 0;
	motor[backLeft] = 0;
}
