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
#include "c.h"
/*������ʲô�����������������е�exp�����󣬶�����ѽ���浽eax������Ϊ�Ҳ��������浽ebx��*/

//��������
//ֻ����涨�ļ򵥲�����
//���������ӵ�exp�����ǵ�ǰ���ɲ����ģ���ζ�����в�����Ҫ�鿴�Լ���ǰ��
//���ﻹȱ������ת�����Ȳ�ʵ�֣��ȵ������ܳ����ٴ�����
//SUBLEX:XOR %eax 0xffffffff
//		 INC EAX
//NOTLEX:CMP EAX 0
Tree exprOPSingle( Tree oprand, Tree op ){
	 if (!strcmp( op->name, "SUB" )|| !strcmp( op->name, "NOT" )) {
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
	else if (!strcmp( op->name, "SIZEOF" )) {
		 op->l = oprand;
		//���ʹ�С
	}
	/*else if (!strcmp( op->name, "" ) {

	}
	else if (!strcmp( op->name, "" ) {

	}*/
}
Tree exprOPDouble( Tree oprand1, Tree oprand2, Tree op ) {

	if (!strcmp( op->name, "MOD" )) {

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
				/*if (oprand1->opType != oprand2->opType) {
					//�����Ҫ����ת�� ����һ���½ڵ� ��������ת�� ���ӽڵ�ָ���ת��ֵ��Ŀ��ֵ��CVXX
				//���øò���
					Tree a = newNode( "TRA", op->l, NULL, CVC - 1 + op->l->opType, op->r->opType, op->l->type );
					op->l = a;
				}*/
				Symbol tempSym = lookup( stringd( temp ), identifiers );
				if (tempSym == NULL) {
					tempSym = install( stringd( temp ), &identifiers, level );
					temp++;
					maxTemp = (temp > maxTemp) ? temp : maxTemp;
					tempSym->offset = identificaionOffset+ temp;
					tempSym->temporary = 1;

				}
				else {
					//��ǰ��ʱ�������Ը���
					//����ûʲôҪ����
				}
				
				op->offset = tempSym->offset;
				return op;
			}
		}
		else
		{
			yyerror( "���в����������\n" );
			return NULL;
		}
	}
	else if (!strcmp( op->name, "ADD" ) || !strcmp( op->name, "SUB" ) || !strcmp( op->name, "STAR" ) || !strcmp( op->name, "DIV" )) {
		if (!strcmp( op->name, "ADD" ))op->opPr = ADD;
		else if (!strcmp( op->name, "STAR" )) {
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
		else if (!strcmp( op->name, "DIV" ))
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
			op->r = oprand1->opType < oprand2->opType ? oprand1 : oprand2;
			op->l = oprand1->opType < oprand2->opType ? oprand2 : oprand1;
			op->opType = op->r->opType;
			op->type = 0;//�����ܽ��и�ֵ����
			Symbol tempSym = lookup( stringd( temp ), identifiers );
			if (tempSym == NULL) {
				tempSym = install( stringd( temp ), &identifiers, level );
				
				tempSym->offset = identificaionOffset+ temp;
				temp++;
				tempSym->temporary = 1;

			}
			else {
				//��ǰ��ʱ�������Ը���
				//����ûʲôҪ����
			}
			
			maxTemp = (temp > maxTemp) ? temp : maxTemp;
			op->offset = tempSym->offset;
			
			return op;
			
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

			op->opPr = EQ;strcpy( op->name, "reeq" );
		}
		else {
			yyerror( "δ֪����\n" );
		}
		if (oprand1->type <= 1 && oprand2->type <= 1) {
			op->l = oprand1;
			op->r =  oprand2 ;
			op->opType = op->l->opType;
			op->type = 0;//�����ܽ��и�ֵ����
			if (oprand1->opType <= FLOAT && oprand1->opType <= FLOAT)
			{

				/*if (oprand1->opType != oprand2->opType) {
					//�����Ҫ����ת�� ����һ���½ڵ� ��������ת�� ���ӽڵ�ָ���ת��ֵ��Ŀ��ֵ��CVXX
				//���øò���
					op->l = newNode( "TRA", op->l, NULL, CVC - 1 + op->l->opType, op->r->opType, op->l->type );
					//op->l = a;
				}*/
			}
			Symbol tempSym = lookup( stringd( temp ), identifiers );
			if (tempSym == NULL) {
				tempSym = install( stringd( temp ), &identifiers, level );
				
				maxTemp = (temp > maxTemp) ? temp : maxTemp;
				tempSym->offset = identificaionOffset+temp;
				temp++;
				tempSym->temporary = 1;

			}
			else {
				//��ǰ��ʱ�������Ը���
				//����ûʲôҪ����
			}
			
			op->offset = tempSym->offset;
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
			op->r = oprand1->opType < oprand2->opType ? oprand1 : oprand2;
			op->l = oprand1->opType < oprand2->opType ? oprand2 : oprand1;

			op->opType = op->r->opType;//op���Ҳ������Ǹ��߼�������
			op->type = 0;//�����ܽ��и�ֵ����
			Symbol tempSym = lookup( stringd( temp ), identifiers );
			if (tempSym == NULL) {
				tempSym = install( stringd( temp ), &identifiers, level );
				temp++;
				maxTemp = (temp > maxTemp) ? temp : maxTemp;
				tempSym->offset = identificaionOffset+temp;
				tempSym->temporary = 1;

			}			
			op->offset = tempSym->offset;
			return op;
		}
		else
		{
			yyerror( "" );
			return NULL;
		}
	}
	else if (!strcmp( op->name, "ASSIGN" )) {
		if (!strcmp( oprand1->name, "NAME" )) {
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
			/*if (oprand1->opType != oprand2->opType) {
				//�����Ҫ����ת�� ����һ���½ڵ� ��������ת�� ���ӽڵ�ָ���ת��ֵ��Ŀ��ֵ��CVXX
			//���øò���
				Tree a = newNode( "TRA", op->r, NULL, CVC - 1 + op->r->opType, op->l->opType, op->l->type );
				//�����ڵ��Ҳ�����ת��Ϊ���ģ����ܶ�ʧ���ȣ��Ҳ�����
				op->r = a;
			}*/
				
			return op;
		}
		else
		{
			yyerror( "��ֵ���ɸ�ֵ������ֵ������\n" );
			return NULL;
		}
	}
	else if (!strcmp( op->name, "OR" ) || !strcmp( op->name, "AND" )) {
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
			if (!strcmp( op->name, "OR" )) {
				//��������cmp��jump,������Ϊ�٣�cmp op1 0;jne �¶������assLine+2;cmp op2 0 ��
				op->opPr = NE;
			}
			else {
				//��������cmp��һ��je,������Ϊ�棨cmp op1 0;je assLine+2��������䣨������һ�䣩;cmp op2 0 ��
				op->opPr = EQ;
			}
			Symbol tempSym = lookup( stringd( temp ), identifiers );
			if (tempSym == NULL) {
				tempSym = install( stringd( temp ), &identifiers, level );
				
				maxTemp = (temp > maxTemp) ? temp : maxTemp;
				tempSym->offset = identificaionOffset+temp;
				temp++;
				tempSym->temporary = 1;

			}

			op->offset = tempSym->offset;
			return op;
		}
		else {
			yyerror( "����δ����\n" );
		}
	}
}

Tree getVarName( Tree name ) {
	//�����һ������
	Symbol find1= lookup( name->idtype, constants );
	Symbol find2 = lookup( name->idtype, identifiers );
	if (find1 != NULL) {
		name->type = 0;
		name->opPr = NOP;
		name->opType = find1->type->op;
		name->offset = find1->offset;
		Tree na= newNode( "INDIRNAME", name, NULL, INDIR, name->opType, 0 );
		na->offset = name->offset;
		return na;
	}
	else if (find2!=NULL&&find2->scope==GLOBAL)
	{
		name->type = 0;
		name->opPr = NOP;
		name->opType = find2->type->op;
		name->offset = find2->offset;
		Tree na =newNode( "INDIRNAME", name, NULL, INDIR, name->opType, 0 );
		na->offset = name->offset;
		return na;
	}
	else if (find2 != NULL && find2->scope > GLOBAL)
	{
		name->type = 1;
		name->opPr = NOP;
		//name->opType = find2->type->op;
		name->offset = find2->offset;
		Tree indirexp= newNode( "INDIREXP", name, NULL, INDIR, name->opType, 1 );
		indirexp->offset = name->offset;
		return indirexp;
	}
	else {
		yyerror( "δ����ı���\n" );
	}
	//ȥ����ȡƫ��ֵ
	//ָ��
		//ȡ��ַ
		//�ӵ�ַȡ��
}

Tree getFuncName( Tree name, Tree arglist ) {
	//������ں��������ҵ���ǰ�ĺ���
	//�����½��CALL
	//CALL->l=�����ձ���
	//�ձ������ָ��ARG�б�
	Symbol func = lookup( name->idtype, functions);
	if (func->type->op == FUNCTION) {
		//��ǰ�����Ǻ�����
		//������ʱ���� 
		//identificaionOffset += 1;
		
		Tree arfReturn = NULL;
		if (name->opType != VOID) {
			arfReturn = newNode( "POPFUNC", NULL, NULL, POP, name->type, 3 );
			
		}
		//Tree nop= newNode( "funcuse", explist, arfReturn, CALL, name->ty, 2 );
		Tree addrl = newNode( "CALL", arglist, name, CALL,name->opType, 2 );
		addrl->intgr = func->type->u.f.args;
		//while()
		Tree nop = newNode( "funcuse", addrl, arfReturn, NOP, name->opType, 2 );
		Symbol tempSym = lookup( stringd( temp ), identifiers );
		if (tempSym == NULL) {
			tempSym = install( stringd( temp ), &identifiers, level );
			maxTemp = (temp > maxTemp) ? temp : maxTemp;
			tempSym->offset = identificaionOffset+temp;
			temp++;
			tempSym->temporary = 1;
		}
		nop->offset = tempSym->offset;
		if (name->opType != VOID) {
			arfReturn->offset = tempSym->offset;

		}
		return nop;
	}
	//return nop;
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
	
	Tree offset= newNode( "offset", NULL, NULL, NOP, INT, 0 );
	offset->intgr = index->intgr;
	//��ʱֻ���Ǳ���λ�ã�type��Ϣ������type��������
	Tree addrl = newNode( "ADDRG", name, offset, NOP, name->ty->type->op, 0 );
	//ע����������ʱ��name->ty->op�����ARRAY,name->ty->type->op�����Ԫ�ص�����
	return newNode( "ARRAY", name, offset, INDIR, name->ty->type->op, name->type );

}
/*���ɵĲ����ڵ��ұ��ǵ������ʽ������Ǳ��ʽ�б�,�����NULLʱ˵���Ѿ�û�в���
	�ڵ������ARG�������ֽڴ�Сpush
	Ҫ�㣺�������
*/

Tree setConstants( Tree cons ) {
	//û�д��constants������ͨ��constants�е������ڿ�ʼ���ǰ����DATA��
	if (!strcmp( cons->name, "INTNUM" )) {
		strcpy( cons->name, "CNST" );
		cons->opType = INT;
		cons->opPr = INDIR;
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
		//STRING
		strcpy( cons->name, "CNST" );
		cons->opType = ARRAY;
		cons->opPr = INDIR;
		cons->type = 0;
		//��ʱֻ���Ǳ���λ�ã�type��Ϣ������type��������
		return newNode( "INDIR", cons, NULL, INDIR, ARRAY, 0 );
		
	}
	
}
//ֱ��������ƥ���ʱ����õ�constant������ɻ���ʱ����constant
