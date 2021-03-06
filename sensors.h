#ifndef _SENSORS_H_
#define _SENSORS_H_


// wheel constants
#define WHEEL_DIAMETER           4.12
#define WHEEL_CIRCUMFERENCE      (3.1415 * WHEEL_DIAMETER)
#define WHEEL_ROTATION_VALUE    (760)
// #define WHEEL_ROTATION_VALUE     (390)
// drive constants
#define WHEEL_TO_WHEEL_DIAMETER  21
#define ROBOT_CIRCUMFRENCE       (3.1415 * WHEEL_TO_WHEEL_DIAMETER)
#define ROBOT_ROTATION           3120
// rotation constants
#define ROTATE_RIGHT_1_DEG      -1
#define ROTATE_LEFT_1_DEG       -ROTATE_RIGHT_1_DEG
// lift positions
#define LIFT_HEIGHT_TOP          760
#define LIFT_HEIGHT_BOTTOM       50
#define LIFT_HEIGHT_CONE         LIFT_HEIGHT_BOTTOM
#define LIFT_HEIGHT_HIGH_GOAL    735
#define LIFT_HEIGHT_MOBILE       280
#define LIFT_HEIGHT_FEEDER       300
#define LIFT_HEIGHT_FEEDER_WAIT  400
// mobile capture positions
#define CAPTURE_EXTENDED         680
#define CAPTURE_TOP              370
#define CAPTURE_RETRACTED        50
// strafe constants
#define STRAFE_RIGHT_1_INCH      1
#define STRAFE_LEFT_1_INCH      -STRAFE_RIGHT_1_INCH


// control variable for task lockCapture(); - must be global since it is accessed by multiple functions
bool mobileCaptureIsLocked;


// displays battery levels on LCD
void displayBatteryLevels();

// uses wheel encoders to drive a distance in inches
void driveInches(float inches, float mult);

// rotates the wheels until the average encoder value has magnitude greater than amount
void driveRaw(int amount, float mult);

// uses wheel encoders to strafe a distance in inches
void strafeInches(float inches, float mult);

// rotates the wheels until the average encoder value has magnitude greater than amount
void strafeRaw(int amount, float mult);

// uses the gyro to rotate to deg (gyro value of 1 = 1/10 degree)
void rotateDeg(float deg, float mult);

// uses the wheel encoder's raw value to rotate
void rotateRaw(int amount, float mult);

// uses lift encoder to move the lift to position
void setLiftPos(int position);

// uses mobile capture encoder to move the mobile capture to position
void setCapturePos(int position);

// starts task lockCapture() with startTask, for convenience
void lockCaptureStart();

// stops task lockCapture() by setting 'mobileCaptureIsLocked' to false, for convenience
void lockCaptureStop();

// locks the mobile capture, call with startTask()
task lockCapture();

// calculates the lock-lift-speed based on a smooth nth root function, n is odd
void lockLift();

// returns the value of the lift encoder, positive is up
int getLiftEncoder();

// returns the value of the capture encoder, positive is extend
int getCaptureEncoder();

// sets the drive encoder values to zero
void resetDriveEncoders();

// returns the value of the right drive encoder, positive is forward
int getRightDriveEncoder();

// returns the value of the left drive encoder, positive is forward
int getLeftDriveEncoder();

// returns the average value of the drive encoders
int getDriveEncoderAvg();

// sets the gyro's value to zero
void resetGyro();

// returns the value of the gyro
int getGyro();

// resets all encoders on the robot and the gyro
void resetSensors();


#include "sensors.c"
#endif // _SENSORS_H_
