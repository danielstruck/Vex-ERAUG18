
void setPistons(int state) {
	if (state == PISTON_PULL) {
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
	const int x = SensorValue[liftEncoder];

  // quadratic
	//int speed = -5 - 0.06143791*x - 0.0000307574*x*x;
  // cubic
	int speed = -5 - 0.05198773*x + 0.00009384581*x*x + 1.579372*pow(10,-7)*x*x*x;

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

void frontWheels(int speed) {
	motor[frontLeft] = speed;
	motor[frontRight] = -speed;
}

void backWheels(int speed) {
	motor[backLeft] = speed;
	motor[backRight] = -speed;
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

void turnSpeed(int speed) {
	leftWheels(speed);
	rightWheels(-speed);
}
