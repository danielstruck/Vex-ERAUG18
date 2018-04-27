#ifndef _AUTON_SKILLS_H_
#define _AUTON_SKILLS_H_


// the auton to be used in the skills challenge
void autonSkills();

// ====== step definitions ======
void s_moveToMobileGoal();
void s_collectMobileGoal();
void s_moveToFeeder();
void s_collectFedCones();
void s_scoreMobileGoal();

// =======other definitions=======
void s_depositFeederCone();


#include "autonSkills.c"
#endif // _AUTON_SKILLS_H_
