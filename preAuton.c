
void pre_auton() {
  // Set bStopTasksBetweenModes to false if you want to keep user created tasks running between
  // Autonomous and Tele-Op modes. You will need to manage all user created tasks if set to false.
  bStopTasksBetweenModes = true;
  //Turns on the Backlight
  bLCDBacklight = true;

  resetSensors();
  
#ifdef _MOTION_PLUS_H_
  // start motion plus updater if it has been included
  startTask(motionPlusUpdater);
#endif // _MOTION_PLUS_H_

  selectAuton();
}

void resetSensors() {
  SensorValue[pistonOne] = 0;
  SensorValue[pistonTwo] = 0;
  SensorValue[liftEncoder] = 0;
  SensorValue[rightEncoder] = 0;
  SensorValue[mobileEncoder] = 0;
  SensorValue[liftEncoder] = 0;
  resetGyro();
}

void resetGyro() {
  SensorType[gyroSens] = sensorNone;
  wait10Msec(100);
  SensorType[gyroSens] = sensorGyro;
  wait10Msec(100);
}

void selectAuton() {
  //Copied from someone's sample code because the documentation for RobotC won't tell me anything useful
  //These should logically work, but I'm not 100% sure
  const short left = 1;
  const short center = 2;
  const short right = 4;

  selectedAuton = 1;
  bool autonConfirm = false;
  displayLCDString(0, 0, "Auton:");
  displayLCDNumber(1, 4, selectedAuton);
  while (!autonConfirm) {
    while (nLCDButtons == 0) {
      wait1Msec(10); // wait for button to be pressed
    }

    switch ((int)nLCDButtons) {
      case left:
        selectedAuton--;
        break;
      case center:
        autonConfirm = true;
        break;
      case right:
        selectedAuton++;
        break;
      case left + center:
        break;
      case left + right:
        break;
      case center + right:
        break;
      case left + center + right:
        break;
    }

    if (selectedAuton < 1)
      selectedAuton = 1;
    else if (selectedAuton > nAutons)
      selectedAuton = nAutons;

    // TODO draw LCD stuff
    clearLCDLine(1);
    displayLCDNumber(1, 4, selectedAuton);

    while (nLCDButtons != 0) {
      /* wait for button to be released */
      wait1Msec(10);
    }
  }
}
