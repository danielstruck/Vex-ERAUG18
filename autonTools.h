#ifndef _AUTON_TOOLS_H_
#define _AUTON_TOOLS_H_


// pushes a cone out of the friction drums
void depositCone();

// pulls a cone into the friction drums
void collectCone();

// waits some time for the robot to stabilize
void waitForStabilize();

// drives for the specified inches then waits for stabilize
void autonDrive(float inches);

// rotates for the specified degrees then waits for stabilize
void autonRotate(float degrees);

// strafes for the specified degrees then waits for stabilize
void autonStrafe(float inches);


#include "autonTools.c"
#endif // _AUTON_TOOLS_H_
