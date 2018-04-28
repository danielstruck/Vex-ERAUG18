#include "motion.h"
#include "tools.h"


void displayBatteryLevels() {
	string batteryLevel;
	sprintf(batteryLevel, "Primary: %.2fV", nImmediateBatteryLevel/1000.0);
	displayLCDCenteredString(0, batteryLevel);
	batteryLevel = "";
	sprintf(batteryLevel, "Backup: %.2fV", BackupBatteryLevel/1000.0);
	displayLCDCenteredString(1, batteryLevel);
}

void driveInches(float inches, float mult) {
	const float rotationsRequired = inches / (1.414 * WHEEL_CIRCUMFERENCE);
	const int rawValue = rotationsRequired * WHEEL_ROTATION_VALUE;

	driveRaw(rawValue, mult);
}

void driveRaw(int amount, float mult) {
	static float slowMult = .82; // how much slower the faster wheel will move vs the slower wheel
	static float criticalDifference = 15;
	static const float waitTimeSec = .001;
	
	resetDriveEncoders();
	
	if (amount != 0) {
		int baseSpeed = signum(amount) * mult * WHEELS_FORWARD;
		
		
		const float waitTime = abs(3 * amount / 1000);
		for (float i = 0; i < waitTime && abs(getDriveEncoderAvg()) < abs(amount); i += waitTimeSec) {
			const float diff = getLeftDriveEncoder() - getRightDriveEncoder();
			int speedL = baseSpeed;
			int speedR = baseSpeed;

			// if (diff > 0)      // left is too fast
				// speedL *= 1 - abs(diff/criticalDifference);//slowMult;
			// else if (diff < 0) // right is too fast
				// speedR *= 1 - abs(diff/criticalDifference);//slowMult;

			rightWheels(speedR);
			leftWheels(speedL);

			wait1Msec(waitTimeSec * 1000);
		}
		
		driveSpeed(-baseSpeed); // kill the momentum
		wait1Msec(90);
	}
	stopWheels();

/*
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
*/
}

void strafeInches(float inches, float mult) {
	const float rotationsRequired = inches / (1.414 * WHEEL_CIRCUMFERENCE);
	const int rawValue = rotationsRequired * WHEEL_ROTATION_VALUE;

	strafeRaw(rawValue, mult);
}

void strafeRaw(int amount, float mult) {
	resetDriveEncoders();

	if (amount != 0) {
		int baseSpeed = signum(amount) * mult * STRAFE_RIGHT;

		while (abs(getRightDriveEncoder()) < abs(amount)) {
			strafeSpeed(baseSpeed);
			wait1Msec(10);
		}

		strafeSpeed(-baseSpeed); // kill the momentum
		wait1Msec(90);
	}
	stopWheels();

/*
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
*/
}

void rotateDeg(float deg, float mult) {
	int rawValue = deg * ROBOT_ROTATION / 360;
	rotateRaw(rawValue, mult);
}

void rotateRaw(int amount, float mult) {
	resetDriveEncoders();

	if (amount != 0) {
		int baseSpeed = signum(amount) * mult * TURN_LEFT;

		while (abs(getLeftDriveEncoder()) < abs(amount)) {
			turnSpeed(baseSpeed);
			wait1Msec(10);
		}

		turnSpeed(-baseSpeed);
		wait1Msec(90);
	}
	stopWheels();

/*
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
	stopWheels();
*/
}

void setLiftPos(int position) {
	// clearLCDLine(0);
	// displayLCDNumber(0, 5, position);
	// if (position != 0) {
		// const int dist = position - getLiftEncoder();
	// clearLCDLine(1);
	// displayLCDNumber(1, 5, dist);
		// int baseSpeed = signum(dist) * LIFT_UP;

		// liftSpeed(baseSpeed);
		// while (abs(getLiftEncoder()) < abs(position))
			// wait1Msec(10);

		// liftSpeed(-baseSpeed);
		// if (signum(baseSpeed) == signum(LIFT_UP))
			// wait1Msec(90);
		// else
			// wait1Msec(45);// since gravity helps slow down the lift, there must be a shorter wait time here

		// lockLift();
	// }


	if (position < getLiftEncoder()) {
		while (getLiftEncoder() > position) {
			liftSpeed(LIFT_DOWN);
			wait1Msec(10);
		}
		liftSpeed(LIFT_UP);
		wait1Msec(90);
	}
	else {
		while(getLiftEncoder() < position) {
			liftSpeed(LIFT_UP);
			wait1Msec(10);
		}
		liftSpeed(LIFT_DOWN);
		wait1Msec(45); // since gravity helps slow down the lift, there must be a shorter wait time here
	}

	lockLift();
}

void setCapturePos(int position) {
	// if (position != 0) {
		// const int dist = position - getCaptureEncoder();
		// int baseSpeed = signum(position) * CAPTURE_EXTEND;

		// mobileCaptureSpeed(baseSpeed);
		// while (abs(getCaptureEncoder()) < abs(position))
			// wait1Msec(10);

		// mobileCaptureSpeed(0);
	// }


	if (position < getCaptureEncoder()) {
		while (getCaptureEncoder() > position) {
			mobileCaptureSpeed(CAPTURE_RETRACT);
			wait1Msec(10);
		}
	}
	else {
		while (getCaptureEncoder() < position) {
			mobileCaptureSpeed(CAPTURE_EXTEND);
			wait1Msec(10);
		}
	}

	mobileCaptureSpeed(0);

}

void lockCaptureStart() {
	startTask(lockCapture);
}

void lockCaptureStop() {
	mobileCaptureIsLocked = false;
}

task lockCapture() {
	static const int SIZE = 50;

	if (!mobileCaptureIsLocked) { // only run once
		mobileCaptureIsLocked = true;
		for (float i = 0; i < 3 && mobileCaptureIsLocked; i += .05) {
			if (getCaptureEncoder() < CAPTURE_TOP - SIZE) {
				if (getCaptureEncoder() > CAPTURE_TOP - SIZE/2)
					mobileCaptureSpeed(CAPTURE_EXTEND * .8);
				else
					mobileCaptureSpeed(CAPTURE_EXTEND);
			}
			else if (getCaptureEncoder() > CAPTURE_TOP + SIZE) {
				if (getCaptureEncoder() < CAPTURE_TOP + SIZE/2)
					mobileCaptureSpeed(CAPTURE_RETRACT * .8);
				else
					mobileCaptureSpeed(CAPTURE_RETRACT);
			}
			else {
				i = 0;
				mobileCaptureSpeed(0);
			}
			
			wait1Msec(50);
		}
	}
}

void lockLift() {
	const static float liftMax    = 850; // the encoder value of the lift when it is at its highest point
	const static float liftPow    = 20; // the power imparted to the lift when it is at liftMax
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
	return -SensorValue[liftEncoder];
}

int getCaptureEncoder() {
	return (-SensorValue[rightMobileEncoder] + SensorValue[leftMobileEncoder]) / 2;
}

void resetDriveEncoders() {
	SensorValue[leftEncoder]  = 0;
	SensorValue[rightEncoder] = 0;
}

int getRightDriveEncoder() {
	// right encoder returns negative values for forward
	return -SensorValue[rightEncoder];
}

int getLeftDriveEncoder() {
	return SensorValue[leftEncoder];
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
	SensorValue[liftEncoder]        = 0;
	SensorValue[rightEncoder]       = 0;
	SensorValue[leftMobileEncoder]  = 0;
	SensorValue[rightMobileEncoder] = 0;
	SensorValue[liftEncoder]        = 0;
	resetGyro();
}
