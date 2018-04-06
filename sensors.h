#ifndef _SENSORS_H_
#define _SENSORS_H_

#define WHEEL_DIAMETER 4
#define WHEEL_CIRCUMFERENCE (3.1415 * WHEEL_DIAMETER/2)

void driveIn(float inches);
void driveRaw(int amount);
void rotateDeg(float deg); // degrees is a system value
void rotateRaw(int amount);
void setLiftPos(int position);
void setMobileCapturePos(int position);
void lockLift();

#include "sensors.c"
#endif // _SENSORS_H_
