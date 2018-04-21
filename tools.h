#ifndef _TOOLS_H_
#define _TOOLS_H_


#define REAR_WHEELS_MULT  0.85


int signum(float val) {
	if (val > 0)
		return 1;
	else if (val < 0)
		return -1;
	else 
		return 0;
}


#endif // _TOOLS_H_