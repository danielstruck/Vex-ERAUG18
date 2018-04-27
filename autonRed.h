#ifndef _AUTON_RED_H_
#define _AUTON_RED_H_


// the auton to be used when playing for the RED side
void autonRed();

// ====== step definitions ======
void r_scorePreloadOnStationaryGoal();
void r_pickUpRightCone();
void r_putConeOnMobileBase();
void r_scoreMobileBase();

// =======other definitions=======


#include "autonRed.c"
#endif // _AUTON_RED_H_
