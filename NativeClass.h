#ifndef _NATIVE_
#define _NATIVE_

#include <windows.h>
#include <stdio.h>
#include <stdarg.h>

typedef int(__fastcall* pfnGetMaxSupply)(BYTE, BYTE);
typedef void (__fastcall *pfnPrintFunc) (int x, int y, const char *text);
typedef void (__fastcall *pfnDropFunc) (int playerid, int edx, DWORD pushed);

class NativeClass {
public:
	void PrintText(int x, int y, const char *fmt, ...);
	int maxsupply(int raceid, int playerid);
	int printicons(DWORD x, DWORD y);
	void dropplayer(int playerid, int edx, DWORD pushed);
};

#endif