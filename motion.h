#ifndef _MOTION_H_
#define _MOTION_H_

#define PISTON_PUSH      1
#define PISTON_PULL      (1 - PISTON_PUSH)
#define DRUM_PULL       -127
#define DRUM_PUSH       -DRUM_PULL
#define DRUM_HOLD        (DRUM_PULL * .1)
#define LIFT_UP          127
#define LIFT_DOWN       -LIFT_UP
#define CAPTURE_EXTEND   127
#define CAPTURE_RETRACT -CAPTURE_EXTEND
#define WHEELS_FORWARD   127
#define WHEELS_BACKWARD -WHEELS_FORWARD
#define TURN_LEFT        127
#define TURN_RIGHT      -TURN_LEFT

void setPistons(int state);
void frictionDrumSpeed(int speed);
void liftSpeed(int speed);
void lockLift();
void driveSpeed(int speed);
void turnSpeed(int speed);
void stopWheels();
void mobileCaptureSpeed(int speed);

#include "motion.c"
#endif // _MOTION_H_
