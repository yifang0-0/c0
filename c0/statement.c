#include "dataStructure.h"
/*
���ڶ������ҽ��

*/

Tree createList( const char* name,Tree l, Tree r ) { 
	return newNode( name, l, r, NOP, 0, r->type );
}//������Ҫȡ�����Ҳ��

Tree createListL( const char* name, Tree l, Tree r ) { return newNode( name, l, r, NOP, l->opPr, l->opType ); }


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
	return newNode( "funDec", name, type, NOP, 0, type->type );
}