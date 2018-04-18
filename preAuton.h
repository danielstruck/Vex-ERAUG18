#ifndef _PRE_AUTON_H_
#define _PRE_AUTON_H_


#include "sensors.h"


// stores what auton the user wants to use
int selectedAuton;

// string representation of the autons
const string autonNames[] = {"default", "blue", "red", "skills"};


// pre_auton() is already defined in the competition includes

// waits for user to select an auton. for actual commands, see definition of selectAuton()
void selectAuton();

#include "preAuton.c"
#endif // _PRE_AUTON_H_
