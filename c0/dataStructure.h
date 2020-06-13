#pragma once
//#define VAR_HASH_SIZE 11
//#define VAR_HASH_SHIFT 4
#include <string.h>
# include<stdlib.h>
#include"stdbool.h"
# include<stdio.h>
# include<stdarg.h>
# include "c.h"
/* ������ */

struct ifo {
	// �������������Ϣ
	char *name;
	int* varid;// �����ڱ��еĵ�ַ
	char *type;
	int size;
	int num;
};

/*ast node*/
struct ast {
	union {
		char *idtype;
		int intgr;
		double dou;
		struct ifo *i;
		Value u;
		

	};
	//���������ֵ �������ͣ�ǰ������������ͣ�struct ifo*��
	char type[15];
	Symbol sym;
	Type ty;
	Coordinate info;
	int line;
	struct ast *l;
	struct ast *r;
	Node node;
	int op;
	//�������ֵ�
};
typedef struct ast* Tree;
/* �������ڵ�� */
struct funcList {
	int num;
	struct ast* func;
};


/*
��������ʱ����һ��hash˳�������ȡ����
û���˳�������ʱ����ִ����ž������еı����ͷ��������µĽ�㣬һ���˳���ǰ����Ҫɾ�����
���ʵ��ɾ����ǰ���ڽ�㣿
1.���������һ����־λ����¼�Ƿ�Ϊ��ǰ��ı���
2.ÿ���齨����ͬ��hash��hash�������״����
*/

 int hash( char * key,int HASH_SHIFT,int HASH_SIZE )
{
	int temp = 0;
	int i = 0;
	while (key[i] != '\0')
	{
		temp = ((temp << HASH_SHIFT) + key[i]) % HASH_SIZE;
		++i;
	}
	return temp;
}

struct  vaList {
	struct ifo* hashList[11];
	struct vaList * nextHashList;
};

struct vaList * variable=NULL;
