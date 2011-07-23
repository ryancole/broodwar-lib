#ifndef _PATCH_
#define _PATCH_

#include <windows.h>

class PatchClass {
public:
	DWORD PatchAddress(int type, DWORD AddressToPatch, DWORD AddressToUse, DWORD PadSize);
	DWORD PatchClass::NopAddress(DWORD AddressToPatch, DWORD Length);
};

#endif