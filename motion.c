
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

void frontWheels(int speed) {
	motor[frontLeft]  = speed;
	motor[frontRight] = speed;
}

void backWheels(int speed) {
	motor[backLeft]  = speed;
	motor[backRight] = speed;
}

void leftWheels(int speed) {
	motor[frontLeft] = speed;
	motor[backLeft]  = speed;
}

void rightWheels(int speed) {
	motor[frontRight] = -speed;
	motor[backRight]  = -speed;
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
	motor[frontLeft]  = 0;
	motor[frontRight] = 0;
	motor[backRight]  = 0;
	motor[backLeft]   = 0;
}
