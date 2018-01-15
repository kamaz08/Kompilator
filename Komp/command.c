#include <stdlib.h>
#include "command.h"


struct command* createCommand(int t){
	struct command* ptr = malloc(sizeof(struct command));
	ptr->type=t;
	ptr->next=NULL;
	return ptr;
}
struct command* createCommand1(struct veriable* i0, struct expression* e){
	struct command* ptr = createCommand(1);
	ptr->id0=i0;
	ptr->exp=e;
	return ptr;
}
struct command* createCommand2(struct condition* c, struct command* c0, struct command* c1){
	struct command* ptr = createCommand(2);
	ptr->con=c;
	ptr->com0=c0;
	ptr->com1=c1;
	return ptr;

}
struct command* createCommand3(struct condition* c, struct command* c0){
	struct command* ptr = createCommand(3);
	ptr->con=c;
	ptr->com0=c0;
	return ptr;
}
struct command* createCommand4(struct veriable* i0, struct veriable* i1, struct veriable* i2, struct command* c0){
	struct command* ptr = createCommand(4);
	ptr->id0=i0;
	ptr->id1=i1;
	ptr->id2=i2;
	ptr->com0=c0;
	return ptr;
}
struct command* createCommand5(struct veriable* i0, struct veriable* i1, struct veriable* i2, struct command* c0){
	struct command* ptr = createCommand(5);
	ptr->id0=i0;
	ptr->id1=i1;
	ptr->id2=i2;
	ptr->com0=c0;
	return ptr;
}
struct command* createCommand6(struct veriable* i0){
	struct command* ptr = createCommand(6);
	ptr->id0=i0;
	return ptr;
}
struct command* createCommand7(struct veriable* i0){
	struct command* ptr = createCommand(7);
	ptr->id0=i0;
	return ptr;
}

struct command* createCommand8(){
	struct command* ptr = createCommand(8);
	return ptr;
}

void addCommand(struct command* to, struct command* w){
	while(to->next!=NULL){
		to=to->next;
	}
	to->next = w;
}



// void generateCommend1(struct charTab* tab, struct command* com){

// }