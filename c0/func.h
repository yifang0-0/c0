#pragma once
#include "string.h"
#include"dataStructure.h"
//���ڴ洢���Ͷ��壬�������������ͱ�
bool isVar( struct ast*a );
//�����б���
bool typeChecker( struct ast* a );
//����ת����
//������ֵ
bool varAssign( struct ast* a );
//���ʽ
	//�м������
bool midOperation( struct ast* a);

void* buildNewVar( struct ast* a );

struct ifo* varNotExist( struct ast* a );

struct ifo* searchVar( char *a );
