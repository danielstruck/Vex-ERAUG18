#include "motion.h"
#include "tools.h"


task motionPlusUpdater() {
	setupProperties(leftDriveProperties, rightDriveProperties, liftProperties, captureProperties);

	clearTimer(PLUS_TIMER); // clear timer after building all properties
	while (true) {
		// update velocities
		updateVelocity(leftDriveProperties);
		updateVelocity(rightDriveProperties);
		updateVelocity(liftProperties);
		updateVelocity(captureProperties);

		// let other tasks work
		wait1Msec(PLUS_TIMER_WAIT);
	}
}

static void updateVelocity(properties_t *p) {
	const float currentPosition = SensorValue[p->sensorPort];
	const float currentTime     = PLUS_CURRENT_TIME;

	// update the velocity
	p->velocity = (currentPosition - p->lastPosition)/(currentTime - p->lastTime);

	// current values are now previous values
	p->lastPosition = currentPosition;
	p->lastTime = currentTime;
}

float momentum(properties_t p) {
	return p.velocity * p.mass;
}

void momentumStop(properties_t p) {
#warning "    motionPlus::momentumStop() not implemented"
	// more power to motor as momentum increases -- account for rotating parts
}

void momentumMove(properties_t p, float targetValue) {
#warning "    motionPlus::momentumMove() not implemented"
	// moves part to targetValue, then calls momentumStop()
}

/*
=====================================
=============SETUP STUFF=============
=====================================
*/

properties_t* buildProperties(properties_t *p, float currentPosition, float mass, int *motorPorts,
int nPorts, int sensorPort, bool rotates){

	p->lastPosition = currentPosition;
	p->lastTime     = PLUS_CURRENT_TIME;
	p->mass         = mass;
	p->motorPorts   = motorPorts;
	p->nPorts       = nPorts;
	p->sensorPort   = sensorPort;
	p->rotates      = rotates;

	return p;
}

static void setupProperties(properties_t *leftDrive, properties_t *rightDrive, properties_t *lift, properties_t *capture) {

	// initial drive positions
	int leftDrivePos       = SensorValue[leftEncoder],
		rightDrivePos      = SensorValue[rightEncoder],
		liftPos            = SensorValue[liftEncoder],
		capturePos         = SensorValue[mobileEncoder];

	// part masses (lbs)
	int leftDriveMass      = 16;
	int rightDriveMass     = 16;
	int liftMass           = 2.5;
	int captureMass        = .1;

	// motor ports
	int leftDrivePorts[]   = {backLeft, frontLeft};
	int rightDrivePorts[]  = {backRight, frontRight};
	int liftPorts[]        = {liftLeft, liftRight};
	int capturePorts[]     = {mobileCapture};

	// number of motors
	int leftDriveNPorts    = 2;
	int rightDriveNPorts   = 2;
	int liftNPorts         = 2;
	int captureNPorts      = 1;

	// sensor ports
	int leftDriveSensor    = leftEncoder;
	int rightDriveSensor   = rightEncoder;
	int liftSensor         = liftEncoder;
	int captureSensor      = mobileEncoder;

	// part uniform about joint
	bool leftDriveRotates  = false;
	bool rightDriveRotates = false;
	bool liftRotates       = true;
	bool captureRotates    = true;

	buildProperties(leftDrive,   leftDrivePos,  leftDriveMass,  leftDrivePorts,  leftDriveNPorts,  leftDriveSensor,  leftDriveRotates);
	buildProperties(rightDrive,  rightDrivePos, rightDriveMass, rightDrivePorts, rightDriveNPorts, rightDriveSensor, rightDriveRotates);
	buildProperties(lift,        liftPos,       liftMass,       liftPorts,       liftNPorts,       liftSensor,       liftRotates);
	buildProperties(capture,     capturePos,    captureMass,    capturePorts,    captureNPorts,    captureSensor,    captureRotates);
}
