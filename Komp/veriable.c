#include <string.h>
#include <stdlib.h>
#include "veriable.h"


void initVeriable(){
	declarVeriables = NULL;
	tempVeriables =NULL;
}

struct declarVeriable* createDeclar(char* id, int tab, long long size){
	struct declarVeriable* ptr = malloc(sizeof(struct declarVeriable));
	ptr->identifier =  malloc(sizeof(char)*(strlen(id)+1));
	strcpy(ptr->identifier, id);
	ptr->type = tab;
	ptr->size = size;
	ptr->isUse = 0;
	ptr->position = 0;
	ptr->next = NULL;
	ptr->isInit = 0;
	return ptr;
}
long long pos = 2;

int declareVeriableTab(char* id, int tab, long long size){
	if(declarVeriables==NULL){
		declarVeriables = createDeclar(id,tab,size);
		return 0;
	}
	struct declarVeriable* ptr = declarVeriables;
	while(ptr->next != NULL){
		
		if(strcmp(ptr->identifier,id)==0){
			return -1;
		}
		ptr=ptr->next;
	}
	if(strcmp(ptr->identifier,id)==0){
		return -1;
	}
	ptr->next = createDeclar(id,tab,size);
	return 0;
}
int declareVeriable(char* id){
	return declareVeriableTab(id, 0, 0);
}
void declareNumb(char* id){
	if(declarVeriables==NULL){
		declarVeriables = createDeclar(id,2,0);
		declarVeriables->isInit=1;
		return;
	}
	struct declarVeriable* ptr = declarVeriables;
	while(ptr->next != NULL){
		if(strcmp(ptr->identifier,id)==0){
			return;
		}
		ptr=ptr->next;
	}
	if(strcmp(ptr->identifier,id)==0){
		return;
	}
	ptr->next = createDeclar(id,2,0);
	ptr->next->isInit=1;
	return;
}

struct declarVeriable* getVeriable(struct veriable* ver){
	struct declarVeriable* ptr = declarVeriables;
	while(ptr!=NULL){
		if(strcmp(ptr->identifier,ver->identifier)==0){
			return ptr;
		}
		ptr = ptr->next;
	}
	return NULL;
}

struct declarVeriable* getLast(){
	struct declarVeriable* ptr = declarVeriables;
	if(ptr==NULL)
		return NULL;
	while(ptr->next !=NULL){
		ptr=ptr->next;
	}
	return ptr;
}


struct veriable* useVeriableTab(char *id, struct veriable* tvp,int line){
	struct veriable* ptr = malloc(sizeof(struct veriable));
	ptr->identifier = malloc(sizeof(char) * (strlen(id)+1));
	ptr->line = line;
	strcpy(ptr->identifier, id);
	ptr->type = 1;
	ptr->tabvpos = tvp;
	return ptr;
}

struct veriable* useVeriable(char *id, int line){

	struct veriable* ptr = malloc(sizeof(struct veriable));
	ptr->line = line;
	ptr->identifier = malloc(sizeof(char) * (strlen(id)+1));
	strcpy(ptr->identifier, id);
	ptr->type = 0;
	return ptr;
}

struct veriable* useValue(char *id){
	struct veriable* ptr = malloc(sizeof(struct veriable));
	ptr->identifier = malloc(sizeof(char) * (strlen(id)+1));
	strcpy(ptr->identifier, id);
	ptr->type = 2;
	return ptr;
}


int searchVeriable(char *id){
	struct declarVeriable* ptr = declarVeriables;
	while(ptr!=NULL){
		if(strcmp(ptr->identifier,id)==0){
			return ptr->type;
		}
		ptr = ptr->next;
	}
	return -1;
}

int searchVeriableTab(char *id, long long ind){
	struct declarVeriable* ptr = declarVeriables;
	while(ptr!=NULL){
		if(strcmp(ptr->identifier,id)==0){
			if(ptr->type==1){
				if(ind<ptr->size && ind >=0)
					return 1;
				else{
					return -3;
				}
			}
			else{
				return -2;
			}
		}
		ptr = ptr->next;
	}
	return -1;
}
void addToTemp(struct declarVeriable* dec){
	dec->next = tempVeriables;
	tempVeriables = dec;
}


void clearTemp(){
	struct declarVeriable* ptr = tempVeriables;
	struct declarVeriable* ptr2;
	while(ptr!=NULL && ptr->next!=NULL){
		ptr2=ptr;
		while(ptr2 !=NULL && ptr2->next!=NULL){
			if(strcmp(ptr->identifier,ptr2->next->identifier)==0){
				struct declarVeriable* ptr3 = ptr2->next;
				ptr2->next = ptr2->next->next;
				free(ptr3->identifier);
				free(ptr3);
				ptr2=ptr2->next;
			}else{
				ptr2=ptr2->next;
			}
		}
		ptr=ptr->next;
	}
}
void generatePosition(){
	clearTemp();
	struct declarVeriable* ptr;
	if(tempVeriables!=NULL){
		ptr = tempVeriables;
		while(ptr->next!=NULL){
			ptr=ptr->next;
		}
		ptr->next = declarVeriables;
		declarVeriables = tempVeriables;
	}
	ptr=declarVeriables;
	// if(declarVeriables==NULL){
	// 	declarVeriables=tempVeriables;
	// 	ptr=declarVeriables;
	// } else{
	// 	ptr = declarVeriables;
	// 	while(ptr->next!=NULL){
	// 		if(ptr->type==0){
	// 			ptr->position = pos++;
	// 		}else if(ptr->type=1){
	// 			ptr->position = pos;
	// 			pos+=ptr->size;
	// 		}
	// 		ptr = ptr->next;
	// 	}
	// 	ptr->next = tempVeriables;
	// }
	while(ptr!=NULL){
		if(ptr->type==0){
				ptr->position = pos++;
			}else if(ptr->type=1 ){
				ptr->position = pos;
				pos+=ptr->size;
			}
			//printf("%lld %s\n", ptr->position, ptr->identifier);
			ptr = ptr->next;
	}
}
long long getPosition(char* id){
	struct declarVeriable* ptr = declarVeriables;
	while(ptr!=NULL){
		if(strcmp(ptr->identifier,id)==0){
			return ptr->position;
		}
		ptr= ptr->next;
	}
	return -1;
}


long long getLastPosition(){
	return pos;
}

// struct value* useVeriableTab(char * id, int i){
// 	if(veriables==NULL){
// 		struct value* p = malloc(sizeof(struct value));
// 		p->isUse=-1;
// 		return p;
// 	}
// 	struct veriable* ptr = veriables;
// 	do{
// 		if(strcmp(ptr->identifier,id)==0){
// 			if(ptr->isTab==0){
// 				if(i==-1){
// 					if(ptr->val->isUse>0){
// 						ptr->val->isUse++;
// 						return ptr->val;
// 					}else{
// 						ptr->val->isUse = 1;
// 						return ptr->val;
// 					}
// 				}else{
// 					ptr->val->isUse=-2;
// 					return ptr->val;
// 				}
// 			}else{
// 				if(i==-1){
// 					ptr->val->isUse=-2;
// 					return ptr->val;
// 				}else{
// 					if(i<ptr->size){
// 						if(ptr->val->isUse>0){
// 							ptr->val->isUse++;
// 							return ptr->val;
// 						}else{
// 							ptr->val->isUse++;
// 							return ptr->val;
// 						}
// 					}else{
// 						ptr->val->isUse=-3;
// 						return ptr->val;
// 					}
// 				}
// 			}
// 		}
// 		ptr = ptr->next;
// 	}while(ptr!=NULL);
// 	struct value* p = malloc(sizeof(struct value));
// 	p->isUse=-1;
// 	return p;
// }
// struct value* useVeriable(char * id){
// 	return useVeriableTab(id,-1);
// }
// struct value* declareNumber(char* id){
// 	declareVeriable(id);
// 	struct value* ptr = useVeriable(id);
// 	ptr->val = id;
// 	return ptr;
// }
