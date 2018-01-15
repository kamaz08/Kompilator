#include <stdlib.h>
#include "expression.h"

struct expression* createExpression(int t, struct veriable* l, struct veriable*r){
	struct expression* ptr = malloc(sizeof(struct expression));
	ptr->type = t;
	ptr->left = l;
	ptr->right = r;
	return ptr;
}

