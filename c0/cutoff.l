/* Companionsource code for "flex & bison", published by O'Reilly
* Media, ISBN 978-0-596-15597-1
* Copyright (c) 2009, Taughannock Networks.All rights reserved.
* See the README file for license conditionsand contact info.
* %option yylineno
这个文件只处理数字算了 
好像不行···只能写到一处
*/
 
/* recognizetokens for the calculator and print them out */
 
%{
# include "cutoff.tab.h"

# include "cutoff_ast.h"

# include <stdio.h>
# include <math.h>
# include <stdlib.h>
extern char* token;
extern Symbol tsym;
extern Coordinate src;
static struct symbol tval;
char *file;	
char *firstfile;	
%}
%option yylineno noyywrap 

SPACE [ \t\r]*

%%
\"([^\"]*)\" { yylval.a=newast("STRINGNUM",0,yylineno);
							return STRINGNUM;}
0|-?[1-9][0-9]* { yylval.a=newast("INTNUM",0,yylineno); return INTNUM; }
-?[0-9]+"."[0-9]* {yylval.a=newast("APPROXNUM",0,yylineno);return APPROXNUM;}
"char"|"int"|"bool"|"double"|"string" {yylval.a=newast("TYPE",0,yylineno);return TYPELEX;}
"TRUE"  {yylval.a=newast("TRUE",0,yylineno);return TRUELEX;}
"FALSE"  {yylval.a=newast("FALSE",0,yylineno);return FALSELEX;}

"unsigned" {yylval.a=newast("UNSIGNED",0,yylineno);return UNSIGNEDLEX;}
"sizeof"  {yylval.a=newast("SIZEOF",0,yylineno);return SIZEOFLEX;}
"struct" {yylval.a=newast("STRUCT",0,yylineno);return STRUCTLEX;}
"union" {yylval.a=newast("UNION",0,yylineno);return UNIONLEX;}
"const" {yylval.a=newast("CONST",0,yylineno);return CONSTLEX;}
"typedef" {yylval.a=newast("TYPEDEF",0,yylineno);return TYPEDEFLEX;}
"break" {yylval.a=newast("BREAK",0,yylineno);return BREAK;}
"for" {yylval.a=newast("FOR",0,yylineno);return FOR;}
"while" {yylval.a=newast("WHILE",0,yylineno);return WHILE;}
"else" {yylval.a=newast("ELSE",0,yylineno);return ELSE;}
"if" {yylval.a=newast("IF",0,yylineno);return IF;}
"return"  {yylval.a=newast("RETURN",0,yylineno);return RETURN;}

"+" { yylval.a=newast("ADD",0,yylineno);yylval.a->op=ADD;return ADDLEX; }
"-" { yylval.a=newast("SUB",0,yylineno);yylval.a->op=SUB;return SUBLEX; }
"*" { yylval.a=newast("STAR",0,yylineno);yylval.a->op=STAR;return STARLEX; }
"/" { yylval.a=newast("DIV",0,yylineno);yylval.a->op=DIV;return DIVLEX; }
"#"  {yylval.a=newast("PS",0,yylineno);return PS;}
"%"  {yylval.a=newast("MOD",0,yylineno);yylval.a->op=MOD;return MODLEX;}
"," {yylval.a=newast("COMMA",0,yylineno);return COMMA;}
"!" {yylval.a=newast("NOT",0,yylineno);yylval.a->op=NOT;return NOTLEX;}
"&"	{yylval.a=newast("ADDRESS",0,yylineno);yylval.a->op=ADDR; return ADDRESS;}
"|"	{yylval.a=newast("BOR",0,yylineno);yylval.a->op=BOR; return BOR;}
"^"	{yylval.a=newast("BXOR",0,yylineno);yylval.a->op=BXOR; return BXOR;}
>|<|>=|<=|==|!= {yylval.a=newast("RELOP",0,yylineno); return RELOP;}
[&][&]	{yylval.a=newast("AND",0,yylineno);yylval.a->op=AND; return ANDLEX;}
[|][|]	{yylval.a=newast("OR",0,yylineno);yylval.a->op=OR; return ORLEX;}
[+][+]	{yylval.a=newast("SELFADD",0,yylineno);yylval.a->op=ADD; return SELFADD;}
[-][-]	{yylval.a=newast("SELFSUB",0,yylineno);yylval.a->op=SUB; return SELFSUB;}
"=" {yylval.a=newast("ASSIGN",0,yylineno);yylval.a->op=INDIR; return ASSIGN;}
";"	{yylval.a=newast("SEMI",0,yylineno); return SEMI;}
"{"	{yylval.a=newast("LB",0,yylineno); return LB;}
"}"	{yylval.a=newast("RB",0,yylineno); return RB;}
"("	{yylval.a=newast("LP",0,yylineno); return LP;}
")"	{yylval.a=newast("RP",0,yylineno); return RP;}
"["	{yylval.a=newast("LSB",0,yylineno); return LSB;}
"]"	{yylval.a=newast("RSB",0,yylineno); return RSB;}

{SPACE} {src.x=0;}


[A-Za-z][A-Za-z0-9]* {yylval.a=newast("NAME",0,yylineno);
							return NAME;}
. { printf("lex Unknown character = '%s'", yytext); yyerror("lex Unknown character"); }
%%
/*
int main(int ac,char **av)
{
	FILE *f;
	firstfile=av[0];
	
	file=firstfile;
	if(ac==1){
		f=fopen(file,"r");
		yydebug = 1;
		ac--;av++;
	}
	else{
		for(int i=1;i<ac;i++){
		file=av[i-1];
		f=fopen(file,"r");
		bp=yy_create_buffer(f,YY_BUF_SIZE);
		yy_switch_to_buffer(bp);
		//读取文件的内容
		yyparse();
		yy_flush_buffer(bp);
		yy_delete_buffer(bp);
		if(file[i-1][0]=='-')break;
		}		
		return 1;
	}
	

	
}*/