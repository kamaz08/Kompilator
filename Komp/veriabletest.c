#include <stdio.h>
#include "veriable.h"


int main(){
	int a=1;
	char s[20];
	int tab,size, pos;
	if(veriables==NULL)
		printf("super");
	else{
		printf("lepiej\n");
	}
	initVeriable();
	if(veriables==NULL)
		printf("super");
	else{
		printf("lepiej\n");
	}
	do{
		scanf("%d",&a);
		scanf("%s",s);
		switch(a){
			case 1:
				scanf("%d",&tab);
				scanf("%d",&size);
				printf("%d\n", declareVeriable(s, tab, size));
				break;
			case 2 :
				scanf("%d",&size);
				scanf("%d",&pos);
				printf("%d\n",useVeriable(s, size,  pos));
				break;
		}

	}while(a!=0);
	




	return 0;
}