#include "dataStructure.h"
/*
���ڵ㶨�岿��
	��ʵ���ⲿ�ֽڵ��ڱ�����ʱ��ֻҪ����
		��ʼ����TypeInitial
		����������
			�ṹ*��ʱ�����ǵ�
			ָ��*��ʱ�����ǵ�
			����
			����
		��ȡ�޶���
		unsigned Ӱ������
		const �����ڴ���ʱ��ֵ
	
����������������ȡ��
����������ȡ��ַ��assgin,mov��Դ��ַ

	ÿһ��Ĳ�����ʽ
		���� Tree varDec(Tree type,Tree var,int ifConst)
		newNode("DEC",TYPE,VAR,0,TYPE->OP,IFCONST)
			�٣�if��ifConst�����ϲ���varlist����ڵ��Ƿ�Ϊ�գ����������ɲ���
				���ң�lookup()�����ڡ����ڵ�type��ͬ��defined=0
				��¼����ǰ���еı��������������ڵ�ʱ���Ա�Ϊջ����ռ䣩���������ɱ������Զ����ɣ��ڱ��б��浱ǰ��ƫ����n
				(ʵ��ƫ��Ӧ��esp+n-size)
				n=n+type->size
				�������κ���䣡
			if(ifConst==0)��û��assgin �����󣬱�������ʱ����
		
		����	
			�٣�
				��ͨ�ڵ㶨��
				if��no const���ҵ�һ���ڵ㣬
				���ң�lookup()�����ڡ����ڵ�type��ͬ��defined=0
				����������assign��
				//����ƥ�� �ܳ����ڴ˴���һ�������ͷ���
				���assgin���ҽڵ�����ת���Ƿ����
					char* �� constant string
					pointer �� pointer
					������=float���µ�ת����assgin��ͬ
				ʧ�� �������
				�ɹ� ���������˽ڵ� ��identificaiton�����½��ڵ�
				n=n+type-size
				sym->defined=1
				����assgin���ر����ã�û��ȡ���������ڣ�
			if(const) ͬ�� ��constants���н����ڵ� ���ı�n
		�ڣ�
			��������
					Tree functionDef(Tree returnType,Tree name,Tree decList,Tree compost){ 
					type()//����function���� ���Լ����ض���
					Tree return=newNode("PUSH",returnType,null,PUSH,return->op,0)//����ֵ������Ϊ��ֵ
				
				�������ݹ�ʹ��varDec()��Ȼ��pop
					popArgs= newNode( "ARGPOP", VAR, VARLIST, POP, VAR->type, 1 );//��ӡpop eax ;mov eax n ����n=n+typesize
				newNode("NOP",popArgs��compost,0,0,0)
					newNode("PROC",NOP��returnType) //��ӡ��ǰ������ NAME UESE EAX EBX ECX EDX
		�ۣ�Tree arrayDef(Tree type,Tree var,int ifConst,Tree exp){
		//��Tree varDec����var-l-name!=name ����==var,������
					Type()
					install()
					var-l=var
					var-r=exp
				//����ͨ���������� ��ʱҪ�����µ�Type array,�������趼һ����Ψһ�ľ���sym->offset=n,n+=name->sym->ty->Type->size*n
					var-l=var
					var-r=null
					sym->offset=n,n+=4(�������ȵ�ָ��)
					return VAR
		}
	
		}
				
				
				����ֵ���Ҳ�
*/

/*
���ǲ���Ҫ�ڳ���֮ǰ���ɵĺ����ڶ���
*/
void setNewSymbol( Symbol newsym, Type type ) {
	newsym->defined = 1;
	newsym->offset = identificaionOffset;
	newsym->type = type;
	newsym->size = type->size;
}
void okayToDec(Tree newsymbol,Tree type,Tree value,int ifconst ) {
	Symbol newsym = install( newsymbol->name, constants, level, 1 );
	newsym->defined = ifconst;
	setNewSymbol( newsym, type->ty );
	if(value!=0){
		newsym->u.c.v = newValue( type->ty->op, value->u, value->opType );
		newsym->defined = 1;
	}
	else newsym->defined = 0;
	identificaionOffset += newsym->size;

}
Value newValue( int type, Value oldValue,int oldType )
{
	Value newValue;
	if (oldType == FLOAT) {
		switch (type) {
		case CHAR:newValue.sc = (char)(oldValue.f);break;
		case UNSIGNEDCHAR:newValue.uc = (char)(oldValue.f);break;
		case INT:newValue.i = (char)(oldValue.f);break;
		case UNSIGNED:newValue.u = (char)(oldValue.f);break;
		case FLOAT:newValue.f = (char)(oldValue.f);break;
		default:yyerror( "�������õ�����\n" );
		}
	}
	else if (oldType == INT) {
		switch (type) {
		case CHAR:newValue.sc = (char)(oldValue.i);break;
		case UNSIGNEDCHAR:newValue.uc = (unsigned char)(oldValue.i);break;
		case INT:newValue.i = (int)(oldValue.i);break;
		case UNSIGNED:newValue.u = (unsigned)(oldValue.i);break;
		case FLOAT:newValue.f = (float)(oldValue.i);break;
		default:yyerror( "�������õ�����\n" );
		}
	}
}

int transferAssignDecl(Tree type,Tree varList ) {
	if (type->ty->op <= FLOAT && varList->r->opType <= FLOAT) {
		if (type->ty->op != varList->r->opType) {
			//ת��
			Tree a = newNode( "TRA", varList->l->r, NULL, CVC - 1 + varList->l->r->opType, varList->l->l->opType, varList->l->l->type );
			//�����ڵ��Ҳ�����ת��Ϊ���ģ����ܶ�ʧ����
			varList->l->r = a;
			return 1;
		}

	}
	return 0;
}


Tree varDec( Tree type, Tree vl, int ifConst ) {
	Tree varList = vl;
	
	if (ifConst) {//���ܳ������������������ǳ���
		//varList���ܳ��ֵ����������varlist��var
		while (!strcmp( varList->name, "varList" )) {

			if (!strcmp( varList->l->name, "Var" )) {
				//�������һ��û�и�ֵ�ı���������
				yyerror( "δ�ڳ�������ʱ��ֵ\n" );
			}
			else if (!strcmp( varList->l->name, "ASSIGN" ))
			{
				if (!strcmp( varList->l->name, "NAME" )) {
					//�ж��Ƿ��ܹ�����
					char* newsymbol = varList->l->name;
					if (//�Ƿ��Ѿ��ڱ��д���
						(lookup( newsymbol, constants
						 ) == NULL /*|| lookup( newsymbol, constant
						 )->defined == 0//����������δ��������
						 */)
						 &&
						 (lookup( newsymbol, identifiers
						 ) == NULL)
						 )
					{
						if (!transferAssignDecl( type, varList )) {
							yyerror( "ʧ�ܵ�����ת�����������߲��������ɸ�ֵ\n" );
						}
						//��������������,���Կ�ʼ����
						okayToDec( varList->l->l, type, varList->l->r ,ifConst);
						varList->type = 0;

					}
					else {
						yyerror( "�����ظ����壡" );
					}

					//������ԣ��������symbol
						//ָ��Ϊ��mov esp+n immidient
				}
				else
				{
					yyerror( "��ʱ��֧�����鸳ֵ\n" );
				}
			}
			varList = varList->r;
			if (varList == NULL)break;
		}
	}
	else {//��ʱ�ȿ����е���Ҳ����û�У�û��ʱ��Ҫ�������飨��ʵ��һά���飩
		Tree newDecl;
			while (!strcmp( varList->name, "varList" )) {
				char* newsymbol = varList->l->name;
				//�ж��Ƿ��Ѿ��ڱ��д���
				if (!strcmp( newsymbol, "Var" )) {
					//δ����
					newDecl = varList->l->l;
					if (!strcmp( newDecl->name, "NAME" )) {
						newsymbol = newDecl->name;
						if (
							!((lookup( newsymbol, constants
							) == NULL || lookup( newsymbol, constants
							)->defined == 0)
							&&
							(lookup( newsymbol, identifiers
							) == NULL) || lookup( newsymbol, identifiers
							)->defined == 0
							)) {
							yyerrer( "�������ͳ�ͻ������ظ�����\n" );
						}
						else {
							//��ʼ����
							okayToDec( newDecl, type, NULL, ifConst );
						}
					}
					else if (!strcmp( newDecl->name, "Array" )) {
						//newDecl = newDecl->l;
						newsymbol = newDecl->l->name;
						if (
							!((lookup( newsymbol, constants
							) == NULL || lookup( newsymbol, constants
							)->defined == 0)
							&&
							(lookup( newsymbol, identifiers
							) == NULL) || lookup( newsymbol, identifiers
							)->defined == 0
							)) {
							yyerrer( "�������ͳ�ͻ������ظ�����\n" );
						}
						else {
							Type ty;
							if (newDecl->r == NULL) {
								ty = PRT( type );
							}
							else {
								if (!strcmp( newDecl->r->name, "CNST" )&&newDecl->r->opType==INT) {
									ty=arrayType( type, newDecl->r->u.i );

								}
								else {
									yyerror( "�����õ�ָ������\n" );
								}
							}
							okayToDec( varList->l->l, type, NULL, ifConst );
						}
					}
					
					
				}
				
				else if (!strcmp( varList->l->name, "ASSIGN" ))
				{
					if (!strcmp( varList->l->l->name, "NAME" )) {
						//�ж��Ƿ��ܹ�����
						newsymbol = varList->l->l->l->name;
						if (
							!((lookup( newsymbol, constants
							) == NULL || lookup( newsymbol, constants
							)->defined == 0)
							&&
							(lookup( newsymbol, identifiers
							) == NULL) || lookup( newsymbol, identifiers
							)->defined == 0
							)) {
							yyerrer( "�������ͳ�ͻ������ظ�����\n" );
						}
						else
							okayToDec( varList->l->l->l, type, varList->l->l->r, ifConst );
						if (!transferAssignDecl( type, varList )) {
							yyerror( "ʧ�ܵ�����ת�����������߲��������ɸ�ֵ\n" );
							}
					}
					else yyerror( "��ʱ��֧�����鸳ֵ\n" );
				}
				
				//Tree examErrorNoAssign = varList;
				varList = varList->r;
				if (!varList)break;
			}
	}
	return newNode( "DEC", type, vl,NOP, type->ty->op, ifConst );
}

void findIfExist( Tree var,Tree type ) {
	Symbol p = lookup( var->name, &identifiers );
	if (!p || (p&&p->scope < level)) {
		p=install( var->name, identifiers );
		p->type = type;
		//return 1;
	}
	else {
		yyerror( "�����ظ�\n" );
	}
	
}

Tree funcDef(Tree type,Tree name,Tree args,int ifconst,Tree explist ) {
	//��������ͼ
	//���뺯��level+1
	
	Tree aftReturn = NULL;

	//����Ƿ����
	if (lookup( name->idtype, identifiers )&& lookup( name->idtype, identifiers )->type->op==FUNCTION && lookup( name->idtype, identifiers )->defined == 1) {
		yyerror( "���������Ѵ���\n" );
	}
	Type *proto;
	int i = 0;
	Tree fundec = args;
	while (fundec != NULL) {
		i += 1;
		fundec = fundec->r;
	}
	proto = (Type*)malloc( i * sizeof( Type ) );
	proto[i] = NULL;
	fundec = args;
	level += 1;
	for (int n = 0;n < i;n++) {
		findIfExist( fundec->l->l->r, fundec->l->l->l );
		proto[n] = fundec->l->l->l->ty;
		if (fundec->l->l->l->type == 0)
			proto[n]->op = CONST;
	}
	level -= 1;
	
	Tree aftReturn=NULL;
	if (type->ty->op != VOID) {
		aftReturn = newNode( "PUSH", NULL, NULL, PUSH, name->type, 3 );
	}
	Tree nop = newNode( "nop", explist, aftReturn, CALL, name->ty, 2 );
	Tree addrl = newNode( "function", nop, aftReturn, NOP, name->ty, 2 );
	addrl->ty=func( type->type, proto );
	level += 1;
	return addrl;
}



Tree changeToUnsigned( Tree oldType ) {
	if (oldType->ty->op == INT) {
		oldType->ty = unsignedinttype;
		oldType->opType = UNSIGNED;
	}
	else if (oldType->ty->op == CHAR) {
		oldType->ty = unsignedchartype;
		oldType->opType = UNSIGNEDCHAR;
	}
	else{
		yyerror( "��������Ϊunsigned������\n" );
	}
	return oldType;
}
//����������ʱ��ʵ���ˣ�����Ҫ�˸�㹦����

