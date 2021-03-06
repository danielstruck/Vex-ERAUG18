#ifndef _AUTON_BLUE_H_
#define _AUTON_BLUE_H_


// the auton to be used when playing for the BLUE side
void autonBlue();

// ====== step definitions ======
void b_scorePreloadOnStationaryGoal();
void b_pickUpRightCone();
void b_putConeOnMobileBase();
void b_scoreMobileBase();

// =======other definitions=======


#include "autonBlue.c"
#endif // _AUTON_BLUE_H_
