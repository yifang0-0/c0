/*
#include "func.h"
#define VAR_HASH_SIZE 11
#define VAR_HASH_SHIFT 4
//两个结点是否类型相同
bool isVar(struct ast*a ) {
	
}

bool varTypeEqual( struct ast* a,struct ast*b ) {
	//同为常数或变量
	if (!strcmp( a->type, b->type )) {
		if (!strcmp( a->type, "NAME" )) {
			if (!strcmp( a->i->type, a->i->type )) {
				return true;
			}
		}
		else return true;
	}
	else {
		//一常数一变量
		if (!strcmp( a->type, "NAME" )&& !strcmp( a->i->type, b->type )
			 ||
			 !strcmp( b->type, "NAME" ) && !strcmp( b->i->type, a->type )) {
				return true;
		}
	}
	 return false;
}

bool midOperation( struct ast*  a ) {
	if (!strcmp( a->type, "ASSIGN" )) {
		//输入操作符是赋值
		//赋值符号
		if (!strcmp( a->l->type, "NAME" )) {
			//左操作符是变量
			//在变量表中找出节点变量的地址
			struct ifo* var = buildNewVar( a );
			if (!strcmp(var->type, "NAME" )) {
				if (!strcmp( var->type, a->l->i->type )) {
					*(var->varid) = &(a->r->i->varid);
				}
				else {
				
				}
			}
		}
		else {
		//错误的赋值行为
		}
	}
}
	

struct ifo* buildNewVar( struct ast* a ) {
	//是否已经存在,存在就返回ifo指针，不存在就创造一个
	struct ifo* var = varNotExist( a );
	if (var!=NULL)return var;
	else {
		int indexVa = 0;
		indexVa = hash( a->i->name );
		variable->hashList[indexVa] = a->i;
		return variable->hashList[indexVa];
	}
}

struct ifo* varNotExist( struct ast * a )
{
	struct vaList* vl=variable;
	int indexVa = 0;
	while (vl != NULL) {
		indexVa = hash( a->i->name,  VAR_HASH_SHIFT, VAR_HASH_SIZE );
		if ((vl->hashList[indexVa]) != NULL) {
			return vl->hashList[indexVa];
		}
		vl = vl->nextHashList;
	}
	return NULL;
}




*/