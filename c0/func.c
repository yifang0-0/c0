/*
#include "func.h"
#define VAR_HASH_SIZE 11
#define VAR_HASH_SHIFT 4
//��������Ƿ�������ͬ
bool isVar(struct ast*a ) {
	
}

bool varTypeEqual( struct ast* a,struct ast*b ) {
	//ͬΪ���������
	if (!strcmp( a->type, b->type )) {
		if (!strcmp( a->type, "NAME" )) {
			if (!strcmp( a->i->type, a->i->type )) {
				return true;
			}
		}
		else return true;
	}
	else {
		//һ����һ����
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
		//����������Ǹ�ֵ
		//��ֵ����
		if (!strcmp( a->l->type, "NAME" )) {
			//��������Ǳ���
			//�ڱ��������ҳ��ڵ�����ĵ�ַ
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
		//����ĸ�ֵ��Ϊ
		}
	}
}
	

struct ifo* buildNewVar( struct ast* a ) {
	//�Ƿ��Ѿ�����,���ھͷ���ifoָ�룬�����ھʹ���һ��
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