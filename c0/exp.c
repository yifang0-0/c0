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

��δ�����ʱ�� int\double����Ϊ��ʱ��������
*/
#include "datastructure.h"
/*������ʲô�����������������е�exp�����󣬶�����ѽ���浽eax������Ϊ�Ҳ��������浽ebx��*/

//��������
//ֻ����涨�ļ򵥲�����
//���������ӵ�exp�����ǵ�ǰ���ɲ����ģ���ζ�����в�����Ҫ�鿴�Լ���ǰ��
//���ﻹȱ������ת�����Ȳ�ʵ�֣��ȵ������ܳ����ٴ�����
//SUBLEX:XOR %eax 0xffffffff
//		 INC EAX
//NOTLEX:CMP EAX 0
Tree exprOPSingle( Tree oprand, Tree op ){
	 if (!strcmp( op->name, "SUBLEX" )|| !strcmp( op->name, "NOTLEX" )) {
		//ȡ����
		if (oprand->opType <= FLOAT) {
			//�����ǳ������Ǳ��������Բ�������
			op->l=oprand;
			op->opType = oprand->opType;
			return op;
		}
		else
		{
			yyerror("�������ʹ��󣬲��ɶԵ�ǰ���ݽ��в���" );
			return NULL;
		}
	}
	else if (!strcmp( op->name, "SIZEOFLEX" )) {
		 op->l = oprand;
		//���ʹ�С
	}
	/*else if (!strcmp( op->name, "" ) {

	}
	else if (!strcmp( op->name, "" ) {

	}*/
}
Tree exprOPDouble( Tree oprand1, Tree oprand2, Tree op ) {

	if (!strcmp( op->name, "MODLEX" )) {

		if (oprand1->type <= 1 && oprand2->type <= 1 && oprand1->opType < FLOAT && oprand1->opType < FLOAT) {
			if (oprand2->type == 0 && (oprand2->u.ifdiv == 1) || oprand2->type == 1 && (oprand2->sym->ifdiv == 1))
			{
				yyerror( "ģ�����\n" );
			}
			else {
				op->r = oprand1->opType < oprand2->opType ? oprand1 : oprand2;
				op->l = oprand1->opType < oprand2->opType ? oprand2 : oprand1;
				op->opPr = MOD;
				op->opType = op->r->opType;
				op->type = 0;//�����ܽ��и�ֵ����
				if (oprand1->opType != oprand2->opType) {
					//�����Ҫ����ת�� ����һ���½ڵ� ��������ת�� ���ӽڵ�ָ���ת��ֵ��Ŀ��ֵ��CVXX
				//���øò���
					Tree a = newNode( "TRA", op->l, NULL, CVC - 1 + op->l->opType, op->r->opType, op->l->type );
					op->l = a;
				}
			}
		}
		else
		{
			yyerror( "���в����������\n" );
			return NULL;
		}
	}
	else if (!strcmp( op->name, "ADDLEX" ) || !strcmp( op->name, "SUBLEX" ) || !strcmp( op->name, "STARLEX" ) || !strcmp( op->name, "DIVLEX" )) {
		if (!strcmp( op->name, "ADDLEX" ))op->opPr = ADD;
		else if (!strcmp( op->name, "STARLEX" )) {
			op->opPr = MUL;
			if (oprand1->opType == POINTER && oprand2->opType < FLOAT || oprand2->opType == POINTER && oprand1->opType < FLOAT)
			{
				if (oprand1->opType == POINTER)
				{
					op->r = oprand1;
					op->l = newNode( "LSH", oprand2, newNode( "instant", NULL, NULL, 0, 2, 0 ), LSH, oprand2->opType, 0 );
					op->l->type = 0;
				}
				else
				{
					op->r = oprand2;
					op->l = newNode( "LSH", oprand1, newNode( "instant", NULL, NULL, 0, 2, 0 ), LSH, oprand1->opType, 0 );
					op->l->type = 0;
				}
				//ָ��Ӽ�
				//mov $1,addr
				//lsh $1 ,2
				//mov $2 ,addrp
				//add $2,$1
				return op;
			}
			else {
				yyerror( "ָ���������" );
				return NULL;
			}
		}
		else if (!strcmp( op->name, "DIVLEX" ))
		{
			if ((oprand2->type == 0 && (oprand2->u.ifdiv == 1) || oprand2->type == 1 && (oprand2->sym->ifdiv == 1)))
			{
				yyerror( "ģ�����\n" );
				return NULL;
			}
			else
				op->opPr = DIV;
		}
		else op->opPr = SUB;
		if (oprand1->type <= 1 && oprand2->type <= 1) {
			if (oprand1->opType <= FLOAT && oprand1->opType <= FLOAT)
			{
				op->r = oprand1->opType < oprand2->opType ? oprand1 : oprand2;
				op->l = oprand1->opType < oprand2->opType ? oprand2 : oprand1;
				op->opType = op->r->opType;
				op->type = 0;//�����ܽ��и�ֵ����
				if (oprand1->opType != oprand2->opType) {
					//�����Ҫ����ת�� ����һ���½ڵ� ��������ת�� ���ӽڵ�ָ���ת��ֵ��Ŀ��ֵ��CVXX
				//���øò���
					Tree a = newNode( "TRA", op->l, NULL, CVC - 1 + op->l->opType, op->r->opType, op->l->type );
					op->l = a;
				}
			}
			return op;
		}
		else
		{
			yyerror( "" );
			return NULL;
		}
	}
	else if (!strcmp( op->name, "RELOP" )) {
		//�߼��Ƚ� 

		if (!strcmp( op->idtype, "!=" )) {
			op->opPr = NE; strcpy( op->name, "NE" );
		}
		else if (!strcmp( op->idtype, ">=" )) {
			op->opPr = GE; strcpy( op->name, "GE" );
		}
		else if (!strcmp( op->idtype, ">" )) {
			op->opPr = GT;strcpy( op->name, "GT" );
		}
		else if (!strcmp( op->idtype, "<=" )) {
			op->opPr = LE; strcpy( op->name, "LE" );
		}
		else if (!strcmp( op->idtype, "<" )) {
			op->opPr = LT; strcpy( op->name, "LT" );
		}
		else if (!strcmp( op->idtype, "==" )) {
			op->opPr = EQ;strcpy( op->name, "EQ" );
		}
		else {
			yyerror( "δ֪����\n" );
		}
		if (oprand1->type <= 1 && oprand2->type <= 1) {
			if (oprand1->opType <= FLOAT && oprand1->opType <= FLOAT)
			{
				op->r = oprand1->opType < oprand2->opType ? oprand1 : oprand2;
				op->l = oprand1->opType < oprand2->opType ? oprand2 : oprand1;
				op->opType = op->l->opType;
				op->type = 0;//�����ܽ��и�ֵ����
				if (oprand1->opType != oprand2->opType) {
					//�����Ҫ����ת�� ����һ���½ڵ� ��������ת�� ���ӽڵ�ָ���ת��ֵ��Ŀ��ֵ��CVXX
				//���øò���
					op->l = newNode( "TRA", op->l, NULL, CVC - 1 + op->l->opType, op->r->opType, op->l->type );
					//op->l = a;
				}
			}
			return op;
		}
		else {
			yyerror( "�ڵ㲻�ɲ���\n" );
		}
	}
	else if (!strcmp( op->name, "BXOR" ) || !strcmp( op->name, "BOR" ) || !strcmp( op->name, "BAND" )) {
		if (oprand1->type <= 1 && oprand2->type <= 1) {
			if (!strcmp( op->name, "BXOR" ))op->opPr = BXOR;
			else if (!strcmp( op->name, "BOR" ))op->opPr = BOR;
			else if (!strcmp( op->name, "BAND" ))op->opPr = BAND;

			if (oprand1->opType < FLOAT && oprand1->opType < FLOAT)
			{
				op->r = oprand1->opType < oprand2->opType ? oprand1 : oprand2;
				op->l = oprand1->opType < oprand2->opType ? oprand2 : oprand1;

				op->opType = op->r->opType;//op���Ҳ������Ǹ��߼�������
				op->type = 0;//�����ܽ��и�ֵ����
				if (oprand1->opType != oprand2->opType) {
					//�����Ҫ����ת�� ����һ���½ڵ� ��������ת�� ���ӽڵ�ָ���ת��ֵ��Ŀ��ֵ��CVXX
				//���øò���
					Tree a = newNode( "TRA", op->l, NULL, CVC - 1 + op->l->opType, op->r->opType, op->l->type );
					op->l = a;

				}
			}
			else {
				yyerror( "ָ���������" );
				return NULL;
			}
		}
		else
		{
			yyerror( "" );
			return NULL;
		}
	}
	else if (!strcmp( op->name, "ASSIGN" )) {
		if (oprand1->sym == NULL  ) {
			//��ʱ�������������
			op->r = oprand2;
			op->l = oprand1;
			op->opPr = ASGN;
			op->opType = op->l->opType;//���������Ǹ�����������
			op->type = 0;//�����ܽ��и�ֵ����
			return op;
		}
		else if (oprand1->type == 1 && oprand2->type <= 1) {
			op->r = oprand2;
			op->l = oprand1;
			//��������һ��INDIR��ɾ���ýڵ㣬ָ������ڵ�
			op->opPr = ASGN;
			op->opType = op->l->opType;//���������Ǹ�����������
			op->type = 0;//�����ܽ��и�ֵ����
			if (oprand1->opType != oprand2->opType) {
				//�����Ҫ����ת�� ����һ���½ڵ� ��������ת�� ���ӽڵ�ָ���ת��ֵ��Ŀ��ֵ��CVXX
			//���øò���
				Tree a = newNode( "TRA", op->r, NULL, CVC - 1 + op->r->opType, op->l->opType, op->l->type );
				//�����ڵ��Ҳ�����ת��Ϊ���ģ����ܶ�ʧ���ȣ��Ҳ�����
				op->r = a;
			}
			return op;
		}
		else
		{
			yyerror( "��ֵ���ɸ�ֵ������ֵ������\n" );
			return NULL;
		}
	}
	else if (!strcmp( op->name, "ORLEX" ) || !strcmp( op->name, "ANDLEX" )) {
		//�ҵ�ͷ��Ҫ�Ӳ����ϵ�������
		// ����
		//���ֵ֮��ıȽ�
		//������0
		//��������
		//cmp
		//jne/je assLine+2
		//cmp
		//assLine+2:��ǰ���
		if (oprand1->type <= 1 && oprand2->type <= 1) {
			op->l = oprand1;
			op->r = oprand2;
			op->type = 0;
			op->opType = CONST;
			if (!strcmp( op->name, "ORLEX" )) {
				//��������cmp��jump,������Ϊ�٣�cmp op1 0;jne �¶������assLine+2;cmp op2 0 ��
				op->opPr = NE;
			}
			else {
				//��������cmp��һ��je,������Ϊ�棨cmp op1 0;je assLine+2��������䣨������һ�䣩;cmp op2 0 ��
				op->opPr = EQ;
			}
		}
		else {
			yyerror( "����δ����\n" );
		}
	}
}
Tree getVarName( Tree name ) {
	//�����һ������
	if (name->type == 1) {
		if (name->sym == lookup( name->idtype, identifiers )) {
			//�����Ѷ���
			Tree addrl=newNode( "ADDRL", NULL, NULL, ADDRL, POINTER, 3 );
			addrl->sym = name->sym;
			//��ʱֻ���Ǳ���λ�ã�type��Ϣ������type��������
			return newNode( "INDIR", addrl, NULL, INDIR, name->opType, 3 );
		}
	}
	else if (name->type == 0) {
		if (name->sym == lookup( name->idtype, constants )) {
			//�����ǳ���
		//	���ҵ�
			Tree addrl = newNode( "ADDRG", NULL, NULL, ADDRL, POINTER, 3 );
			addrl->sym = name->sym;
			//��ʱֻ���Ǳ���λ�ã�type��Ϣ������type��������
			return newNode( "INDIR", addrl, NULL, INDIR, name->opType, 3 );

		}
	}
	else {
		yyerror( "δ����ı���" );
	}
	//ȥ����ȡƫ��ֵ
	//ָ��
		//ȡ��ַ
		//�ӵ�ַȡ��
}
Tree getFuncName( Tree name, Tree explist ) {
	//������ں��������ҵ���ǰ�ĺ���
	//�����½��CALL
	//CALL->l=�����ձ���
	//�ձ������ָ��ARG�б�
	if (name->opPr == FUNCTION) {
		//��ǰ�����Ǻ�����
		Tree arfReturn = NULL;
		if (name->opType != VOID) {
			arfReturn = newNode( "PUSH", NULL, NULL, PUSH, name->type, 3 );
		}
		Tree nop= newNode( "nop", explist, arfReturn, CALL, name->ty, 2 );
		Tree addrl = newNode( "CALL", nop, NULL, CALL,name->ty, 2 );
	}
	
	//CALL��ʱ�������ѹȫ����ջ��jump�����

	//����ARG������ѹջn��

	//CALL->l->r�ǲ���ƫ������ÿ��������һ���趨numofvar

	//��Ҫ������� ֱ��pop����
	//mov��һ���ڴ�ֵ

	//POPȫ���Ĵ���������ָ�����


}
Tree getArrayName( Tree name,Tree index ) {
	//�����һ������������һ������
	//ȥ����ȡƫ��ֵ
	//�Ӳ����л����һƫ����
	//ָ��
		//ȡ��ַ
		//�ӵ�ַ+ƫ����ȡ��
	//NAME����addr 
	Tree addrl = newNode( "ADDRG", name, NULL, ADDRG, name->ty->type->op, 0);//ע����������ʱ��name->ty->op�����ARRAY,name->ty->type->op�����Ԫ�ص�����
	Tree int4 = newNode( "CNST", index, NULL, CNST, INT, 0 );
	int4->intgr = index->intgr << 2;
	Tree add = newNode( "ADD", addrl, int4, ADD, INT, 0 );
	//��ʱֻ���Ǳ���λ�ã�type��Ϣ������type��������
	return newNode( "INDIR", add, NULL, INDIR, name->ty->type->op, name->type );

}
/*���ɵĲ����ڵ��ұ��ǵ������ʽ������Ǳ��ʽ�б�,�����NULLʱ˵���Ѿ�û�в���
	�ڵ������ARG�������ֽڴ�Сpush
	Ҫ�㣺�������
*/

Tree setConstants( Tree cons ) {
	//û�д��constants������ͨ��constants�е������ڿ�ʼ���ǰ����DATA��
	if (!strcmp( cons->name, "INTNUM" )) {
		strcpy( cons->name, "CNST" );
		cons->opType = 0;
		cons->opPr = INT;
		cons->type = 0;
		//ֱ����Ϊ������ʹ��
		return cons;

	}
	else if(!strcmp( cons->name, "APPROXNUM" )) {
		strcpy( cons->name, "CNST" );
		cons->opType = 0;
		cons->opPr = FLOAT;
		cons->type = 0;
		//ֱ����Ϊ������ʹ��
		return cons;
	}
	else
	{
		Tree addrl = newNode( "ADDRG", cons, NULL, ADDRG,ARRAY , 0 );
		addrl->ty = arrayType( chartype, strlen(cons->str->len), 1 );
		cons->opType = CHAR;
		cons->type = 0;
		//��ʱֻ���Ǳ���λ�ã�type��Ϣ������type��������
		return newNode( "INDIR", addrl, NULL, INDIR, ARRAY, 0 );
		
	}
	
}
//ֱ��������ƥ���ʱ����õ�constant������ɻ���ʱ����constant