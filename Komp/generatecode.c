#include "generatecode.h"
#include <stdlib.h>
#include <stdio.h>

void getVeria(struct charTab* tab, struct veriable* ptr, int reg);
void getValue(struct charTab* tab, struct veriable* ptr, int reg);
void generateExp0(struct charTab* tab, struct expression* ptr);
void generateExp1(struct charTab* tab, struct expression* ptr);
void generateExp2(struct charTab* tab, struct expression* ptr);
void generateExp3(struct charTab* tab, struct expression* ptr);
void generateExp4(struct charTab* tab, struct expression* ptr);
void generateExp5(struct charTab* tab, struct expression* ptr);
void generateExpresion(struct charTab* tab, struct expression* ptr);
void generateCon0(struct charTab* tab, struct condition* ptr);
void generateCon1(struct charTab* tab, struct condition* ptr);
void generateCon2(struct charTab* tab, struct condition* ptr);
void generateCon3(struct charTab* tab, struct condition* ptr);
void generateCon4(struct charTab* tab, struct condition* ptr);
void generateCon5(struct charTab* tab, struct condition* ptr);
void generateCondition(struct charTab* tab, struct condition* ptr);
void generateCom0(struct charTab* tab, struct command* ptr);
void generateCom1(struct charTab* tab, struct command* ptr);
void generateCom2(struct charTab* tab, struct command* ptr);
void generateCom3(struct charTab* tab, struct command* ptr);
void generateCom4(struct charTab* tab, struct command* ptr);
void generateCom5(struct charTab* tab, struct command* ptr);
void generateCom6(struct charTab* tab, struct command* ptr);
void generateCom7(struct charTab* tab, struct command* ptr);
void generateCom8(struct charTab* tab, struct command* ptr);
void generateCom(struct charTab* tab, struct command* ptr);

long long numberfor;

struct charTab* createCharTab(){
	struct charTab* ptr = malloc(sizeof(struct charTab));
	ptr->size = 0;
	ptr->first = NULL;
	ptr->last = NULL;
	return ptr;
}
void addLine0(struct charTab* c, char* roz){
	if(c->first==NULL){
		c->first = c->last =  malloc(sizeof(struct charline));
	}else{
		c->last->next =  malloc(sizeof(struct charline));
		c->last = c->last->next;
	}
	c->last->next=NULL;
	c->size++;
	c->last->line = malloc(sizeof(char)*20);
	sprintf(c->last->line,"%s",roz);

}
void addLine1(struct charTab* c, char* roz, long long i){
	if(c->first==NULL){
		c->first = c->last =  malloc(sizeof(struct charline));
	}else{
		c->last->next =  malloc(sizeof(struct charline));
		c->last = c->last->next;
	}
	c->last->next=NULL;
	c->size++;
	c->last->line = malloc(sizeof(char)*20);
	sprintf(c->last->line,"%s %lld",roz,i);

}
void addLine2(struct charTab* c,char* roz, long long i, long long j){
	if(c->first==NULL){
		c->first = c->last =  malloc(sizeof(struct charline));
	}else{
		c->last->next =  malloc(sizeof(struct charline));
		c->last = c->last->next;
	}
	c->last->next=NULL;
	c->size++;
	c->last->line = malloc(sizeof(char)*20);
	sprintf(c->last->line,"%s %lld %lld",roz,i,j);
}

struct charline* addEmptyLine(struct charTab* c){
	if(c->first==NULL){
		c->first = c->last =  malloc(sizeof(struct charline));
	}else{
		c->last->next =  malloc(sizeof(struct charline));
		c->last = c->last->next;
	}
	c->last->next=NULL;
	c->size++;
	return c->last;
}
void changeLine(struct charline* l, char* roz, long long i, long long j){
	l->line = malloc(sizeof(char)*20);
	if(j!=-1)
		sprintf(l->line,"%s %lld %lld",roz,i,j);
	else
		sprintf(l->line,"%s %lld",roz,i);
}
void printCode(struct charTab* tab){
	struct charline* ptr = tab->first;
	while(ptr!=NULL){
		printf("%s\n", ptr->line);
		ptr= ptr->next;
	}
}


void getValueToRegister(struct charTab* tab, int toRegister, long long value){
	addLine1(tab, "ZERO", toRegister);
	if(value == 0)
		return;
	int t[1000];
	int i=-1;
	while(value>0){
		t[++i]=value % 2;
		value = value/2;
	}
	for(i; i>=0; --i){
		addLine1(tab, "SHL", toRegister);
		if(t[i]==1)
			addLine1(tab, "INC", toRegister);
	}
}

void generateCommand(struct  command* ptr){
	numberfor=0;
	struct charTab* tab = createCharTab();
	generateCom(tab, ptr);
	addLine0(tab,"HALT");
	printCode(tab);
}

void generateCom(struct charTab* tab, struct command* ptr){
	while(ptr!=NULL){
		switch(ptr->type){
			case 1: 
				generateCom1(tab,ptr);
				break;
			case 2: 
				generateCom2(tab,ptr);
				break;
			case 3: 
				generateCom3(tab,ptr);
				break;
			case 4: 
				generateCom4(tab,ptr);
				break;
			case 5: 
				generateCom5(tab,ptr);
				break;
			case 6: 
				generateCom6(tab,ptr);
				break;
			case 7: 
				generateCom7(tab,ptr);
				break;
			case 8: 
				generateCom8(tab,ptr);
				break;
		}
		ptr= ptr->next;
	}
}

void generateCom1(struct charTab* tab, struct command* ptr){
	generateExpresion(tab,ptr->exp);
	getVeria(tab, ptr->id0, 0);
	addLine1(tab, "STORE", 1);
}
void generateCom2(struct charTab* tab, struct command* ptr){

	generateCondition(tab,ptr->con);
	struct charline* line = addEmptyLine(tab);
	generateCom(tab, ptr->com0);
	changeLine(line, "JZERO", 1, tab->size+1);
	line = addEmptyLine(tab);
	generateCom(tab, ptr->com1);
	changeLine(line, "JUMP", tab->size, -1);

}
void generateCom3(struct charTab* tab, struct command* ptr){
	long long pos = tab->size;
	generateCondition(tab,ptr->con);
	struct charline* line = addEmptyLine(tab);
	generateCom(tab, ptr->com0);
	addLine1(tab,"JUMP", pos);
	changeLine(line, "JZERO", 1, tab->size);
}
void generateCom4(struct charTab* tab, struct command* ptr){
	getValue(tab, ptr->id1, 1);
	getVeria(tab, ptr->id0, 0);
	addLine1(tab, "STORE", 1);
	getValue(tab, ptr->id2, 4);
	long long fpos = getLastPosition()+numberfor++;

	getValueToRegister(tab,0,fpos);
	addLine1(tab,"STORE",4);

	//getVeria(tab, ptr->id0, 0);

	struct charline* line = addEmptyLine(tab);
	long long pos1 = tab->size;
	getVeria(tab, ptr->id0, 0);
	addLine1(tab,"LOAD", 1);
	addLine1(tab,"INC", 1);
	addLine1(tab,"STORE", 1);
	changeLine(line, "JUMP", tab->size,-1);

	getValueToRegister(tab,0,fpos);
	addLine1(tab,"LOAD", 4);
	addLine1(tab,"INC", 4);
	getVeria(tab, ptr->id0, 0);
	addLine1(tab,"SUB", 4);
	line = addEmptyLine(tab);
	generateCom(tab,ptr->com0);
	addLine1(tab, "JUMP", pos1);
	changeLine(line, "JZERO", 4, tab->size);
	numberfor--;
}
void generateCom5(struct charTab* tab, struct command* ptr){
	getValue(tab, ptr->id1, 1);
	addLine1(tab,"INC", 1);
	getVeria(tab, ptr->id0, 0);
	addLine1(tab, "STORE", 1);
	getValue(tab, ptr->id2, 4);
	long long fpos = getLastPosition()+numberfor++;

	getValueToRegister(tab,0,fpos);
	addLine1(tab,"STORE",4);

	//getVeria(tab, ptr->id0, 0);

	//struct charline* line = addEmptyLine(tab);
	long long pos1 = tab->size;

//	getValue(tab, ptr->id0, 4);
	getVeria(tab, ptr->id0, 3);
	addLine1(tab,"COPY", 3);
	addLine1(tab,"LOAD", 4);
	getValueToRegister(tab,0,fpos);
	addLine1(tab,"SUB", 4);
	long long x = tab->size;
	struct charline* line = addEmptyLine(tab);
	//addLine2(tab,"JZERO", 4, x + 2); //  wypierdalaj
	addLine1(tab,"COPY", 3);
	addLine1(tab,"LOAD", 4);
	addLine1(tab,"DEC", 4);
	addLine1(tab,"STORE", 4);
	generateCom(tab,ptr->com0);
	addLine1(tab, "JUMP", pos1);
	changeLine(line, "JZERO", 4, tab->size);
	// addLine1(tab,"LOAD", 4);
	// getVeria(tab, ptr->id0, 0);
	

	// struct charline* line = addEmptyLine(tab);
	// addLine1(tab,"LOAD", 1);
	// addLine1(tab,"DEC", 1);
	// addLine1(tab,"STORE", 1);	
	// generateCom(tab,ptr->com0);
	// addLine1(tab, "JUMP", pos1);
	// changeLine(line, "JUMP", tab->size, -1);







	// getValue(tab, ptr->id1, 1);
	// getVeria(tab, ptr->id0, 0);
	// addLine1(tab, "STORE", 1);
	// getValue(tab, ptr->id2, 4);
	// struct declarVeriable* last =  getLast();
	// int fpos = last->position+numberfor++;
	// getValueToRegister(tab,0,fpos);
	// addLine1(tab,"STORE",4);

	// struct charline* line = addEmptyLine(tab);
	// int pos1 = tab->size;
	// getVeria(tab, ptr->id0, 0);
	// addLine1(tab,"LOAD", 4);
	// addLine1(tab,"INC", 4);
	// addLine1(tab,"STORE", 4);
	// changeLine(line, "JUMP", tab->size,-1);
	// getValueToRegister(tab,0 , fpos);
	// addLine1(tab,"SUB", 4);
	// int pos2= tab->size;
	// addLine2(tab, "JZERO", 4, pos2+2);
	// line = addEmptyLine(tab);
	// generateCom(tab,ptr->com0);
	// addLine1(tab, "JUMP", pos1);
	// changeLine(line, "JUMP", tab->size, -1);
	numberfor--;
}
void generateCom6(struct charTab* tab, struct command* ptr){
	getVeria(tab, ptr->id0,0);
	addLine1(tab, "GET", 1);
	addLine1(tab, "STORE", 1);
}
void generateCom7(struct charTab* tab, struct command* ptr){
	getValue(tab, ptr->id0, 1);
	addLine1(tab, "PUT", 1);
}
void generateCom8(struct charTab* tab, struct command* ptr){
}

void generateCondition(struct charTab* tab, struct condition* ptr){
	switch(ptr->type){
		case 0:
			generateCon0(tab,ptr);
			break;
		case 1:
			generateCon1(tab,ptr);
			break;
		case 2:
			generateCon2(tab,ptr);
			break;
		case 3:
			generateCon3(tab,ptr);
			break;
		case 4:
			generateCon4(tab,ptr);
			break;
		case 5:
			generateCon5(tab,ptr);
			break;
	}

}
void generateCon0(struct charTab* tab, struct condition* ptr){
	generateCon1(tab,ptr);
	long long pos = tab->size;
	addLine2(tab, "JZERO", 1, pos+3);
	addLine1(tab, "ZERO", 1);
	addLine1(tab, "JUMP", pos+4);
	addLine1(tab, "INC", 1);
}
void generateCon1(struct charTab* tab, struct condition* ptr){
	if(ptr->left->type!=2){
		getValue(tab,ptr->right,4);
		getVeria(tab,ptr->left,3);
	}else if(ptr->right->type!=2){
		getValue(tab,ptr->left,4);
		getVeria(tab,ptr->right,3);
	}else{
		long long a = atoll(ptr->left->identifier);
		long long b = atoll(ptr->right->identifier);
		addLine1(tab, "ZERO", 1);
		if(a!=b)
			addLine1(tab, "INC", 1);
		return;
	}
	addLine1(tab, "ZERO", 0);
	addLine1(tab, "ZERO", 1);
	addLine1(tab, "STORE", 4);
	addLine1(tab, "COPY", 3);
	addLine1(tab, "SUB", 4);
	long long pos = tab->size;
	addLine2(tab, "JZERO", 4, pos+2);
	addLine1(tab, "JUMP", pos+9);
	addLine1(tab, "ZERO", 0);
	addLine1(tab, "LOAD", 4);
	addLine1(tab, "INC", 4);
	addLine1(tab, "COPY", 3);
	addLine1(tab, "SUB", 4);
	addLine2(tab, "JZERO", 4, pos+9);
	addLine1(tab, "JUMP", pos+10);
	addLine1(tab, "INC", 1);
}
void generateCon2(struct charTab* tab, struct condition* ptr){
	if(ptr->left->type!=2){
		getValue(tab,ptr->right,4);
		getVeria(tab,ptr->left,0);
		addLine1(tab, "ZERO", 1);
		addLine1(tab, "SUB", 4);
		long long pos = tab->size;
		addLine2(tab, "JZERO", 4, pos+2);
		addLine1(tab, "INC", 1);
	}else if(ptr->right->type!=2){
		getValue(tab,ptr->left,4);
		getVeria(tab,ptr->right,0);
		addLine1(tab, "ZERO", 1);
		addLine1(tab, "INC", 1);
		addLine1(tab, "SUB", 4);
		long long pos = tab->size;
		addLine2(tab, "JZERO", 4, pos+2);
		addLine1(tab, "DEC", 1);
	}else{
		long long a = atoll(ptr->left->identifier);
		long long b = atoll(ptr->right->identifier);
		addLine1(tab, "ZERO", 1);
		if(a<=b)
			addLine1(tab, "INC", 1);
		return;
	}

}
void generateCon3(struct charTab* tab, struct condition* ptr){
	if(ptr->left->type!=2){
		getValue(tab,ptr->right,4);
		getVeria(tab,ptr->left,0);
		addLine1(tab,"INC", 4);
		addLine1(tab, "ZERO", 1);
		addLine1(tab, "INC", 1);
		addLine1(tab, "SUB", 4);
		long long pos = tab->size;
		addLine2(tab, "JZERO", 4, pos+2);
		addLine1(tab, "DEC", 1);
	}else if(ptr->right->type!=2){
		getValue(tab,ptr->left,4);
		getVeria(tab,ptr->right,0);
		addLine1(tab, "ZERO", 1);
		addLine1(tab, "INC", 1);
		addLine1(tab, "SUB", 4);
		long long pos = tab->size;
		addLine2(tab, "JZERO", 4, pos+2);
		addLine1(tab, "JUMP", pos+3);
		addLine1(tab, "DEC", 1);
	}else{
		long long a = atoll(ptr->left->identifier);
		long long b = atoll(ptr->right->identifier);
		addLine1(tab, "ZERO", 1);
		if(a>b)
			addLine1(tab, "INC", 1);
		return;
	}

}
void generateCon4(struct charTab* tab, struct condition* ptr){
	generateCon3(tab,ptr);
	long long pos = tab->size;
	addLine2(tab, "JZERO", 1, pos+3);
	addLine1(tab, "ZERO", 1);
	addLine1(tab, "JUMP", pos+4);
	addLine1(tab, "INC", 1);
}
void generateCon5(struct charTab* tab, struct condition* ptr){
	generateCon2(tab,ptr);
	long long pos = tab->size;
	addLine2(tab, "JZERO", 1, pos+3);
	addLine1(tab, "ZERO", 1);
	addLine1(tab, "JUMP", pos+4);
	addLine1(tab, "INC", 1);
}


void generateExpresion(struct charTab* tab, struct expression* ptr){
	switch(ptr->type){
		case 0:
			generateExp0(tab,ptr);
			break;
		case 1:
			generateExp1(tab,ptr);
			break;
		case 2:
			generateExp2(tab,ptr);
			break;
		case 3:
			generateExp3(tab,ptr);
			break;
		case 4:
			generateExp4(tab,ptr);
			break;
		case 5:
			generateExp5(tab,ptr);
			break;
	}
}
void generateExp0(struct charTab* tab, struct expression* ptr){
	getValue(tab,ptr->left,1);
}
void generateExp1(struct charTab* tab, struct expression* ptr){
	if(ptr->left->type!=2){
		getValue(tab,ptr->right,1);
		getVeria(tab,ptr->left,0);
		addLine1(tab, "ADD", 1);
		return;
	}
	if(ptr->right->type!=2){
		getValue(tab,ptr->left,1);
		getVeria(tab,ptr->right,0);
		addLine1(tab, "ADD", 1);
		return;
	}
	getValue(tab,ptr->left,1);
	getValue(tab,ptr->right,2);
	addLine1(tab, "ZERO", 0);
	addLine1(tab, "STORE", 2);
	addLine1(tab, "ADD", 1);
}
void generateExp2(struct charTab* tab, struct expression* ptr){
	if(ptr->right->type!=2){
		getValue(tab,ptr->left,1);
		getVeria(tab,ptr->right,0);
		addLine1(tab, "SUB", 1);
		return;
	}
	getValue(tab,ptr->left,1);
	getValue(tab,ptr->right,2);
	addLine1(tab, "ZERO", 0);
	addLine1(tab, "STORE", 2);
	addLine1(tab, "SUB", 1);
}
void generateExp3(struct charTab* tab, struct expression* ptr){
	getValue(tab,ptr->left,3);
	getValue(tab,ptr->right,4);
	long long pos=tab->size;
	addLine1(tab, "ZERO", 0);
	addLine1(tab, "STORE", 3);
	addLine1(tab, "INC", 0);
	addLine1(tab, "STORE", 4);
	addLine1(tab, "DEC", 0);
	addLine1(tab, "SUB", 4);
	addLine2(tab, "JZERO", 4, pos+11);
	addLine1(tab, "LOAD", 4);
	addLine1(tab, "INC", 0);
	addLine1(tab, "LOAD", 3);
	addLine1(tab, "JUMP", pos+13);
	addLine1(tab, "INC", 0);
	addLine1(tab, "LOAD", 4);
	addLine1(tab, "ZERO", 1);
	addLine2(tab, "JZERO", 4, pos+25);
	addLine2(tab, "JODD", 4, pos+19);
	addLine1(tab, "SHL", 3);
	addLine1(tab, "SHR", 4);
	addLine1(tab, "JUMP", pos+15);
	addLine1(tab, "ZERO", 0);
	addLine1(tab, "STORE", 3);
	addLine1(tab, "ADD", 1);
	addLine1(tab, "SHL", 3);
	addLine1(tab, "SHR", 4);
	addLine1(tab, "JUMP", pos+14);
}
void generateExp4(struct charTab* tab, struct expression* ptr){
	getValue(tab,ptr->left,3);
	getValue(tab,ptr->right,4);
	long long pos=tab->size;
	addLine1(tab, "ZERO", 1);
	addLine2(tab, "JZERO",4, pos+39);
	addLine1(tab, "ZERO", 0);
	addLine1(tab, "INC", 0);
	addLine1(tab, "STORE", 4);
	addLine1(tab, "ZERO", 4);
	addLine1(tab, "INC", 4);
	addLine2(tab, "JZERO", 3,pos+15);
	addLine1(tab, "SHL", 4);
	addLine2(tab, "JODD", 3, pos+12);
	addLine1(tab, "SHR", 3);
	addLine1(tab, "JUMP", pos+7);
	addLine1(tab, "SHR", 3);
	addLine1(tab, "INC", 4);
	addLine1(tab, "JUMP", pos+7);
	addLine1(tab, "ZERO", 3);
	addLine1(tab, "DEC", 4);
	addLine2(tab, "JZERO", 4, pos+40);
	addLine1(tab, "INC", 4);
	addLine1(tab, "SHL", 3);
	addLine2(tab, "JODD", 4, pos+23);
	addLine1(tab, "SHR", 4);
	addLine1(tab, "JUMP", pos+25);
	addLine1(tab, "INC", 3);
	addLine1(tab, "SHR", 4);
	addLine1(tab, "ZERO", 0);
	addLine1(tab, "STORE", 3);
	addLine1(tab, "INC", 0);
	addLine1(tab, "INC", 3);
	addLine1(tab, "SUB", 3);
	addLine2(tab, "JZERO", 3, pos+35);
	addLine1(tab, "SHL", 1);
	addLine1(tab, "INC", 1);
	addLine1(tab, "DEC", 3);
	addLine1(tab, "JUMP", pos+16);
	addLine1(tab, "ZERO", 0);
	addLine1(tab, "LOAD", 3);
	addLine1(tab, "SHL", 1);
	addLine1(tab, "JUMP", pos+16);
	addLine1(tab, "ZERO", 3);

}
void generateExp5(struct charTab* tab, struct expression* ptr){
	generateExp4(tab,ptr);
	addLine1(tab, "ZERO", 0);
	addLine1(tab, "STORE", 3);
	addLine1(tab, "LOAD", 1);
}

void getValue(struct charTab* tab, struct veriable* ptr, int reg){ //0,2 i register
	if(ptr->type==0){
		long long pos = getPosition(ptr->identifier);
		getValueToRegister(tab, 0, pos);
		addLine1(tab,"LOAD",reg);
	}
	if(ptr->type==1){
		long long pos = getPosition(ptr->identifier);
		if(ptr->tabvpos->type==2){
			pos+=atoll(ptr->tabvpos->identifier);
			getValueToRegister(tab, 0, pos);
			addLine1(tab,"LOAD",reg);
		}else{
			long long x = reg==0?2:reg;
			getValueToRegister(tab, x, pos);
			long long pos1 = getPosition(ptr->tabvpos->identifier);
			getValueToRegister(tab, 0, pos1);
			addLine1(tab, "ADD", x);
			addLine1(tab, "COPY", x);
			addLine1(tab,"LOAD",reg);
		}
	}
	if(ptr->type==2){
		getValueToRegister(tab, reg, atoll(ptr->identifier));
	}
}

void getVeria(struct charTab* tab, struct veriable* ptr, int reg){ //0 2 register
	if(ptr->type==0){
		long long pos = getPosition(ptr->identifier);
		getValueToRegister(tab, reg, pos);
	}
	if(ptr->type==1){
		long long pos = getPosition(ptr->identifier);
		if(ptr->tabvpos->type==2){
			pos+=atoll(ptr->tabvpos->identifier);
			getValueToRegister(tab, reg, pos);
		}else{
			int x = reg==0?2:reg;
			getValueToRegister(tab, x, pos);
			long long pos1 = getPosition(ptr->tabvpos->identifier);
			getValueToRegister(tab, 0, pos1);
			addLine1(tab, "ADD", x);
			if(reg==0)
				addLine1(tab, "COPY", x);
		}
	}
}