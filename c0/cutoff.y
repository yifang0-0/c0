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
	 |ExtDefList  {typeInit();$$=newast("Program",1,$1);printf("syntax tree:\n");eval_print($$,0);printf("syntax tree!\n\n");}
    ;

ExtDefList:
	ExtDef ExtDefList {$$=newast("ExtOtherDefList",2,$1,$2);}
	| {$$=newast("ExtDefList",0,-1);}
	;
ExtDef:
	Specifire SEMI	{$$=newast("ExtDef",2,$1,$2);}
	|Specifire NAME FunDecList Compst	{$$=funcDef($1,$2,$3,0,$4) ;}
	|Specifire VarList SEMI{$$=varDec( $1,$2, 1 );}
	|Specifire NAME FunDecList SEMI{$$=funcDef($1,$2,$3,0,NULL);}
	|CONST Specifire NAME FunDecList Compst	{$$=funcDef($1,$2,$3,1,$4);}
	|CONST Specifire VarList SEMI{$$=varDec( $1, $2, 1 );}

	;

	
	;
/*Specifire*/
Specifire:TYPE {$$=$1;}
	|UNSIGNED TYPE {$$=changeToUnsigned($1);
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

DefList:Def DefList  {$$=createList("DefList",$1,$2);}
	|Def{$$=createList( "DefList",$1,NULL);}
	;
Def:
Specifire VarList SEMI {$$=varDec( $1, $2, 0 );}
|CONST Specifire VarList SEMI {$$=varDec( $2, $3, 1 );}
	;
FunDecList:LP fDecList RP {$$=$2;}
	|LP  RP {$$=NULL;}
	;
fDecList:
fDecVar COMMA fDecList {$$=createList("funcDecList",$1,$3);}
| fDecVar{$$=createList( "funcDec", $1,NULL);}
	;
fDecVar:Specifire Var {$$=funcVarDec( $2,$1,0 ) ;}
|CONST Specifire Var {$$=funcVarDec( $3,$2,1 );}
	;

	
/*Declaration*/
VarList:DecVar COMMA VarList {$$=createList("VarList", $1,$3 );}
	|DecVar {$$=createListL( "VarList", $1,NULL);}
	;
DecVar: Var {$$=createListL( "Var", $1,NULL);;}
	|Var ASSIGN Exp{$$=exprOPDouble( $1,$3, $2 );}
	;
Var: NAME {$$=$1;}
	|Var LSB Exp RSB {$$=createList( "Array", $1,$3);}
	|Var LSB  RSB {$$=createList( "Array",$1,NULL);}
	;
	
Exp:
		Exp SELFADD  {$$=exprOPSingle($2,$1);}
		|Exp SELFSUB {$$=exprOPSingle($2,$1);}
		|STARLEX Exp {$$=exprOPSingle($1,$2);}
		|ADDRESS Exp {$$=exprOPSingle($1,$2);}
		|SUBLEX Exp {$$=exprOPSingle($1,$2);}
		|NOTLEX Exp {$$=exprOPSingle($1,$2);}
		|SELFADD Exp {$$=exprOPSingle($1,$2);}
		|SELFSUB Exp {$$=exprOPSingle($1,$2);}
		|SIZEOFLEX Exp {$$=exprOPSingle($1,$2);}
		|Exp STARLEX Exp{$$=exprOPDouble($1,$3,$2);}//*
		|Exp DIVLEX Exp{$$=exprOPDouble($1,$3,$2);}//div
		|Exp MODLEX Exp{$$=exprOPDouble($1,$3,$2);}
	    |Exp ADDLEX Exp{$$=exprOPDouble($1,$3,$2);}//+
        |Exp SUBLEX Exp{$$=exprOPDouble($1,$3,$2);}//-
        |Exp RELOP Exp{$$=exprOPDouble($1,$3,$2);}
		|Exp ADDRESS Exp{$$=exprOPDouble($1,$3,$2);}//按位与
		|Exp BXOR Exp{$$=exprOPDouble($1,$3,$2);}
		|Exp BOR Exp{$$=exprOPDouble($1,$3,$2);}
    	|Exp ANDLEX Exp{$$=exprOPDouble($1,$3,$2);}
		|Exp ORLEX Exp{$$=exprOPDouble($1,$3,$2);}
		|Exp ASSIGN Exp{$$=exprOPDouble($1,$3,$2);}
        |LP Exp RP{$$=$2;}
        |NAME LP Args RP {$$=getFuncName($1,$3);}
        |NAME LP RP {$$=getFuncName($1,NULL);}
        |NAME LSB Exp RSB {$$=getArrayName($1,$3);}//NAME[id]
        |NAME {$$=getVarName($1)}
        |INTNUM {$$=setContants($1);}
        |APPROXNUM{$$=setContants($1);}
		|STRINGNUM{$$=setContants($1);}
        ;
Args:Exp COMMA Args {$$=setArgs($1,$3); }
        |Exp {$$=setArgs($1,NULL);}//一个的时候不生成right结点
        ;
%%
 
int main(int ac,char **av)
{
	
	
    printf("> ");
	//yyrestart("")
    yyparse();
}
 
