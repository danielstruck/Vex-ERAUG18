#include "motion.h"

void driveInches(float inches) {
  // uses wheel encoders to drive a distance in inches
  float rotationsRequired = inches /(1.414 * WHEEL_CIRCUMFERENCE);
  int rawValue = rotationsRequired * WHEEL_ROTATION_VALUE;
  clearLCDLine(0);
  displayLCDNumber(0, 0, rotationsRequired);
  displayLCDNumber(1, 0, rawValue);
  driveRaw(rawValue);
  // c * r = d
  // r = d / c
}

void driveRaw(int amount) {
	const float slowMult = .9;
	
	resetDriveEncoders();

	if (amount > 0) {
		// for driving forward
		while(getDriveEncoderAvg() <= amount) {
			if (getLeftEncoder() > getRightEncoder()) {
				// left side is faster -- needs to slow down
				leftWheels(WHEELS_FORWARD * slowMult);
				rightWheels(WHEELS_FORWARD)
			}
			else {
				// right side is faster
				leftWheels(WHEELS_FORWARD);
				rightWheels(WHEELS_FORWARD * slowMult);
			}
			
			wait1Msec(10); // let other tasks run
		}
		driveSpeed(WHEELS_BACKWARD); // kill the momentum
	}
	else {
		// for driving backward
		while(getDriveEncoderAvg() >= amount) {
			if (getLeftEncoder() < getRightEncoder()) {
				// left side is faster -- needs to slow down
				leftWheels(WHEELS_BACKWARD * .9);
				rightWheels(WHEELS_BACKWARD)
			}
			else {
				// right side is faster
				leftWheels(WHEELS_BACKWARD);
				rightWheels(WHEELS_BACKWARD * .9);
			}
			
			wait1Msec(10); // let other tasks run
		}
		driveSpeed(WHEELS_FORWARD); // kill the momentum
	}

	wait1Msec(90);
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


void resetDriveEncoders() {
	SensorValue[leftEncoder] = 0;
	SensorValue[rightEncoder] = 0;
}
int getDriveEncoderAvg() {
	return (getRightEncoder() + getLeftEncoder()) / 2;
}
int getRightEncoder() {
	// right encoder returns negative values for forward
	return -SensorValue[rightEncoder];
}
int getLeftEncoder() {
	return SensorValue[leftEncoder];
}
void resetGyro() {
  SensorType[gyroSens] = sensorNone;
  wait1Msec(1000);
  SensorType[gyroSens] = sensorGyro;
}
int getGyro() {
  return SensorValue[gyroSens] - 1800;
}