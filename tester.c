#pragma config(UART_Usage, UART1, uartVEXLCD, baudRate19200, IOPins, None, None)
#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, in1,    gyroSens,       sensorGyro)
#pragma config(Sensor, dgtl2,  pistonTwo,      sensorDigitalOut)
#pragma config(Sensor, dgtl3,  pistonOne,      sensorDigitalOut)
#pragma config(Sensor, I2C_1,  leftEncoder,    sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_2,  leftMobileEncoder, sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_3,  rightEncoder,   sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_4,  rightMobileEncoder, sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_5,  liftEncoder,    sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Motor,  port2,           liftRight,     tmotorVex393HighSpeed_MC29, openLoop, reversed, encoderPort, I2C_4)
#pragma config(Motor,  port3,           mobileCapture, tmotorVex393_MC29, openLoop, encoderPort, I2C_3)
#pragma config(Motor,  port4,           frontLeft,     tmotorVex393_MC29, openLoop, driveLeft, encoderPort, I2C_1)
#pragma config(Motor,  port5,           backLeft,      tmotorVex393_MC29, openLoop, driveLeft, encoderPort, I2C_1)
#pragma config(Motor,  port6,           backRight,     tmotorVex393_MC29, openLoop, driveRight, encoderPort, I2C_2)
#pragma config(Motor,  port7,           frontRight,    tmotorVex393_MC29, openLoop, driveRight, encoderPort, I2C_2)
#pragma config(Motor,  port8,           frictionDrum2, tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port9,           liftLeft,      tmotorVex393HighSpeed_MC29, openLoop, encoderPort, I2C_4)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "motion.h"
//#include "motionPlus.h"
#include "sensors.h"
#include "autonBlue.h"

// waits until a LCD button is pressed
void stall();
// stalls, then waits 'secs' seconds
void countdown(int secs);
// displays 's' to the LCD on line 'line', then stalls
void info(int line, const string s);
void testAutonBlue();
void fullTestMotion();
void fullTestSensors();
void fullTestMotionPlus();

task main() {
	stall();
	lockCaptureStart();
	stall();
	setCapturePos(CAPTURE_EXTENDED);
	stall();
	//testAutonBlue();
	//fullTestMotion();
	//fullTestSensors();

	//while (1) {
	//	for (int i = 0; i <= 255; ++i) {
	//		displayLCDChar(0, i%15, (char)i);
	//		displayLCDNumber(1, i%15, i%10);
	//		wait1Msec(50);
	//	}
	//}
}

//================================================
//================= DEFINITIONS ==================
//================================================

void stall() {
	while ((int)nLCDButtons == 0) {
		/* wait for button to be pressed */
		wait1Msec(50);
	}
	while ((int)nLCDButtons != 0) {
		/* wait for button to be released */;
		wait1Msec(50);
	}
}

void info(int line, const string s) {
	clearLCDLine(line);
	displayLCDCenteredString(line, s);
	stall();
}

void countdown(int secs) {
	info(0, "countdown...");
	for (int i = secs; i > 0; --i) {
		clearLCDLine(0);
		displayLCDNumber(0, 0, i);
		wait1Msec(1000);
	}
}

void testAutonBlue() {
	displayBatteryLevels();

	stall();
	clearLCDLine(0);
	displayLCDCenteredString(0, "Test Blue Auton");

	setPistons(PISTON_RETRACT);
	liftSpeed(LIFT_UP);
	wait1Msec(500);
	mobileCaptureSpeed(CAPTURE_RETRACT);
	liftSpeed(0);
	wait1Msec(1000);
	mobileCaptureSpeed(0);
	countdown(3);
	setupAuton();
	autonBlue();
}

void fullTestMotion() {
#ifdef _MOTION_H_
	//=============================
	//========== MOTION ===========
	//=============================
	info(0, "motion.h");

	info(1, "PISTON_EXTEND");
	setPistons(PISTON_EXTEND);
	wait1Msec(1000);
	stopAllMotors();

	info(1, "PISTON_RETRACT");
	setPistons(PISTON_RETRACT);
	wait1Msec(1000);
	stopAllMotors();

	info(1, "DRUM_PULL");
	drumSpeed(DRUM_PULL);
	wait1Msec(1000);
	stopAllMotors();

	info(1, "DRUM_PUSH");
	drumSpeed(DRUM_PUSH);
	wait1Msec(1000);
	stopAllMotors();

	info(1, "DRUM_HOLD");
	drumSpeed(DRUM_HOLD);
	wait1Msec(1000);
	stopAllMotors();

	info(1, "LIFT_UP");
	liftSpeed(LIFT_UP);
	wait1Msec(1000);
	stopAllMotors();

	info(1, "CAPTURE_EXTEND");
	mobileCaptureSpeed(CAPTURE_EXTEND);
	wait1Msec(1000);
	stopAllMotors();

	info(1, "CAPTURE_RETRACT");
	mobileCaptureSpeed(CAPTURE_RETRACT);
	wait1Msec(1000);
	stopAllMotors();

	info(1, "LIFT_DOWN");
	liftSpeed(LIFT_DOWN);
	wait1Msec(1000);
	stopAllMotors();

	info(1, "WHEELS_FORWARD");
	driveSpeed(WHEELS_FORWARD);
	wait1Msec(1000);
	stopAllMotors();

	info(1, "WHEELS_BACKWARD");
	driveSpeed(WHEELS_BACKWARD);
	wait1Msec(1000);
	stopAllMotors();

	info(1, "STRAFE_RIGHT");
	strafeSpeed(STRAFE_RIGHT);
	wait1Msec(1000);
	stopAllMotors();

	info(1, "STRAFE_LEFT");
	strafeSpeed(STRAFE_LEFT);
	wait1Msec(1000);
	stopAllMotors();

	info(1, "TURN_LEFT");
	turnSpeed(TURN_LEFT);
	wait1Msec(1000);
	stopAllMotors();

	info(1, "TURN_RIGHT");
	turnSpeed(TURN_RIGHT);
	wait1Msec(1000);
	stopAllMotors();
#endif // _MOTION_H_
}

void fullTestSensors() {
#ifdef _SENSORS_H_
//=============================
//========== SENSORS ==========
//=============================
	info(0, "sensors.h");

	info(1, "drive 12 inches FORW");
	driveInches(12, 1);
	wait1Msec(1000);

	info(1, "drive 12 inches BACK");
	driveInches(-12, 1);
	wait1Msec(1000);

	info(1, "strafe 12 inches R");
	strafeInches(12, 1);
	wait1Msec(1000);

	info(1, "strafe 12 inches L");
	strafeInches(-12, 1);
	wait1Msec(1000);

	info(1, "rotate 90 degrees R");
	rotateDeg(ROTATE_RIGHT_1_DEG * 90, 1);
	wait1Msec(1000);

	info(1, "rotate 90 degrees L");
	rotateDeg(ROTATE_LEFT_1_DEG * 90, 1);
	wait1Msec(1000);

	info(1, "LIFT_HEIGHT_TOP");
	setLiftPos(LIFT_HEIGHT_TOP);
	wait1Msec(1000);

	info(1, "LIFT_HEIGHT_BOTTOM");
	setLiftPos(LIFT_HEIGHT_BOTTOM);
	wait1Msec(1000);

	info(1, "LIFT_HEIGHT_CONE");
	setLiftPos(LIFT_HEIGHT_CONE);
	wait1Msec(1000);

	info(1, "LIFT_HEIGHT_HIGH_GOAL");
	setLiftPos(LIFT_HEIGHT_HIGH_GOAL);
	wait1Msec(1000);

	info(1, "LIFT_HEIGHT_MOBILE");
	setLiftPos(LIFT_HEIGHT_MOBILE);
	wait1Msec(1000);

	info(1, "CAPTURE_TOP");
	setCapturePos(CAPTURE_TOP);
	wait1Msec(1000);

	info(1, "CAPTURE_EXTENDED");
	setCapturePos(CAPTURE_EXTENDED);
	wait1Msec(1000);

	info(1, "CAPTURE_RETRACTED");
	setCapturePos(CAPTURE_RETRACTED);
	wait1Msec(1000);

	info(1, "lock capture");
	lockCaptureStart();
	wait1Msec(1000);
#endif // _SENSORS_H_
}

void fullTestMotionPlus() {
#ifdef _MOTION_PLUS_H_
//=============================
//========== MOTION + =========
//=============================
	startTask(motionPlusUpdater);

	info(0, "motionPlus.h");
	info(1, "LIFT_HEIGHT_HIGH_GOAL");
	momentumMove(&liftProperties, LIFT_HEIGHT_HIGH_GOAL);
	displayLCDCenteredString(0, "actual");
	displayLCDCenteredString(1, "target");
	stall();
	displayLCDNumber(0, 0, getLiftEncoder());
	displayLCDNumber(0, 0, LIFT_HEIGHT_HIGH_GOAL);
	stall();

	info(0, "motionPlus.h");
	info(1, "CAPTURE_TOP");
	momentumMove(&captureProperties, CAPTURE_TOP);
	displayLCDCenteredString(0, "actual");
	displayLCDCenteredString(1, "target");
	stall();
	displayLCDNumber(0, 0, getCaptureEncoder());
	displayLCDNumber(0, 0, CAPTURE_TOP);
	stall();

	info(0, "motionPlus.h");
	info(1, "drive raw 2500");
	driveRaw(2500);
	momentumStop();
	displayLCDCenteredString(0, "actual");
	displayLCDCenteredString(1, "target");
	stall();
	displayLCDNumber(0, 0, getDriveEncoderAvg());
	displayLCDNumber(0, 0, 2500);
	stall();
#endif // _MOTION_PLUS_H_
}
