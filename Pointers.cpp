#include "Pointers.h"

int *offset_totalplayers = (int*)0x006591b0;
int *offset_totalbuildings = (int*)0x00518084;
int *offset_ourplayerid = (int*)0x00508D5C;
int *offset_raceid = (int*)0x00658E8C;
int *offset_minsupply = (int*)0x00517f34;
int *offset_minerals = (int*)0x00515240;
int *offset_gas = (int*)0x00515270;
int *offset_color = (int*)0x00672d01;
unsigned long offset_playernames = 0x00658e48;

Pointers *offsets = new Pointers;
PlayerInfo *players = new PlayerInfo[7];

int Pointers::getcolor(int x) {
	switch(*(offset_color + x)) {
		case 0: return 0x06; break; // red
		case 1: return 0x02; break; // blue
		case 2: return 0x07; break; // teal
		case 6: return 0x04; break; // white
		case 7: return 0x03; break; // yellow
		default: return 0x7F; break; // red
	}
}