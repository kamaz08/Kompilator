%option yylineno

%{
	int yywrap(void);
	int lex(void);
	#include <stdio.h>
	#include "bison.tab.h"
%}

%x 					comment

pidentifier			[_a-z]+
whitespace			[ \r\t\v\f]
linefeed			\n
number				[0-9]+

%%

\(					BEGIN(comment);
<comment>\)			BEGIN(INITIAL);
<comment>.			;
<comment>\n 		;
"VAR" 				return KVAR;
"BEGIN"				return KBEGIN;
"END" 				return KEND;
"IF" 				return KIF;
"THEN" 				return KTHEN;
"ELSE"				return KELSE;
"ENDIF" 			return KENDIF;
"WHILE" 			return KWHILE;
"DO" 				return KDO;
"ENDWHILE" 			return KENDWHILE;
"FOR" 				return KFOR;
"FROM" 				return KFROM;
"TO" 				return KTO;
"DOWNTO" 			return KDOWNTO;
"ENDFOR" 			return KENDFOR;
"READ" 				return KREAD;
"WRITE" 			return KWRITE;

";"			return KSR;
":="		return KPR;

"+"			return KDOD;
"-"			return KMIN;
"*"			return KRAZ;
"/"			return KDZI;
"%"			return KMOD;

"="			return KROW;
"<>"		return KROZ;
"<"			return KMNI;
">"			return KWIE;
"<="		return KMRO;
">="		return KWRO;
"["			return KKLE;
"]"			return KKPR;

{number}		{yylval.id = strdup(yytext); return KNUMBER;}
{pidentifier}	{yylval.id = strdup(yytext); return KPIDENTIFIER;}
{linefeed}		;
{whitespace}	;


%%
int yywrap(void){ return 1;}