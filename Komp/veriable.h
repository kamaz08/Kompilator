#ifndef VERIABLE_H
#define VERIABLE_H


struct declarVeriable{
	char* identifier;
	long long position;
	int type;
	long long size;
	struct declarVeriable* next;
	int isUse;
	int isInit;
};

struct veriable{
	char* identifier;
	int line;
	int type;
	struct veriable* tabvpos;
};

struct declarVeriable* declarVeriables;
struct declarVeriable* tempVeriables;

void initVeriable();
int declareVeriableTab(char* id, int tab, long long size);
int declareVeriable(char* id);
void declareNumb(char* id);
struct veriable* useVeriableTab(char *id, struct veriable* tvp, int line);
struct veriable* useVeriable(char *id, int line);
struct veriable* useValue(char *id);
int searchVeriable(char *id);
struct declarVeriable* getVeriable(struct veriable* ver);
struct declarVeriable* getLast();
void generatePosition();
long long getPosition(char* id);
void addToTemp(struct declarVeriable* dec);
long long getLastPosition();
int searchVeriableTab(char *id, long long ind);
#endif