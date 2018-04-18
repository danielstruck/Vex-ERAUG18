task LCDControl() {
	static const int left   = 1;
	static const int center = 2;
	static const int right  = 4;
	
	while (true) {
		switch ((int)nLCDButtons) {
			case left:
				break;
			case center:
				break;
			case right:
				break;
			case left + center:
				break;
			case left + right:
				break;
			case center + right:
				break;
			case left + center + right: // reset all sensors
				while (nLCDButtons != 0)
					wait1Msec(10); // let other tasks run
				
				clearLCDLine(0);
				clearLCDLine(1);
				displayLCDCenteredString(0, "reset sensors?");
								  //           111111
								  // 0123456789012345
				displayLCDCenteredString(1, "yes  cancel   no");
				
				for (int i = 0; i < 3000 && nLCDButtons == 0; i += 10)
					wait1Msec(10); // let other tasks run
				
				if (nLCDButtons == left)
					resetSensors();
				break;
			default:
				string line;
				sprintf(line, "%.2fV", nImmediateBatteryLevel/1000.0);
				clearLCDLine(1);
				displayLCDCenteredString(1, line);
				break;
		}
	}
}
