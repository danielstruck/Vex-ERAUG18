
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
	
	int liftMax  = -850, // the encoder value of the lift when it is at its highest point
	    liftPow  = 35, // the power imparted to the lift when it is at liftMax
	    liftPow0 = -85, // the sensor value at zero power
		abruptness = 3; // !!must be positive and odd!! - the abruptness of the positive/ negetive switch (13+ is basically a step function)

	float numerator   = x - liftPow0;
	static const float denominator = liftMax - liftPow0;
	int speed = liftPow * pow(numerator / denominator, 1.0/abruptness);


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
