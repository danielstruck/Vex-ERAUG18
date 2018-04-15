
task autonomous() {
	switch (selectedAuton) {
		case 1:
		  autonBlue();
		  break;
		case 2:
		  autonRed();
		  break;
		case 3:
		  autonSkills();
		  break;
		default:
		  autonDefault();
		  break;
	}
}
