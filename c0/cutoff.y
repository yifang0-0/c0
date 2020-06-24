%{
/*
#ifndef _UNISTD_H
#define _UNISTD_H 

#include <io.h> 
#include <process.h> 
#endif   */
# include <stdio.h>
# include "c.h"






%}

%union{
struct ast* a;
double d;
}
/*declare tokens*/
%token  <a> INTNUM APPROXNUM STRINGNUM
%token <a> TYPE STRUCT TYPEDEF BREAK CONSTLEX UNION RETURN IF ELSE FOR WHILE NAME SPACE SEMI COMMA ASSIGN RELOP ADDLEX MODLEX SIZEOFLEX UNSIGNEDLEX
SUBLEX STARLEX DIVLEX ANDLEX ORLEX BANDLEX BORLEX BXORLEX NOTLEX LP RP LB RB LSB RSB PS DS AERROR TRUE FALSE VOIDLEX CONTINUE  DO ADDRESS SELFSUB
 SWITCH
%token <a> EOL
%token <a>  FALSELEX TRUELEX
//%token <a> StructSpecifire
%type  <a> Program ExtDefList ExtDef Specifire StructSpecifire UnionSpecifire DefList Def FunDecList fDecList  fDecVar  DecVar 
 VarList Var  Compst STATELIST STATE Exp Args  

/*priority*/
%left COMMA

%right ASSIGN
%left BORLEX
%left ANDLEX
%left ORLEX 
%left ADDLEX SUBLEX
%left STARLEX DIVLEX
%right NOTLEX LP
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
	 |ExtDefList  {printf("syntax tree:\n");eval_print($$,0);printf("syntax tree!\n\n");}
    ;

ExtDefList:
	ExtDef ExtDefList {$$=createListL("ExtDefList",$1,$2);}
	| {$$=createListL("ExtDefList",NULL,NULL);}
	;
ExtDef:
	Specifire SEMI	{$$=newast("ExtDef",2,$1,$2);}
	|Specifire NAME FunDecList Compst	{$$=funcDef($1,$2,$3,0,$4) ; exitscope( );identificaionOffset=0;}
	|Specifire VarList SEMI{$$=varDec( $1,$2, 0 );identificaionOffset=0;}
	|Specifire NAME FunDecList SEMI{$$=funcDef($1,$2,$3,0,NULL);identificaionOffset=0;}
	|CONSTLEX Specifire NAME FunDecList Compst	{$$=funcDef($1,$2,$3,1,$4); exitscope( );identificaionOffset=0;}
	|CONSTLEX Specifire VarList SEMI{$$=varDec( $1, $2, 1 );identificaionOffset=0;}

	;

	
	;
/*Specifire*/
Specifire:TYPE {$$=$1;}
	|UNSIGNEDLEX TYPE {$$=changeToUnsigned($1);}
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
Compst:LB  STATELIST RB {$$=$2; }
STATELIST:
	STATE STATELIST {$$=createListL("STATELIST",$1,$2);}
	|{$$=newast("STATELIST",0,-1);}
STATE:
	//Def {$$=newast("STATE",1,$1);}
	Exp SEMI {$$=$1;temp=0;}//临时变量重设
	|Compst {$$=$1; exitscope( )}
	|DefList {$$=createListL("STATE",$1,NULL);}
	|RETURN  SEMI {$$=Return($1,NULL);}
	|RETURN  EXP SEMI {$$=Return($1,$2);}
	|IF LP Exp RP STATE {$$=ifStatement($5,$3,NULL);}
	|IF LP Exp RP STATE ELSE STATE {$$=ifStatement($5,$3,$7);}
	|WHILE LP Exp RP STATE
	|DO STATE WHILE LP Exp RP SEMI
	|SWITCH LP NAME RP STATE
	|BREAK SEMI
	|CONTINUE SEMI
;

/*Defination*/

DefList:Def DefList  {$$=createList("DefList",$1,$2);}
	|Def{$$=createList( "DefList",$1,NULL);}
	;
Def:
Specifire VarList SEMI {$$=varDec( $1, $2, 0 );}
|CONSTLEX Specifire VarList SEMI {$$=varDec( $2, $3, 1 );}
	;
FunDecList:LP fDecList RP {$$=$2;}
	|LP  RP {$$=NULL;}
	;
fDecList:
fDecVar COMMA fDecList {$$=createList("funcDecList",$1,$3);}
| fDecVar{$$=createList( "funcDec", $1,NULL);}
	;
fDecVar:Specifire Var {$$=funcVarDec( $2,$1,0 ) ;}
|CONSTLEX Specifire Var {$$=funcVarDec( $3,$2,1 );}
	;

	
/*Declaration*/
VarList:DecVar COMMA VarList {$$=createList("varList", $1,$3 );}
	|DecVar {$$=createListL( "varList", $1,NULL);}
	;
DecVar: Var {$$=createListL( "Var", $1,NULL);;}
	|Var ASSIGN Exp{$$=exprOPDouble( $1,$3, $2 );}
	;
Var: NAME {$$=$1;}
	|Var LSB INTNUM RSB {$$=createList( "Array", $1,$3);}
	|Var LSB  RSB {$$=createList( "Array",$1,NULL);}
	;
	//所有Exp的生成都伴随一个临时变量（除非assign）
	Exp:
		//Exp SELFADD  {$$=exprOPSingle($2,$1);}
		//|Exp SELFSUB {$$=exprOPSingle($2,$1);}
		STARLEX Exp {$$=exprOPSingle($1,$2);}
		//|ADDRESS Exp {$$=exprOPSingle($1,$2);}
		|SUBLEX Exp {$$=exprOPSingle($1,$2);}
		|NOTLEX Exp {$$=exprOPSingle($1,$2);}
		//|SELFADD Exp {$$=exprOPSingle($1,$2);}
		//|SELFSUB Exp {$$=exprOPSingle($1,$2);}
		|SIZEOFLEX Exp {$$=exprOPSingle($1,$2);}
		|Exp STARLEX Exp{$$=exprOPDouble($1,$3,$2);}//*
		|Exp DIVLEX Exp{$$=exprOPDouble($1,$3,$2);}//div
		|Exp MODLEX Exp{$$=exprOPDouble($1,$3,$2);}
	    |Exp ADDLEX Exp{$$=exprOPDouble($1,$3,$2);}//+
        |Exp SUBLEX Exp{$$=exprOPDouble($1,$3,$2);}//-
        |Exp RELOP Exp{$$=exprOPDouble($1,$3,$2);}
		|Exp ADDRESS Exp{$$=exprOPDouble($1,$3,$2);}//按位与
		|Exp BXORLEX Exp{$$=exprOPDouble($1,$3,$2);}
		|Exp BORLEX Exp{$$=exprOPDouble($1,$3,$2);}
    	|Exp ANDLEX Exp{$$=exprOPDouble($1,$3,$2);}
		|Exp ORLEX Exp{$$=exprOPDouble($1,$3,$2);}
		|Exp ASSIGN Exp{$$=exprOPDouble($1,$3,$2);}
        |LP Exp RP{$$=$2;}
        |NAME LP Args RP {$$=getFuncName($1,$3);}
        |NAME LP RP {$$=getFuncName($1,NULL);}
        |NAME LSB INTNUM RSB {$$=getArrayName($1,$3);}//NAME[id]
        |NAME {$$=getVarName($1);}
        |INTNUM {$$=setConstants($1);}
        |APPROXNUM{$$=setConstants($1);}
		|STRINGNUM{$$=setConstants($1);}
        ;
Args:Exp COMMA Args {$$=setArgs($1,$3); }
        |Exp {$$=setArgs($1,NULL);}//一个的时候不生成right结点
        ;
%%
 
int main(int ac,char **av)
{
	
	Initial( ) ;
	//yyrestart("")
    yyparse();
}
 
