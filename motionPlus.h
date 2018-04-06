#ifndef _MOTION_PLUS_H_
#define _MOTION_PLUS_H_

typedef struct {
  float lastPosition; // last recorded value of the sensor
  float lastTime;     // the time that lastPosition was recorded
  float velocity;     // the velocity of the sensor, based on the difference in position and time
  float mass;         // the mass of the part
  int *motorPorts;    // a list of ports accociated with the sensor
  int nPorts;         // the length of *motorPorts
  int sensorPort;     // the index of the sensor of the part
  bool rotates;       // whether the sensor measures rotation (a joint) or linearly (a wheel)
} properties_t;
#define PLUS_TIMER T4
#define PLUS_CURRENT_TIME time1(PLUS_TIMER)

static void updateVelocity(properties_t *p);
task motionPlusUpdater();
float momentum(properties_t p);
void momentumStop(properties_t p);
void momentumMove(properties_t p, float targetValue);
/*
  =====================================
  =============SETUP STUFF=============
  =====================================
*/
properties_t* buildProperties(properties_t *p, float currentPosition, float mass,
                              int *motorPorts, int nPorts, int sensorPort, bool rotates);
static void setupProperties(properties_t *leftDrive, properties_t *rightDrive,
                            properties_t *lift, properties_t *capture);

#include "motionPlus.c"
#endif // _MOTION_PLUS_H_
