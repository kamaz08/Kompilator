%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "veriable.h"
#include "condition.h"
#include "expression.h"
#include "command.h"
#include "generatecode.h"


extern int yylineno;
int yylex(void);
void yyerror(char const *,...);
char *laczenienapisow(char* str1, char* str2);
%}

%union {
	char* id;
	struct veriable* val;
	struct condition* con;
	struct expression* exp;
	struct command* com;
}
%type <val> identifier
%type <com> command
%type <com> commands
%type <exp> expression
%type <val> value
%type <con> condition

%token KVAR KBEGIN KEND KIF KTHEN KELSE KENDIF KWHILE KDO KENDWHILE KFOR KFROM KTO KDOWNTO KENDFOR KREAD KWRITE KSKIP KSR KPR KDOD KMIN KRAZ KDZI KMOD KROW KROZ KMNI KWIE KMRO KWRO KKLE KKPR;
%token <id> KNUMBER;
%token <id> KPIDENTIFIER;
%%



input:
	program																{}
	;
program:
	KVAR vdeclarations KBEGIN commands KEND 							{
																			if(checkVeriables($4)<0)
																				return;
																			generatePosition();
																			generateCommand($4);
																		}
	;
vdeclarations:
	vdeclarations KPIDENTIFIER											{
																			if(declareVeriable($2)==-1){
																				yyerror("Ponowna deklaracja zmiennej");
																				printf("Zmienna: %s\n",$2);
																				YYERROR;
																			}
																		} 
	| vdeclarations KPIDENTIFIER KKLE KNUMBER KKPR						{
																			if(declareVeriableTab($2,1,atoll($4))==-1){
																				yyerror("Ponowna deklaracja zmiennej");
																				printf("Zmienna: %s\n",$2);
																				YYERROR;
																			}
																		} 
	| %empty															{}

commands:
	commands command 													{addCommand($1,$2); $$=$1;}
	| command 															{$$=$1;}

command:
	identifier KPR expression KSR										{
																			$$=createCommand1($1,$3);
																		}
	| KIF condition KTHEN commands KELSE commands KENDIF				{$$=createCommand2($2,$4,$6);}
	| KIF condition KTHEN commands KENDIF								{$$=createCommand2($2,$4,$6);} // nowyyy :D
	| KWHILE condition KDO commands KENDWHILE							{$$=createCommand3($2,$4);}
	| KFOR KPIDENTIFIER KFROM value KTO value KDO commands KENDFOR		{
																			if(searchVeriable($2)!=-1){
																				yyerror("Zmienna jest juz uzyta");
																				printf("Zmienna: %s\n",$2);
																				YYERROR;
																			}
																			$$=createCommand4(useVeriable($2,yylineno), $4,$6,$8 );
																		}
	| KFOR KPIDENTIFIER KFROM value KDOWNTO value KDO commands KENDFOR	{
																			if(searchVeriable($2)!=-1){
																				yyerror("Zmienna jest juz uzyta");
																				printf("Zmienna: %s\n",$2);
																				YYERROR;
																			}
																			$$=createCommand5(useVeriable($2,yylineno), $4,$6,$8 );
																		}
	| KREAD identifier KSR												{$$=createCommand6($2);}
	| KWRITE value KSR													{$$=createCommand7($2);}

expression:
	value 																{$$=createExpression(0,$1,NULL);}
	| value KDOD value 													{$$=createExpression(1,$1,$3);}
	| value KMIN value 													{$$=createExpression(2,$1,$3);}
	| value KRAZ value 													{$$=createExpression(3,$1,$3);}
	| value KDZI value 													{$$=createExpression(4,$1,$3);}
	| value KMOD value 													{$$=createExpression(5,$1,$3);}

condition:
	value KROW value 													{$$=createCondition(0,$1,$3);}
	| value KROZ value													{$$=createCondition(1,$1,$3);}
	| value KMNI value	 												{$$=createCondition(2,$1,$3);}
	| value KWIE value													{$$=createCondition(3,$1,$3);}
	| value KMRO value													{$$=createCondition(4,$1,$3);}
	| value KWRO value													{$$=createCondition(5,$1,$3);}

value:
	KNUMBER 															{declareNumb($1);$$=useValue($1);}
	| identifier														{$$=$1;}

identifier:
	KPIDENTIFIER														{	
																			if(searchVeriable($1)==1){
																				yyerror("Zmienna jest tablica");
																				printf("Zmienna: %s\n",$1);
																				YYERROR;
																			}
																			$$ = useVeriable($1,yylineno);
																		}
	 | KPIDENTIFIER KKLE KPIDENTIFIER KKPR								{	
	 																		int bo = searchVeriable($1);
	 																		if(bo==-1){
	 																			yyerror("Uzycie niezadeklarowanej zmiennej");
	 																			printf("Zmienna: %s\n",$1);
																				YYERROR;
	 																		}
	 																		if(bo==0){
	 																			yyerror("Zmienna nie jest tablica");
	 																			printf("Zmienna: %s\n",$1);
																				YYERROR;
	 																		}
	 																		if(searchVeriable($3)==1){
																				yyerror("Zmienna jest tablica");
																				printf("Zmienna: %s\n",$1);
																				YYERROR;
																			}
	 																		$$ = useVeriableTab($1,useVeriable($3,yylineno),yylineno); 
																		}
	 | KPIDENTIFIER KKLE KNUMBER KKPR 									{
	 																		int bo = searchVeriableTab($1, atoll($3));
	 																		if(bo==-1){
	 																			yyerror("Uzycie niezadeklarowanej zmiennej");
	 																			printf("Zmienna: %s\n",$1);
																				YYERROR;
	 																		}
	 																		if(bo==-2){
	 																			yyerror("Zmienna nie jest tablica");
	 																			printf("Zmienna: %s\n",$1);
																				YYERROR;
	 																		}
	 																		if(bo==-3){
	 																			yyerror("Przekroczony rozmiar tablicy");
	 																			printf("Zmienna: %s\n",$1);
																				YYERROR;
	 																		}
	 																		declareNumb($3);
																			$$=useVeriableTab($1, useValue($3), yylineno); 
	 																	}

%%

char *laczenienapisow(char* str1, char* str2){
	char *result =  malloc(sizeof(char)*(strlen(str1)+strlen(str2)+1));
	strcat(result,str1);
	strcat(result,str2);
	return result;
}

void yyerror(const char *fmt,...){
	printf("\33[2K\rBLAD: %s w lini %d\n",fmt,yylineno);
}
int main(){
		initVeriable();
		yyparse();
}