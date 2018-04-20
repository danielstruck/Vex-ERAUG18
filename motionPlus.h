#ifndef _MOTION_PLUS_H_
#define _MOTION_PLUS_H_


#define PLUS_TIMER        T4
#define PLUS_CURRENT_TIME time1(PLUS_TIMER)
/* !CAUTION!:
 *   wait times too large will cause velocities to be too unpredictable, while values too small may not register a sufficient change in position or time
**/
#define PLUS_TIMER_WAIT   100


typedef struct {
  float lastPosition; // last recorded value of the sensor
  float lastTime;     // the time that lastPosition was recorded
  float velocity;     // the velocity of the sensor, based on the difference in position and time
  float mass;         // the mass of the part (lbs)
  int *motorPorts;    // a list of ports associated with the sensor
  int nPorts;         // the length of *motorPorts
  int sensorPort;     // the index of the sensor of the part
  bool rotates;       // true if the part is not uniform about the joint (like an arm)
} properties_t;

properties_t *leftDriveProperties, *rightDriveProperties, *liftProperties, *captureProperties;


// setup properties for all encoders, clears 'PLUS_TIMER', and continuously updates velocities
task motionPlusUpdater();

// updates the velocity for the property_t '*p'
static void updateVelocity(properties_t *p);

// returns the momentum, calculated by v*m
float momentum(properties_t p);

// applies decelerating power to the motor in 'p' according to the value of 'momentum(p)'
void momentumStop(properties_t p);

// move the part in '*p' close to the target position, then calls 'momentumStop()'
void momentumMove(properties_t p, float targetValue);

/*
  =====================================
  =============SETUP STUFF=============
  =====================================
*/

// constructs a properties_t based on the arguments
properties_t* buildProperties(properties_t *p, float currentPosition, float mass, int *motorPorts,
                              int nPorts, int sensorPort, bool rotates);

// constructs all properties_t arguments based on defaults
static void setupProperties(properties_t *leftDrive, properties_t *rightDrive, properties_t *lift,
                            properties_t *capture);


#include "motionPlus.c"
#endif // _MOTION_PLUS_H_
