#ifndef CONDITION_H
#define CONDITION_H

// #include "veriable.h"

struct condition{
	int type;			//0=, 1<>, 2<, 3>, 4<=, 5>=
	struct veriable* left;
	struct veriable* right;
};

struct condition* createCondition(int t, struct veriable* l, struct veriable*r);

#endif