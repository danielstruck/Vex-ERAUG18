#ifndef _AUTON_TOOLS_H_
#define _AUTON_TOOLS_H_


#define BLUE  1
#define RED  -BLUE
#define DRIVE_INCHES_MULT   .5
#define ROTATE_DEGREES_MULT .45


// pushes a cone out of the friction drums
void depositCone();

// pulls a cone into the friction drums
void collectCone();

// waits some time for the robot to stabilize
void waitForStabilize();

// drives for the specified inches then waits for stabilize
void autonDrive(float inches, float mult);

// rotates for the specified degrees then waits for stabilize
void autonRotate(float degrees, float mult);

// strafes for the specified degrees then waits for stabilize
void autonStrafe(float inches, float mult);

// does setup for all autons
void setupAuton();


#include "autonTools.c"
#endif // _AUTON_TOOLS_H_
