#include "NativeClass.h"

void NativeClass::PrintText(int x, int y, const char *fmt, ...) {
	int len;
	char *buffer;
	va_list args;
	const pfnPrintFunc Print = (pfnPrintFunc)0x004E5D80;

	va_start(args, fmt);
	len = _vscprintf(fmt, args) + 1;
	buffer = new char[len];
	vsprintf(buffer, fmt, args);

	Print(x, y, buffer);
	delete [] buffer;
}

int NativeClass::maxsupply(int raceid, int playerid) {
	pfnGetMaxSupply getmaxsup = (pfnGetMaxSupply)0x410A90;

	return (getmaxsup(raceid, playerid) >> 1);
}

int NativeClass::printicons(DWORD x, DWORD y) {
	__asm {
		pushad
		pushfd

		push 0x0012fdd4
		movsx edx, x
		movsx ecx, y
		mov eax, 0x004e7a40
		call eax

		popfd
		popad
	}
}

void NativeClass::dropplayer(int playerid, int edx, DWORD pushed) {
	// drop player from game, do not tell anyone func offset!!!
	const pfnDropFunc Drop = (pfnDropFunc)0x00481200;
	Drop(playerid, edx, pushed);
}