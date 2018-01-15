#ifndef GENERATECODE_H
#define GENERATECODE_H

#include "veriable.h"
#include "condition.h"
#include "expression.h"
#include "command.h"


struct charline{
	char* line;
	struct charline* next;
};
struct charTab{
	struct charline* first;
	struct charline* last;
	long long size;
};
void addLine0(struct charTab* c, char* roz);
void addLine1(struct charTab* c, char* roz, long long i);
void addLine2(struct charTab* c,char* roz, long long i, long long j);
struct charline* addEmptyLine(struct charTab* c);
void changeLine(struct charline* l, char* roz, long long i, long long j);
struct charTab* createCharTab();
void getValueToRegister(struct charTab* tab, int toRegister, long long value);
void generateCommand(struct command* ptr);
void printCode(struct charTab* tab);


#endif