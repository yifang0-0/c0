%{
 #ifndef _UNISTD_H
#define _UNISTD_H 
#include <io.h> 
#include <process.h> 
#endif   
# include <stdio.h>
#include"cutoff_ast.h"

extern int yylex();
extern int yylineno;
void yyerror( const char *s, ... );

extern char* yytext;
//struct va v[512];
int vaNum;

%}

%union{
struct ast* a;
double d;
}
/*declare tokens*/
%token  <a> INTNUM APPROXNUM STRINGNUM
%token <a> TYPE STRUCT TYPEDEF BREAK CONST UNION RETURN IF ELSE FOR WHILE NAME SPACE SEMI COMMA ASSIGN RELOP ADD SIZEOF UNSIGNED
SUB STAR DIV AND OR DOT NOT LP RP LB RB LSB RSB PS DS AERROR TRUE FALSE 
%token <a> EOL
//%token <a> StructSpecifire
%type  <a> Program ExtDefList ExtVarList ExtDef/*ExtVarDefList ExtOtherDefList ExtOtherDef */ Specifire StructSpecifire UnionSpecifire DefList Def FunDecList fDecList  fDecVar  DecVar
 VarList Var  FunDec Compst STATELIST STATE Exp Args 
 
/*priority*/
%left COMMA
%right ASSIGN
%left OR
%left AND
%left RELOP
%left ADD SUB
%left STAR DIV
%right NOT LP
%left  RP LSB RSB DOT

/*
 %union{
	 struct ast*a;
	 double d;
 }
 %token <d>NUMBER
%token EOL
%type <a> exp factor term 

*/
%%


Program:
	{printf("no input");treefree($$);}
	 |ExtDefList  {$$=newast("Program",1,$1);printf("syntax tree:\n");eval_print($$,0);printf("syntax tree!\n\n");}
    ;

ExtDefList:
	ExtDef ExtDefList {$$=newast("ExtOtherDefList",2,$1,$2);}
	| {$$=newast("ExtDefList",0,-1);}
	;
ExtDef:
	Specifire SEMI	{$$=newast("ExtDef",2,$1,$2);}
	|Specifire FunDec Compst	{$$=newast("ExtDef",3,$1,$2,$3);}
	|Specifire ExtVarList SEMI{$$=newast("ExtDef",3,$1,$2,$3);}
	;
ExtVarList:DecVar COMMA VarList {$$=newast("ExtVarList",3,$1,$2,$3);}
	|DecVar {$$=newast("ExtVarList",1,$1);}
	|FunDec {$$=newast("ExtVarList",1,$1);}
	;
FunDec:NAME FunDecList {$$=newast("FunDec",2,$1,$2);}
	;
/*Specifire*/
Specifire:TYPE {$$=newast("Specifire",1,$1);}
	|StructSpecifire {$$=newast("Specifire",1,$1);}
	|UnionSpecifire {$$=newast("Specifire",1,$1);}
	;
StructSpecifire:STRUCT NAME LSB DefList RSB {$$=newast("StructSpecifire",5,$1,$2,$3,$4,$5);}
	|STRUCT NAME {$$=newast("StructSpecifire",2,$1,$2);}
	;
UnionSpecifire:UNION NAME LSB DefList RSB {$$=newast("UnionSpecifire",5,$1,$2,$3,$4,$5);}
	|UNION NAME {$$=newast("UnionSpecifire",2,$1,$2);}
	;
/*statement*/
Compst:LB  STATELIST RB {$$=newast("Compst",3,$1,$2,$3);}
STATELIST:
	STATE STATELIST {$$=newast("STATELIST",2,$1,$2);}
	|{$$=newast("STATELIST",0,-1);}
STATE:
	//Def {$$=newast("STATE",1,$1);}
	Exp SEMI {$$=newast("STATE",2,$1,$2);}
	|Compst {$$=newast("STATE",1,$1);}
	|DefList {$$=newast("STATE",1,$1);}
	|RETURN Exp SEMI {$$=newast("STATE",3,$1,$2,$3);}
	|IF LP Exp RP STATE {$$=newast("STATE",5,$1,$2,$3,$4,$5);}
	|IF LP Exp RP STATE ELSE STATE {$$=newast("STATE",7,$1,$2,$3,$4,$5,$6,$7);}

/*Defination*/

DefList:Def DefList  {$$=newast("DefList",2,$1,$2);}
	|{printf("this i***********************");$$=newast("DefList",-1);}
	;
Def:
Specifire VarList SEMI {$$=newast("Def",3,$1,$2,$3);}
	;
FunDecList:LP fDecList RP {$$=newast("FunDecList",3,$1,$2,$3);}
	|LP  RP {$$=newast("FunDecList",2,$1,$2);}
	;
fDecList:
fDecVar COMMA fDecList {$$=newast("fDecList",3,$1,$2,$3);}
| fDecVar{$$=newast("fDecList",1,$1);}
	;
fDecVar:Specifire Var {$$=newast("DecVarList",2,$1,$2);}
	;

	
/*Declaration*/
VarList:DecVar COMMA VarList {$$=newast("VarList",3,$1,$2,$3);}
	|DecVar {$$=newast("VarList",1,$1);}
	;
DecVar: Var {$$=newast("DecVar",1,$1);}
	|Var ASSIGN Exp{$$=newast("DecVar",2,$1,$2);}
	;
Var: NAME {$$=newast("Var",1,$1);}
	|Var LSB INTNUM RSB {$$=newast("Var",4,$1,$2,$3,$4);}
	|Var LSB  RSB {$$=newast("Var",3,$1,$2,$3);}
	;
	
Exp:
		Exp SELFADD  {$$=newast("Exp",2,$1,$2);}
		|Exp SELFSUB {$$=newast("Exp",2,$1,$2);}
		|STARLEX Exp {$$=newast("Exp",2,$1,$2);}
		|ADDRESS Exp {$$=newast("Exp",2,$1,$2);}
		|SUBLEX Exp {$$=newast("Exp",2,$1,$2);}
		|NOTLEX Exp {$$=newast("Exp",2,$1,$2);}
		|SELFADD Exp {$$=newast("Exp",2,$1,$2);}
		|SELFSUB Exp {$$=newast("Exp",2,$1,$2);}
		|SIZEOFLEX Exp {$$=newast("Exp",2,$1,$2);}
		|Exp STARLEX Exp{$$=newast("Exp",3,$1,$2,$3);}//*
		|Exp DIVLEX Exp{$$=newast("Exp",3,$1,$2,$3);}//div
		|Exp MODLEX Exp{$$=newast("Exp",3,$1,$2,$3);}
	    |Exp ADDLEX Exp{$$=newast("Exp",3,$1,$2,$3);}//+
        |Exp SUBLEX Exp{$$=newast("Exp",3,$1,$2,$3);}//-
        |Exp RELOP Exp{$$=newast("Exp",3,$1,$2,$3);}
		|Exp ADDRESS Exp{$$=newast("Exp",3,$1,$2,$3);}//按位与
		|Exp BXOR Exp{$$=newast("Exp",3,$1,$2,$3);}
		|Exp BOR Exp{$$=newast("Exp",3,$1,$2,$3);}
    	|Exp ANDLEX Exp{$$=newast("Exp",3,$1,$2,$3);}
		|Exp ORLEX Exp{$$=newast("Exp",3,$1,$2,$3);}
		|Exp ASSIGN Exp{$$=newast("Exp",3,$1,$2,$3);}
        |LP Exp RP{$$=newast("Exp",3,$1,$2,$3);}
        |NAME LP Args RP {$$=newast("Exp",4,$1,$2,$3,$4);}
        |NAME LP RP {$$=newast("Exp",3,$1,$2,$3);}
        |NAME LSB Exp RSB {$$=newast("Exp",4,$1,$2,$3,$4);}//NAME[id]
        |NAME {$$=newast("Exp",1,$1);}
		|Args {$$=newast("Exp",1,$1);}
        |INTNUM {$$=newast("Exp",1,$1);}
        |APPROXNUM{$$=newast("Exp",1,$1);}
		|STRINGNUM{$$=newast("Exp",1,$1);}
        ;
Args:Exp COMMA Args {$$=exprCOMMA(newast("Args",3,$1,$2,$3)) }
        |Exp {$$=newast("Args",1,$1);}//一个的时候不生成right结点
        ;
%%
 
int main(int ac,char **av)
{
	
	
    printf("> ");
	//yyrestart("")
    yyparse();
}
 


/*STATEMENT*/
/*int main(int ac,char av){ printf();yyparse();}
Compst:LB DefList StmtList RB {$$=newast("Compst",4,$1,$2,$3,$4);}
	;
StmtList:Stmt StmtList{$$=newast("StmtList",2,$1,$2);}
	| {$$=newast("StmtList",0,-1);}
	;
Stmt:Exp SEMI {$$=newast("Stmt",2,$1,$2);}
	|Compst {$$=newast("Stmt",1,$1);}
	|RETURN Exp SEMI {$$=newast("Stmt",3,$1,$2,$3);}
	|IF LP Exp RP Stmt {$$=newast("Stmt",5,$1,$2,$3,$4,$5);}
	|IF LP Exp RP Stmt ELSE Stmt {$$=newast("Stmt",7,$1,$2,$3,$4,$5,$6,$7);}
	|WHILE LP Exp RP Stmt {$$=newast("Stmt",5,$1,$2,$3,$4,$5);}
	;
*/