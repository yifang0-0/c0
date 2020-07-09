#include "c.h"

/*
由于逗号是右结合
int main(){int a;int b;a=2;b=3;a=a+b;}
*/
extern int label;
Tree createList( const char* name,Tree l, Tree r ) { 
	if(r==NULL)return newNode( name, l, r, NOP, 0, 0 );
	else return newNode( name, l, r, NOP, r->opPr, r->type );
}//属性需要取得是右侧的

Tree createListL( const char* name, Tree l, Tree r ) { 
	if (l == NULL)return newNode( name, l, r, NOP, 0, 0 );
	else return newNode( name, l, r, NOP, l->opPr, l->opType ); }


Tree setArgs( Tree exp, Tree explist ) {
	Tree Arg = newNode( "ARG", explist, exp, ARG, exp->opType, exp->type );
	
	return Arg;
}
/*
Tree commaVar( const char* name, Tree l, Tree r ) { return newNode( name, l, r, NOP, 0, r->type ); }

Tree arrayVar( const char* name, Tree l, Tree r ) {
	newNode( name, l, r, NOP, 0, r->type );
}
*/
Tree funcVarDec( Tree name, Tree type, int ifconst ) {
	type->opType = type->opType;
	type->type = (!ifconst);
	return newNode( "funDec", type, name, NOP, 0, type->type );
}

Tree ifStatement(Tree state1,Tree exp,Tree state2 ) {
	int lab=label;
	genlabel( 1 );
	Tree jequal=newNode( "CMP", exp, NULL, EQ, 0, 0 );
	jequal->intgr = lab;//表达式正确不跳 不正确跳到label camp eax,0 je 相等（是零）跳转
	Tree label1 = NULL;
	Tree label2 = NULL;
	Tree gotoLabe2 = NULL;
	if (state2 != NULL) {		
		int lab= genlabel( 1 );
		gotoLabe2= newNode( "JUMP", NULL, NULL, JUMP, 0, 0 );
		gotoLabe2->intgr = lab;
		label2= newNode( "LABEL",state2, NULL, LABEL, 0, 0 );
		gotoLabe2->intgr = lab;
	}
	label1=newNode( "LABEL", state1,gotoLabe2 , LABEL, 0, 0 );
	label1->intgr = jequal->intgr;
	//jequal->intgr = lab;
	Tree nop=newNode( "brench", label1, label2, NOP, 0, 0 );
	return newNode( "IF", jequal, nop, NOP, 0, 0 );
}

Tree breakState( Tree brk ) {
	if (roundNow != 0) {
		brk=newNode( "JUMP", NULL, NULL, JUMP, 0, 0 );
		brk->intgr = roundNow;
		roundNow = 0;
		return brk;
	}
	yyerror( "在非循环内使用break\n" );
}
/*
Tree Compst( Tree com ) {
	if (roundNow != 0) {
		Tree brk = newNode( "JUMP", NULL, NULL, JUMP, 0, 0 );
		brk->intgr = roundNow;
		roundNow = 0;
	}
}
*/

Tree Return( Tree ret,Tree exp ) {
		ret = newNode( "RET", exp, NULL, RET, 0, 0 );
	return ret;
}

/*Tree generateCase(Tree exp) {
	//左边造一个 右边造一个
	newNode( "CMP", nop, type, , 0, type->type );
	newNode( "case", nop, type, NOP, 0, type->type );
	return newNode( "case", nop, type, NOP, 0, type->type );
}
Tree switchStatement( ) {
	//左边造一个 右边造一个
	
}*/

