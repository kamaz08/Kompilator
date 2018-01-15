%{
#include <stdio.h>
#include <string.h>
#include <math.h>
extern int yylineno;
int yylex(void);
void yyerror(char const *,...);
char *laczenienapisow(char* str1, char* str2);
%}

%union {
	char* x;
	char *id;
	char *num;
}
%type <x> identifier
%type <x> command
%type <x> commands
%type <x> expression
%type <x> value
%type <x> condition
%token KVAR KBEGIN KEND KIF KTHEN KELSE KENDIF KWHILE KDO KENDWHILE KFOR KFROM KTO KDOWNTO KENDFOR KREAD KWRITE KSKIP KSR KPR KDOD KMIN KRAZ KDZI KMOD KROW KROZ KMNI KWIE KMRO KWRO KKLE KKPR;
%token <num> KNUMBER;
%token <id> KPIDENTIFIER;
%%



input:
	program																{printf("zaczynam Program\n");}
	;
program:
	KVAR vdeclarations KBEGIN commands KEND 							{printf("%s\n",$4);}
	;
vdeclarations:
	vdeclarations KPIDENTIFIER											{printf("declaracja\n");}
	| vdeclarations KPIDENTIFIER KKLE KNUMBER KKPR						{printf("declaracja tablicy\n");}
	| %empty															{printf("deklaracja pusta\n");}

commands:
	commands command 													{$$=laczenienapisow(laczenienapisow("KOMENDY ", $1),$2);}
	| command 															{$$=laczenienapisow(laczenienapisow("komenda ", $1),"\n");}

command:
	identifier KPR expression KSR										{$$=laczenienapisow(laczenienapisow("PRZYPISANIE ", $1),$3);	}
	| KIF condition KTHEN commands KELSE commands KENDIF				{$$=laczenienapisow(laczenienapisow($$=laczenienapisow("IF ", $2),$4),$6);}
	| KWHILE condition KDO commands KENDWHILE							{$$=laczenienapisow(laczenienapisow("WHILE ", $2),$4);	}
	| KFOR KPIDENTIFIER KFROM value KTO value KDO commands KENDFOR		{$$=laczenienapisow(laczenienapisow($$=laczenienapisow(laczenienapisow("FOR ", $2),$4), $6),$8);}
	| KFOR KPIDENTIFIER KFROM value KDOWNTO value KDO commands KENDFOR	{$$=laczenienapisow(laczenienapisow($$=laczenienapisow(laczenienapisow("FORD ", $2),$4), $6),$8);}
	| KREAD identifier KSR												{$$=laczenienapisow("READ ", $2);}
	| KWRITE value KSR													{$$=laczenienapisow("WRITE ", $2);	}
	| KSKIP KSR															{$$="SKIP ";}

expression:
	value 																{$$=laczenienapisow("WARTOSC ", $1);				}
	| value KDOD value 													{$$=laczenienapisow(laczenienapisow("DODWANIE ", $1),$3);	}
	| value KMIN value 													{$$=laczenienapisow(laczenienapisow("ODEJMOWANIE  ", $1),$3);	}
	| value KRAZ value 													{$$=laczenienapisow(laczenienapisow("ROWNE ", $1),$3);	}
	| value KDZI value 													{$$=laczenienapisow(laczenienapisow("DZIELENIE ", $1),$3);	}
	| value KMOD value 													{$$=laczenienapisow(laczenienapisow("MOD ", $1),$3);		}

condition:
	value KROW value 													{$$=laczenienapisow(laczenienapisow("ROWNE ", $1),$3);	}
	| value KROZ value													{$$=laczenienapisow(laczenienapisow("ROZNE ", $1),$3);	}
	| value KMNI value	 												{$$=laczenienapisow(laczenienapisow("MNIEJSZE  ", $1),$3);	}
	| value KWIE value													{$$=laczenienapisow(laczenienapisow("WIEKSZE  ", $1),$3);	}
	| value KMRO value													{$$=laczenienapisow(laczenienapisow("MNIEJSZE ROWNE ", $1),$3); }
	| value KWRO value													{$$=laczenienapisow(laczenienapisow("WIEKSZE ROWNE ", $1),$3);	}

value:
	KNUMBER 															{$$="LICZBA ";			}
	| identifier														{$$="WARTOSC ZMIENNA ";	}

identifier:
	KPIDENTIFIER														{$$="ZMIENNA ";	}
	 | KPIDENTIFIER KKLE KPIDENTIFIER KKPR								{$$="ZMIENNA TABLIC ";	}
	 | KPIDENTIFIER KKLE KNUMBER KKPR 									{$$="ZMIENNA TABLICA WARTOSC ";	}

// exp:
// 	NUM 				{printf("%dkurde",$1); $$ = $1;}
// 	| VAR				{printf("hahahaha");}
// 	| exp '+' exp 		{printf("+ ");$$ = $1 + $3;}
// 	| exp '-' exp		{printf("- ");$$ = $1 - $3;}
// 	| exp '*' exp		{printf("* ");$$ = $1 * $3;}
// 	| exp '/' exp		{if($3){printf("/ ");$$ = $1 / $3;}else {yyerror("Dzielenie przez 0");YYERROR;}}
// 	| '-' NUM %prec NEG	{printf("-%d ",$2);$$ =-$2;}
// 	| exp '^' exp		{printf("^ ");$$ = pow($1,$3);}
// 	| exp '%' exp		{printf("%% ");$$ = ($1 % $3 + $3) % $3;}
// 	| '(' exp ')'		{$$ = $2;}
// 	;
%%




char *laczenienapisow(char* str1, char* str2){
	char *result =  malloc(sizeof(char)*(strlen(str1)+strlen(str2)+1));
	strcat(result,str1);
	strcat(result,str2);
	return result;
}
void yyerror(const char *fmt,...){
	printf("\33[2K\rBLAD: %s\n",fmt);
}
int main(){

		yyparse();
}