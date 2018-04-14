#ifndef _AUTON_BLUE_H_
#define _AUTON_BLUE_H_

void autonBlue();

// auton steps
void b_scorePreloadOnStationaryGoal();
void b_pickUpRightCone();
void b_putConeOnMobileBase();
void b_scoreMobileBase();

// other definitions
void depositCone();
void collectCone();

#include "autonBlue.c"
#endif // _AUTON_BLUE_H_


