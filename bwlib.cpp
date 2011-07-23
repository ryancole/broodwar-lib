#include <windows.h>
#include "GlobalClass.h"
#include "Pointers.h"

#define color_blue	0x02
#define color_white	0x04
#define color_red	0x06
#define color_tab	0x09

void beginpatchproc(void);
void printpatchproc(void);
void __fastcall handlecommand(const char *theCommand);
void displaypage(int pagenumber);

BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved) {
    switch (dwReason) {
		case DLL_PROCESS_ATTACH: {
				global->PageNumber = 0;	

				//global->patch.NopAddress(0x004b8bdf, 32);
				global->patch.PatchAddress(2, 0x0047af68, (DWORD)&handlecommand, NULL);
				global->patch.PatchAddress(1, 0x0044B242, (DWORD)&beginpatchproc, NULL);
				global->patch.PatchAddress(2, 0x00473b68, (DWORD)&printpatchproc, NULL);
				break;
				}

        case DLL_PROCESS_DETACH:
				break;
    }

	return true;
}

void beginpatchproc(void) {
	int numplayers = 0;
	for(int x = 0; x <= 7; x++) {
		if(offsets->totalbuildings(x) >= 1) {
			players[numplayers].id = x;
			players[numplayers].race = offsets->getraceid(numplayers);
			players[numplayers].color = offsets->getcolor(numplayers);
			numplayers++;
		}
	}
}

void printpatchproc(void) {
	for(int x = 0; x <= (offsets->totalplayers()-1); x++) {
		global->native.PrintText(0x00, (00 + (x * 10)), "%c%d %c%s", color_blue, players[x].id, color_white, offsets->playernames(players[x].id));
	}

	displaypage(global->PageNumber);
}

void __fastcall handlecommand(const char *theCommand) {
	DWORD originalFunction = 0x00478600;
	
	if(!strncmp("/drop ", theCommand, 6)) {
		if(strlen(theCommand) == 7) {
			int userid = theCommand[6] - '0';
			global->native.dropplayer(userid, 0, 0x40000006);
		}
	} else if(!strncmp("/page ", theCommand, 6)) {
		if(strlen(theCommand) == 7) {
			int pagenum = theCommand[6] - '0';
			global->PageNumber = pagenum;
		}
	} else {
		goto end;
	}

end:
	__asm {
		mov ecx, theCommand
		call originalFunction
	}
}

void displaypage(int pagenumber) {
	switch(pagenumber) {
		case 0: {
			//global->native.printicons(0x82, 0x00);
			for(int x = 0; x <= (offsets->totalplayers()-1); x++) {
				global->native.PrintText(0x82, (00 + (x * 10)), "%c%d", color_blue, offsets->minerals(x));
				global->native.PrintText(0xA0, (00 + (x * 10)), "%c%d", color_blue, offsets->gas(x));
				global->native.PrintText(0xBE, (00 + (x * 10)), "%c%d/%d", color_blue, offsets->minsupply(x), global->native.maxsupply(players[x].race, players[x].id));
			}
			break;
		}

		default: {
			global->native.PrintText(0x82, 00, "No page selected");
			break;
		}
	}
}