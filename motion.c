
void setPistons(int pistonState) {
	if (pistonState == PISTON_PULL) {
		SensorValue[pistonOne] = PISTON_PULL;
		SensorValue[pistonTwo] = PISTON_PULL;
	}
	else {
		SensorValue[pistonOne] = PISTON_PUSH;
		SensorValue[pistonTwo] = PISTON_PUSH;
	}
}

void frictionDrumSpeed(int speed) {
	motor[frictionDrum2] = speed;
}

void liftSpeed(int speed) {
	motor[liftLeft] = speed;
	motor[liftRight] = speed;
}

void lockLift() {
	int x = SensorValue[liftEncoder]; // x value for quad
	int speed = -5 - 0.06143791*x - 0.0000307574*x*x;
	liftSpeed(speed);
}

void stopWheels() {
	motor[frontLeft] = 0;
	motor[frontRight] = 0;
	motor[backRight] = 0;
	motor[backLeft] = 0;
}

void mobileCaptureSpeed(int speed) {
	motor[mobileCapture] = speed;
}

void driveSpeed(int speed) {
	motor[frontLeft] = -speed;
	motor[backLeft] = -speed;
	motor[frontRight] = speed;
	motor[backRight] = speed;
}

void turnSpeed(int speed) {
	motor[frontLeft] = speed;
	motor[frontRight] = speed;
	motor[backRight] = -speed;
	motor[backLeft] = -speed;
}
