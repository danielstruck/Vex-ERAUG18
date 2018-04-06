#pragma config(UART_Usage, UART1, uartVEXLCD, baudRate19200, IOPins, None, None)
#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, in3,    gyroSens,       sensorGyro)
#pragma config(Sensor, dgtl2,  pistonTwo,      sensorDigitalOut)
#pragma config(Sensor, dgtl3,  pistonOne,      sensorDigitalOut)
#pragma config(Sensor, I2C_1,  leftEncoder,    sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Sensor, I2C_2,  rightEncoder,   sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Sensor, I2C_3,  mobileEncoder,  sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Sensor, I2C_4,  liftEncoder,    sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Motor,  port2,           liftRight,     tmotorVex393HighSpeed_MC29, openLoop, reversed, encoderPort, I2C_4)
#pragma config(Motor,  port3,           mobileCapture, tmotorVex393_MC29, openLoop, encoderPort, I2C_3)
#pragma config(Motor,  port4,           frontLeft,     tmotorVex393_MC29, openLoop, driveLeft, encoderPort, I2C_1)
#pragma config(Motor,  port5,           backLeft,      tmotorVex393_MC29, openLoop, driveLeft, encoderPort, I2C_1)
#pragma config(Motor,  port6,           backRight,     tmotorVex393_MC29, openLoop, driveRight, encoderPort, I2C_2)
#pragma config(Motor,  port7,           frontRight,    tmotorVex393_MC29, openLoop, driveRight, encoderPort, I2C_2)
#pragma config(Motor,  port8,           frictionDrum2, tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port9,           liftLeft,      tmotorVex393HighSpeed_MC29, openLoop, encoderPort, I2C_4)

#include "motion.h"
#include "motionPlus.h"
#include "sensors.h"

void stall();
void info(int line, const string s);

task main() {
	// test code here

}

void stall() {
	while ((int)nLCDButtons == 0)
		/* stall for button to be pressed */;
	while ((int)nLCDButtons != 0)
		/* stall for button to be released */;
}

void info(int line, const string s) {
	stopAllMotors();
	clearLCDLine(line);
	displayLCDString(line, 0, s);
	stall();
}
