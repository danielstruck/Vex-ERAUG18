#ifndef _TOOLS_H_
#define _TOOLS_H_


int signum(float val) {
	if (val > 0)
		return 1;
	else if (val < 0)
		return -1;
	else 
		return 0;
}


#endif // _TOOLS_H_