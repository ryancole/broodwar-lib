#ifndef _GLOBAL_
#define _GLOBAL_

#include <stdio.h>
#include "PatchClass.h"
#include "NativeClass.h"

class GlobalClass {
public:
	PatchClass patch;
	NativeClass native;

	int PageNumber;
	void debugprint(char *output);
};

extern GlobalClass *global;

#endif