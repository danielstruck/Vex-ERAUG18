#ifndef _SENSORS_H_
#define _SENSORS_H_

#define WHEEL_DIAMETER           4.12
#define WHEEL_CIRCUMFERENCE      (3.1415 * WHEEL_DIAMETER)
#define WHEEL_ROTATION_VALUE     390
#define WHEEL_TO_WHEEL_DIAMETER  21
#define ROBOT_CIRCUMFRENCE       (3.1415 * WHEEL_TO_WHEEL_DIAMETER)
#define ROBOT_ROTATION           1900

#define ROTATE_RIGHT_1_DEG      -1
#define ROTATE_LEFT_1_DEG       -ROTATE_RIGHT_1_DEG

#define LIFT_HEIGHT_TOP          870
#define LIFT_HEIGHT_BOTTOM       50
#define LIFT_HEIGHT_CONE         LIFT_HEIGHT_BOTTOM
#define LIFT_HEIGHT_HIGH_GOAL    735
#define LIFT_HEIGHT_MOBILE       250

#define CAPTURE_EXTENDED  715
#define CAPTURE_TOP       (CAPTURE_EXTENDED/2)
#define CAPTURE_RETRACTED 50

// writes battery levels to LCD
void displayBatteryLevels();

// uses wheel encoders to drive a distance in inches
void driveInches(float inches);

void driveRaw(int amount);

// uses the gyro to rotate to deg (gyro value of 1 = 1/10 degree)
void rotateDeg(float deg);

// uses the wheel encoder's raw value to rotate
void rotateRaw(int amount);

// uses lift encoder to move the lift to position
void setLiftPos(int position);

// uses mobile capture encoder to move the mobile capture to position
void setCapturePos(int position);

task lockMobile();

void resetDriveEncoders();

int getDriveEncoderAvg();

int getRightEncoder();

int getLeftEncoder();

void resetGyro();

int getGyro();

int getLiftEncoder();

int getCaptureEncoder();

void resetSensors();

#include "sensors.c"
#endif // _SENSORS_H_
