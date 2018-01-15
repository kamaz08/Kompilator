#ifndef COMMAND_H
#define COMMAND_H

#include "veriable.h"
// #include "helper.h"

struct command{
	int type;			//0commands, 1:=, 2if, 3while 4for, 5ford, 6read, 7write, 8skip
	struct veriable* id0;
	struct veriable* id1;
	struct veriable* id2;
	struct expression* exp;
	struct condition* con;
	struct command* com0;
	struct command* com1;
	struct command* next;
};


struct command* createCommand1(struct veriable* i0, struct expression* e);
struct command* createCommand2(struct condition* c, struct command* c0, struct command* c1);
struct command* createCommand3(struct condition* c, struct command* c1);
struct command* createCommand4(struct veriable* i0, struct veriable* i1, struct veriable* i2, struct command* c0);
struct command* createCommand5(struct veriable* i0, struct veriable* i1, struct veriable* i2, struct command* c0);
struct command* createCommand6(struct veriable* i0);
struct command* createCommand7(struct veriable* i0);
struct command* createCommand8();
void addCommand(struct command* to, struct command* w);



#endif