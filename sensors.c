#include "motion.h"

void driveIn(float inches) {
#warning "    sensors::driveIn() not implemented"
  // uses wheel encoders to drive a distance in inches
}

void driveRaw(int amount) {
	SensorValue[leftEncoder] = 0;
	SensorValue[rightEncoder] = 0;

	if (amount > 0) {
		// for driving forward
		driveSpeed(WHEELS_FORWARD * .5);
		while((SensorValue[liftEncoder] <= amount))
			wait1Msec(10); // let other tasks run
		driveSpeed(WHEELS_BACKWARD * .1); // kill the momentum
	}
	else {
		// for driving backward
		driveSpeed(WHEELS_BACKWARD * .5);
		while((SensorValue[liftEncoder] >= amount))
			wait1Msec(10); // let other tasks run
		driveSpeed(WHEELS_FORWARD * .1); // kill the momentum
	}

	wait1Msec(50);
	stopWheels();
}

void rotateDeg(float deg) {
#warning "    sensors::rotateDeg() not implemented"
  // uses the gyro to rotate to deg (gyro value of 1 = 1/10 degree)
}

void rotateRaw(int amount) {
#warning "    sensors::rotateRaw() not implemented"
  // uses the gyroscope's raw value to rotate
}

void setLiftPos(int position) {
#warning "    sensors::setLiftPos() not implemented"
  // uses lift encoder to move the lift to position
}

void setMobileCapturePos(int position) {
#warning "    sensors::setMobileCapturePos() not implemented"
  // uses mobile capture encoder to move the mobile capture to position
}

void lockLift() {
	// max lift val = 850
	const int x = SensorValue[liftEncoder];

  // quadratic
	//int speed = -5 - 0.06143791*x - 0.0000307574*x*x;
  // cubic
	int speed = -5 - 0.05198773*x + 0.00009384581*x*x + 1.579372*pow(10,-7)*x*x*x;

	liftSpeed(speed);
}
