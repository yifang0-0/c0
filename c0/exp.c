/*
//���ʽ�ļ���Ҫ���������֪��symbol�Ĵ���
1.���ͼ�顢ת��
2.��顢���·��ű�ת����
3.NAME�Ƿ��������ű��У���ǰscope��
4.������������������ͣ�ADD->ADDI,g����opֵ
������
expr1(���������������Լ���sizeof��ǿ������ת��)
expr2(˫������+=*%/ �߼��ȽϷ�)
expr3(:? ����ѡ�������û�����ô��������)

*/
#include "datastructure.h"
Tree exprCOMMA(Tree right ) {
	right->ty = right->l->r->ty;
	right->sym = right->l->r->sym;
	right->op = RIGHT;
	return right;
}