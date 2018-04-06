#include "userControl.h"
#include "motion.h"

#define MOBILE_TARGET   -370
#define MOBILE_ZONE_SZ  100

task lockMobile() {
	if (!mobileCaptureIsLocked) {// only run once
		mobileCaptureIsLocked = true;
		while (mobileCaptureIsLocked) {
			if (SensorValue[mobileEncoder] > MOBILE_TARGET + MOBILE_ZONE_SZ)
				mobileCaptureSpeed(CAPTURE_EXTEND);
			else if (SensorValue[mobileEncoder] < MOBILE_TARGET - MOBILE_ZONE_SZ)
				mobileCaptureSpeed(CAPTURE_RETRACT);
			else
				mobileCaptureSpeed(0);
			wait1Msec(50);
		}
	}
}
task usercontrol() {
	while (true)
	{
		// Y component, X component, Rotation
		int strafeVal = C1RX;
		if (abs(strafeVal) < 20)
			strafeVal = 0;
		motor[frontLeft] =    C1LY + strafeVal + C1LX;
		motor[frontRight] =  -C1LY + strafeVal + C1LX;
		motor[backRight] =    C1LY + strafeVal - C1LX;
		motor[backLeft] =    -C1LY + strafeVal - C1LX;

		// Lift Controls
		if(vexRT [Btn5U] == 1) {
			liftSpeed(127);
		}
		else if(vexRT[Btn5D] == 1) {
			liftSpeed(-127);
		}
		else {
			// max list val 850
			int idle = -3*SensorValue[liftEncoder]/85 - 5;
			motor[liftLeft] = motor[liftRight] = idle;
		}

		// Friction Drum Controls
		static int drumIdle = 0;
		if(vexRT[Btn6U] == 1)
		{
			frictionDrumSpeed(127);
			drumIdle = 10;
		}
		else if(vexRT[Btn6D] == 1)
		{
			frictionDrumSpeed(-127);
			drumIdle = 0;
		}
		else
		{
			frictionDrumSpeed(drumIdle);
		}
		//Pneumatics
		if (vexRT[Btn8D] == 1)
		{
			setPistons(PISTON_PULL);
		}
		else if (vexRT[Btn8U] == 1)
		{
			setPistons(PISTON_PUSH);
		}

		//Mobile Goal control
		if (vexRT[Btn8L] == 1 && !mobileCaptureIsLocked){
			startTask(lockMobile);
		}
		else {
			if (abs(vexRT[Ch2]) > 50) {
				mobileCaptureIsLocked = false;
				mobileCaptureSpeed(vexRT[Ch2]);
			}
			else if (!mobileCaptureIsLocked) {
				mobileCaptureSpeed(0);
			}
		}
	}
}
