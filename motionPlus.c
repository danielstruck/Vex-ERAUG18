
task motionPlusUpdater() {
  properties_t *leftDrive, *rightDrive, *lift, *capture;
  setupProperties(leftDrive, rightDrive, lift, capture);

  clearTimer(PLUS_TIMER); // clear timer after building all properties
  while (true) {
    // update velocities
    updateVelocity(leftDrive);
    updateVelocity(rightDrive);
    updateVelocity(lift);
    updateVelocity(capture);

    // let other tasks work
    wait1Msec(100);
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
properties_t* buildProperties(properties_t *p, float currentPosition, float mass,
                              int *motorPorts, int nPorts, int sensorPort, bool rotates) {

  p->lastPosition = currentPosition;
  p->lastTime     = PLUS_CURRENT_TIME;
  p->mass         = mass;
  p->motorPorts   = motorPorts;
  p->nPorts       = nPorts;
  p->sensorPort   = sensorPort;
  p->rotates      = rotates;

  return p;
}

static void setupProperties(properties_t *leftDrive, properties_t *rightDrive,
                            properties_t *lift, properties_t *capture) {

	int leftDrivePos      = SensorValue[leftEncoder],
	    rightDrivePos     = SensorValue[rightEncoder],
	    liftPos           = SensorValue[liftEncoder],
	    capturePos        = SensorValue[mobileEncoder];

#error "    motionPlus: mass not implemented"
	int  leftDriveMass     = -1,
	     rightDriveMass    = -1,
	     liftMass          = -1,
	     captureMass       = -1;

	int  leftDrivePorts[]  = {backLeft,frontLeft},
	     rightDrivePorts[] = {backRight, frontRight},
	     liftPorts[]       = {liftLeft, liftRight},
	     capturePorts[]    = {mobileCapture};

	int  leftDriveNPorts   = 2,
	     rightDriveNPorts  = 2,
	     liftNPorts        = 2,
	     captureNPorts     = 1;

	int  leftDriveSensor   = leftEncoder,
	     rightDriveSensor  = rightEncoder,
	     liftSensor        = liftEncoder,
	     captureSensor     = mobileEncoder;

	bool leftDriveRotates  = false,
	     rightDriveRotates = false,
	     liftRotates       = true,
	     captureRotates    = true;

  buildProperties(leftDrive,   leftDrivePos,  leftDriveMass,  leftDrivePorts,  leftDriveNPorts,  leftDriveSensor,  leftDriveRotates);
  buildProperties(rightDrive,  rightDrivePos, rightDriveMass, rightDrivePorts, rightDriveNPorts, rightDriveSensor, rightDriveRotates);
  buildProperties(lift,        liftPos,       liftMass,       liftPorts,       liftNPorts,       liftSensor,       liftRotates);
  buildProperties(capture,     capturePos,    captureMass,    capturePorts,    captureNPorts,    captureSensor,    captureRotates);
}
