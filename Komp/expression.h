#ifndef EXPRESSION_H
#define EXPRESSION_H

// #include "veriable.h"

struct expression{
	int type;			//0v, 1+, 2-, 3*, 4/, 5%
	struct veriable* left;
	struct veriable* right;
};

struct expression* createExpression(int t, struct veriable* l, struct veriable*r);
 
#endif