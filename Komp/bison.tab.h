/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_BISON_TAB_H_INCLUDED
# define YY_YY_BISON_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    KVAR = 258,
    KBEGIN = 259,
    KEND = 260,
    KIF = 261,
    KTHEN = 262,
    KELSE = 263,
    KENDIF = 264,
    KWHILE = 265,
    KDO = 266,
    KENDWHILE = 267,
    KFOR = 268,
    KFROM = 269,
    KTO = 270,
    KDOWNTO = 271,
    KENDFOR = 272,
    KREAD = 273,
    KWRITE = 274,
    KSKIP = 275,
    KSR = 276,
    KPR = 277,
    KDOD = 278,
    KMIN = 279,
    KRAZ = 280,
    KDZI = 281,
    KMOD = 282,
    KROW = 283,
    KROZ = 284,
    KMNI = 285,
    KWIE = 286,
    KMRO = 287,
    KWRO = 288,
    KKLE = 289,
    KKPR = 290,
    KNUMBER = 291,
    KPIDENTIFIER = 292
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 19 "bison.y" /* yacc.c:1909  */

	char* id;
	struct veriable* val;
	struct condition* con;
	struct expression* exp;
	struct command* com;

#line 100 "bison.tab.h" /* yacc.c:1909  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_BISON_TAB_H_INCLUDED  */
