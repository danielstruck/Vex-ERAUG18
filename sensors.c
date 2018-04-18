#include "motion.h"

void displayBatteryLevels() {
	string batteryLevel;
	sprintf(batteryLevel, "Primary: %.2fV", nImmediateBatteryLevel/1000.0);
	displayLCDCenteredString(0, batteryLevel);
	batteryLevel = "";
	sprintf(batteryLevel, "Backup: %.2fV", BackupBatteryLevel/1000.0);
	displayLCDCenteredString(1, batteryLevel);
}

void driveInches(float inches) {
	float rotationsRequired = inches /(1.414 * WHEEL_CIRCUMFERENCE);
	int rawValue = rotationsRequired * WHEEL_ROTATION_VALUE;

	driveRaw(rawValue);
}

void driveRaw(int amount) {
	const float slowMult = .9;

	resetDriveEncoders();

	if (amount > 0) {
		// for driving forward
		while(getDriveEncoderAvg() <= amount) {
			if (getLeftDriveEncoder() > getRightDriveEncoder()) {
				// left side is faster -- needs to slow down
				leftWheels(WHEELS_FORWARD * slowMult);
				rightWheels(WHEELS_FORWARD);
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
			if (getLeftDriveEncoder() < getRightDriveEncoder()) {
				// left side is faster -- needs to slow down
				leftWheels(WHEELS_BACKWARD * slowMult);
				rightWheels(WHEELS_BACKWARD);
			}
			else {
				// right side is faster
				leftWheels(WHEELS_BACKWARD);
				rightWheels(WHEELS_BACKWARD * slowMult);
			}

			wait1Msec(10); // let other tasks run
		}
		driveSpeed(WHEELS_FORWARD); // kill the momentum
	}

	wait1Msec(90);
	stopWheels();
}

void strafeInches(float inches) {
#warning "  sensors::strafeInches() not implemented"
}

void strafeRaw(int amount) {
#warning "  sensors::strafeRaw() untested"
	const float slowMult = .9;

	resetDriveEncoders();

	if (amount > 0) {
		// for strafing right
		strafeSpeed(STRAFE_RIGHT);
		while(getRightDriveEncoder() <= amount)
			wait1Msec(10); // let other tasks run
		strafeSpeed(STRAFE_LEFT); // kill the momentum
	}
	else {
		// for strafing left
		strafeSpeed(STRAFE_LEFT);
		while(getRightDriveEncoder() >= amount)
			wait1Msec(10); // let other tasks run
		strafeSpeed(STRAFE_RIGHT); // kill the momentum
	}

	wait1Msec(90);
	stopWheels();
}

void rotateDeg(float deg) {
	int rawValue = deg * ROBOT_ROTATION / 360;
	rotateRaw(rawValue);
}

void rotateRaw(int amount) {
	resetDriveEncoders();

	if (amount > 0) {
		turnSpeed(TURN_LEFT);
		while (getRightDriveEncoder() < amount)
			wait1Msec(10);
		turnSpeed(TURN_RIGHT);
	}
	else {
		turnSpeed(TURN_RIGHT);
		while (getRightDriveEncoder() > amount)
			wait1Msec(10);
		turnSpeed(TURN_LEFT);
	}

	wait1Msec(90);
	turnSpeed(0);
}

void setLiftPos(int position) {
	if (position < getLiftEncoder()) {
		liftSpeed(LIFT_DOWN);
		while (getLiftEncoder() > position)
			wait1Msec(10);
		liftSpeed(LIFT_UP);
		wait1Msec(90);
	}
	else {
		liftSpeed(LIFT_UP);
		while(getLiftEncoder() < position)
			wait1Msec(10);
		liftSpeed(LIFT_DOWN);
		wait1Msec(45); // since gravity helps slow down the lift, there must be a shorter wait time here
	}

	lockLift();
}

void setCapturePos(int position) {
	// #error "Test sensors::setCapturePos()"
	if (position < getCaptureEncoder()) {
		mobileCaptureSpeed(CAPTURE_RETRACT);
		while (getCaptureEncoder() > position)
			wait1Msec(10);
	}
	else {
		mobileCaptureSpeed(CAPTURE_EXTEND);
		while (getCaptureEncoder() < position)
			wait1Msec(10);
	}

	mobileCaptureSpeed(0);
}

<<<<<<< HEAD
task lockCapture() {
	static const int MOBILE_TARGET  = -370;
	static const int MOBILE_ZONE_SZ = 100;
=======
task lockMobile() {
	static const int MOBILE_TARGET  = 300;
	static const int MOBILE_ZONE_SZ = 50;
>>>>>>> 29dd72af9c3993e8c0c8cc386504597201a3a035
	if (!mobileCaptureIsLocked) {// only run once
		mobileCaptureIsLocked = true;
		while (mobileCaptureIsLocked) {
			if (getCaptureEncoder() < MOBILE_TARGET - MOBILE_ZONE_SZ)
				mobileCaptureSpeed(CAPTURE_EXTEND);
			else if (getCaptureEncoder() > MOBILE_TARGET + MOBILE_ZONE_SZ)
				mobileCaptureSpeed(CAPTURE_RETRACT);
			else
				mobileCaptureSpeed(0);
			wait1Msec(50);
		}
	}
}

void lockLift() {
	const static float liftMax    = 850; // the encoder value of the lift when it is at its highest point
	const static float liftPow    = 35; // the power imparted to the lift when it is at liftMax
	const static float liftPow0   = 85; // the sensor value at zero power
	const static float abruptness = 3; // !!must be positive and odd!! - the abruptness of the positive/ negetive switch (13+ is basically a step function)
	const static float denominator = liftMax - liftPow0;

	const int x = getLiftEncoder();
	const float numerator = x - liftPow0;
	const int sign = (numerator == 0)? 0: (abs(numerator/denominator)/(numerator/denominator));
	const int speed = liftPow * pow(abs(numerator / denominator), 1.0/abruptness) * sign;

	liftSpeed(speed);
}

int getLiftEncoder() {
	return -(SensorValue[liftEncoder]);
}

int getCaptureEncoder() {
	return -(SensorValue[mobileEncoder]);
}

void resetDriveEncoders() {
	SensorValue[leftEncoder]  = 0;
	SensorValue[rightEncoder] = 0;
}

int getRightDriveEncoder() {
	// right encoder returns negative values for forward
	return -(SensorValue[rightEncoder]);
}

int getLeftDriveEncoder() {
	return (SensorValue[leftEncoder]);
}

int getDriveEncoderAvg() {
	return (getRightDriveEncoder() + getLeftDriveEncoder()) / 2;
}

void resetGyro() {
	SensorType[gyroSens] = sensorNone;
	wait1Msec(10);
	SensorType[gyroSens] = sensorGyro;
}

int getGyro() {
	return SensorValue[gyroSens];
}

void resetSensors() {
	SensorValue[liftEncoder]   = 0;
	SensorValue[rightEncoder]  = 0;
	SensorValue[mobileEncoder] = 0;
	SensorValue[liftEncoder]   = 0;
	resetGyro();
}
