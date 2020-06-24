/* A Bison parser, made by GNU Bison 2.7.  */

/* Bison interface for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2012 Free Software Foundation, Inc.
   
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

#ifndef YY_YY_CUTOFF_TAB_H_INCLUDED
# define YY_YY_CUTOFF_TAB_H_INCLUDED
/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     INTNUM = 258,
     APPROXNUM = 259,
     STRINGNUM = 260,
     TYPE = 261,
     STRUCT = 262,
     TYPEDEF = 263,
     BREAK = 264,
     CONSTLEX = 265,
     UNION = 266,
     RETURN = 267,
     IF = 268,
     ELSE = 269,
     FOR = 270,
     WHILE = 271,
     NAME = 272,
     SPACE = 273,
     SEMI = 274,
     COMMA = 275,
     ASSIGN = 276,
     RELOP = 277,
     ADDLEX = 278,
     MODLEX = 279,
     SIZEOFLEX = 280,
     UNSIGNEDLEX = 281,
     SUBLEX = 282,
     STARLEX = 283,
     DIVLEX = 284,
     ANDLEX = 285,
     ORLEX = 286,
     BANDLEX = 287,
     BORLEX = 288,
     BXORLEX = 289,
     NOTLEX = 290,
     LP = 291,
     RP = 292,
     LB = 293,
     RB = 294,
     LSB = 295,
     RSB = 296,
     PS = 297,
     DS = 298,
     AERROR = 299,
     TRUE = 300,
     FALSE = 301,
     VOIDLEX = 302,
     CONTINUE = 303,
     DO = 304,
     ADDRESS = 305,
     SELFSUB = 306,
     SWITCH = 307,
     EOL = 308,
     FALSELEX = 309,
     TRUELEX = 310,
     DOT = 311
   };
#endif


#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{
/* Line 2058 of yacc.c  */
#line 19 "cutoff.y"

struct ast* a;
double d;


/* Line 2058 of yacc.c  */
#line 119 "cutoff.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */

#endif /* !YY_YY_CUTOFF_TAB_H_INCLUDED  */
