#include <stdlib.h>
#include "condition.h"

struct condition* createCondition(int t, struct veriable* l, struct veriable*r){
	struct condition* ptr = malloc(sizeof(struct condition));
	ptr->type = t;
	ptr->left = l;
	ptr->right = r;
}
 
