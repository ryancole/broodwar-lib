#ifndef _POINTERS_
#define _POINTERS_

extern int *offset_totalplayers;
extern int *offset_totalbuildings;
extern int *offset_ourplayerid;
extern int *offset_raceid;
extern int *offset_minsupply;
extern int *offset_minerals;
extern int *offset_gas;
extern int *offset_color;
extern unsigned long offset_playernames;

class Pointers {
public:
	int getcolor(int x);
	inline int ourplayerid() { return *offset_ourplayerid; };
	inline int totalplayers() { return *offset_totalplayers; };
	inline int getraceid(int x) { return *(offset_raceid + (x * 0x12)); };
	inline int totalbuildings(int x) { return *(offset_totalbuildings + x); };
	inline int minsupply(int x) { return *(offset_minsupply + x); };
	inline int minerals(int x) { return *(offset_minerals + x); };
	inline int gas(int x) { return *(offset_gas + x); };
	inline char *playernames(int x) { return (char*)(offset_playernames + (x * 0x48)); };
};

struct PlayerInfo {
	char color;
	char *name;
	int id, race;
};

extern Pointers *offsets;
extern PlayerInfo *players;

#endif