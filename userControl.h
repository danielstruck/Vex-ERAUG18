#ifndef _USER_CONTROL_H_
#define _USER_CONTROL_H_

// drive controls
#define STRAFE_AXIS        vexRT[Ch4]
#define DIVE_AXIS          vexRT[Ch3]
#define ROTATE_AXIS        vexRT[Ch1]
// lift controls
#define LIFT_UP_BTN        vexRT[Btn5U]
#define LIFT_DOWN_BTN      vexRT[Btn5D]
// drum controls
#define DRUM_PULL_BTN      vexRT[Btn6U]
#define DRUM_PUSH_BTN      vexRT[Btn6D]
#define DRUM_IDLE_SPEED
// piston controls
#define PISTON_RETRACT_BTN vexRT[Btn8D]
#define PISTON_EXTEND_BTN  vexRT[Btn8U]
// mobile capture controls
#define MOBILE_LOCK_BTN    vexRT[Btn8L]
#define MOBILE_AXIS        vexRT[Ch2]


// usercontrol is already defined in the competition includes

// defines how the drive is controlled
void driveControl();

// defines how the lift is controlled
void liftControl();

// defines how the friction drums are controlled
void drumControl();

// defines how the pistons are controlled
void pistonControl();

// defines how the mobile capture is controlled
void mobileControl();


#include "userControl.c"
#endif // _USER_CONTROL_H_
