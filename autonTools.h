#ifndef _AUTON_TOOLS_H_
#define _AUTON_TOOLS_H_


// pushes a cone out of the friction drums
void depositCone();

// pulls a cone into the friction drums
void collectCone();

// waits some time for the robot to stabilize
void waitForStabilize();


#include "autonTools.c"
#endif // _AUTON_TOOLS_H_
