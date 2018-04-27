#ifndef _MOTION_H_
#define _MOTION_H_


// piston states
#define PISTON_EXTEND     1
#define PISTON_RETRACT    (1 - PISTON_EXTEND)
// drum speeds
#define DRUM_PULL         127
#define DRUM_PUSH        -DRUM_PULL
#define DRUM_HOLD         (DRUM_PULL * .1)
// lift speeds
#define LIFT_UP           127
#define LIFT_DOWN        -LIFT_UP
// capture speeds
#define CAPTURE_EXTEND    127
#define CAPTURE_RETRACT  -CAPTURE_EXTEND
// drive speeds
#define WHEELS_FORWARD    127
#define WHEELS_BACKWARD  -WHEELS_FORWARD
// strafe speeds
#define STRAFE_REAR_MULT  .85
#define STRAFE_RIGHT      127
#define STRAFE_LEFT      -STRAFE_RIGHT
// turn speeds
#define TURN_LEFT        -127
#define TURN_RIGHT       -TURN_LEFT


// sets the pistons' state
void setPistons(int state);

// sets the friction drum's speed
void drumSpeed(int speed);

// sets the lift speed
void liftSpeed(int speed);

// sets the mobile capture speed
void mobileCaptureSpeed(int speed);

void flSpeed(int speed);
void blSpeed(int speed);
void frSpeed(int speed);
void brSpeed(int speed);

// sets the front drive wheels' speed
void frontWheels(int speed);

// sets the back drive wheels' speed
void backWheels(int speed);

// sets the left drive wheels' speed
void leftWheels(int speed);

// sets the right drive wheels' speed
void rightWheels(int speed);

// sets the speed for the left and right wheels
void driveSpeed(int speed);

// sets the speed for the front and back wheels
void strafeSpeed(int speed);

// sets the left wheels to speed and the right wheels to -speed
void turnSpeed(int speed);

// sets all drive wheels' speed to zero
void stopWheels();


#include "motion.c"
#endif // _MOTION_H_
