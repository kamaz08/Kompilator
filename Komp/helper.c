#include "helper.h"
#include <stdlib.h>
#include <stdio.h>


int checkVeriables(struct command* com){
	if(com==NULL)
		return 0;
	struct command* ptr = com;
	while(ptr!=NULL){
		switch(ptr->type){
			case 1:
				if(check1(ptr)<0)
					return -1;
				break;
			case 2:
				if(check2(ptr)<0)
					return -1;
				break;
			case 3:
				if(check3(ptr)<0)
					return -1;
				break;	
			case 4:
			case 5:
				if(check4(ptr)<0)
					return -1;
				break;
			case 6:
				if(check6(ptr)<0)
					return -1;
				break;
			case 7:
				if(check7(ptr)<0)
					return -1;
				break;
		}
		ptr = ptr -> next;
	}
	return 0;
}

int check7(struct command* com){
//	printf("check7\n");
	if(checkVeriable(com->id0, 1)<0)
		return -1;
	return 0;
}

int check6(struct command* com){
//	printf("check6\n");
	if(checkVeriable(com->id0, 0)<0)
		return -1;
	return 0;
}

int check4(struct command* com){
//	printf("check4\n");
	if(checkVeriable(com->id1,1)<0 || checkVeriable(com->id2,1)<0){
		return -1;
	}
	struct declarVeriable* ptr =  getLast();
	declareVeriable(com->id0->identifier);
	ptr->next->isInit=2;

	//checkVeriable(com->id0, 0);
	int bo = checkVeriables(com->com0);
	addToTemp(ptr->next);
	ptr->next = NULL;
	return bo;
}

int check3(struct command* com){
//	printf("check3\n");
	int bo = checkCondition(com->con);
	if(bo<0){
		return -1;
	}
	if(checkVeriables(com->com0)<0)
		return -1;
	return 0;
}

int check2(struct command* com){
//	printf("check2\n");
	int bo = checkCondition(com->con);
	if(bo<0){
		return -1;
	}
	if(checkVeriables(com->com0)<0 || checkVeriables(com->com1)<0)
		return -1;
	return 0;
}

int check1(struct command* com){
//	printf("check1\n");
	if(checkVeriable(com->id0,0)<0){
		return -1;
	}
	int bo = checkExpression(com->exp);
	if(bo<0){
		return -1;
	}
	return 0;
}


int checkVeriable(struct veriable* ver, int init){
	struct declarVeriable* ptr = getVeriable(ver);
	if(ptr==NULL){
		printf("Nizadeklarowana zmienna w lini %d\n", ver->line);
		printf("Zmienna: %s\n", ver->identifier);
		return -1;
	}

	if(init==1 && ptr->isInit == 0){
		printf("Niezainicjowana zmienna w lini %d\n", ver->line);
		printf("Zmienna: %s\n", ver->identifier);
		return -2;
	}
	if(init == 0 && ptr->isInit==2){
		printf("Zmiana wartosci iteratora petli w lini %d\n", ver->line);
		printf("Zmienna: %s\n", ver->identifier);
		return -2;
	}
	if(init==0){
		ptr->isInit=1;
	}
	if(ver->type==1){
		return checkVeriable(ver->tabvpos,1);
	}
	ptr->isUse++;
	return 0;
}

int checkExpression(struct expression* exp){
	int bo = checkVeriable(exp->left,1);
	if(bo<0){
		return -1;
	}
	if(exp->right!=NULL){
		bo = checkVeriable(exp->right,1);
		if(bo<0){
			return -1;
		}
	}
	return 0;
}

int checkCondition(struct condition* con){
	int bo = checkVeriable(con->left,1);
	if(bo<0){
		return -1;
	}
	bo = checkVeriable(con->right,1);
	if(bo<0){
		return -1;
	}
	return 0;
}
