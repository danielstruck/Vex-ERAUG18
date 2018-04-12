#ifndef _SENSORS_H_
#define _SENSORS_H_

#define WHEEL_DIAMETER       4.12
const float WHEEL_CIRCUMFERENCE = (3.1415 * WHEEL_DIAMETER);
#define WHEEL_ROTATION_VALUE 390

void driveInches(float inches);
void driveRaw(int amount);
void rotateDeg(float deg); // degrees is a system value
void rotateRaw(int amount);
void setLiftPos(int position);
void setMobileCapturePos(int position);

void resetDriveEncoders();
int getDriveEncoderAvg();
int getRightEncoder();
int getLeftEncoder();
void resetGyro();
int getGyro();

#include "sensors.c"
#endif // _SENSORS_H_
