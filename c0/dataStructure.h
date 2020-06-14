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
		//struct ifo *i;
		Value u;
		Symbol sym; //���ż���ȡ���ű����
		Type ty;    //���ͼ���ȡ����		
	};//�������ֵ constant name ��Ҫ�õ����
	//���������ֵ �������ͣ�ǰ������������ͣ�struct ifo*��
	char name[15];//�洢�ڵ�����
	Coordinate info; //�洢�ڵ�λ��
	struct ast *l;
	struct ast *r; //�Ƿ���Ҫָ����һ�����ģ�
	int opPr; //�洢�ڵ㹦��
	int opType;//��������
	//�������ֵ�
	int type;//0const 1���Ʊ��� 2������ʶ�� 3����
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
