#include "c.h"
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
void okayToDec(Tree newsymbol,Type type,Tree value,int ifconst ) {
	Symbol newsym ;
	if (ifconst) {
		newsym = install( newsymbol->idtype, &constants, CONSTANT );identificaionOffset -= 1;
	}
	else newsym = install( newsymbol->idtype, &identifiers, level);
	newsymbol->opType = type->op;
	newsymbol->opPr=INDIR;
	newsym-> type= type;
	newsym->ifconst = ifconst;
	setNewSymbol( newsym, type );
	if(value!=0){
		newsym->u.c.v = newValue( type->op, value->u, value->opType );
		newsym->defined = 1;
	}
	else newsym->defined = 0;
	identificaionOffset +=1;
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
	return newValue;
}
//�ж��Ƿ���Խ���ת��
int transferAssignDecl(Tree type,Tree Var ) {
	if (type->ty->op <= FLOAT && Var->opType <= FLOAT) {
			return 1;
		}
//����ת��
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
				if (!strcmp( varList->l->l->name, "NAME" )) {
					//�ж��Ƿ��ܹ�����
					char* newsymbol = varList->l->l->idtype;
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
						/*
						if (!transferAssignDecl( type, varList )) {
							yyerror( "ʧ�ܵ�����ת�����������߲��������ɸ�ֵ\n" );
						}*/
						//��������������,���Կ�ʼ����
						okayToDec( varList->l->l, type->ty, varList->l->r ,ifConst);
						varList->type = 0;
						//��������Ҫ����һ�����ɶ�ebp�Ķ���
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
						newsymbol = newDecl->idtype;//idtype
						if (
							//����Ĳ�����NULL��أ���̫��
							((lookup( newsymbol, constants ) != NULL)
							||
							(lookup( newsymbol, identifiers ) != NULL) && lookup( newsymbol, identifiers )->defined != 0
							)
							) {
							yyerror( "�������ͳ�ͻ������ظ�����\n" );
						}
						else {
							//��ʼ����
							okayToDec( newDecl, type->ty, NULL, ifConst );
						}
					}
					else if (!strcmp( newDecl->name, "Array" )) {
						//newDecl = newDecl->l;
						newsymbol = newDecl->l->idtype;
						Symbol find1 = (lookup( newsymbol, constants ));
						Symbol find2 = (lookup( newsymbol, identifiers ));
						if (
						find1||(find2&&find2->defined==1)
								)
							 {
							yyerror( "�������ͳ�ͻ������ظ�����\n" );
						}
						else {
							Type ty;
							if (newDecl->r == NULL) {
								ty = PRT( type->ty );
							}
							else {
								if (!strcmp( newDecl->r->name, "CNST" )&&newDecl->r->opType==INT) {
									ty=arrayType( type->ty, newDecl->r->u.i );

								}
								else {
									yyerror( "�����õ�ָ������\n" );
								}
							}
							okayToDec( varList->l->l, ty, NULL, ifConst );
						}
					}
					
					
				}
				
				else if (!strcmp( varList->l->name, "ASSIGN" ))
				{
					if (!strcmp( varList->l->l->name, "NAME" )) {
						//�ж��Ƿ��ܹ�����
						newsymbol = varList->l->l->idtype;
						if (
							((lookup( newsymbol, constants ) != NULL)
							||
							(lookup( newsymbol, identifiers ) != NULL) && lookup( newsymbol, identifiers )->defined != 0
							)
							) {
							yyerror( "�������ͳ�ͻ������ظ�����\n" );
						}
						else
							okayToDec( varList->l->l, type->ty, varList->l->l->r, ifConst );
						
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

Symbol findIfExist( Tree var,Tree type ,int ifconst) {
	if(!strcmp(var->name,"Var")){
		Symbol p = lookup( var->idtype, identifiers );
		if (!p || (p&&p->scope < level)) {
			p = install( var->idtype, &identifiers, level );
			p->type = type->ty;
			p->ifconst = ifconst;
				identificaionOffset += 1;
				p->offset = identificaionOffset - 1;
			p->defined = 0;
			return p;
		}
		else {
			yyerror( "�����ظ�\n" );
		}
	}
	else if( !strcmp( var->name, "Array" ) ) {
		Symbol p = lookup( var->l->idtype, identifiers );
		if (!p || (p&&p->scope < level)) {
			p = install( var->l->idtype, &identifiers, level );
			p->type = arrayType(type->ty, var->r-> u.i );
			identificaionOffset += type->ty->size / type->ty->type->size;
			p->offset = identificaionOffset - type->ty->size / type->ty->type->size;
			p->defined = 0;
			p->ifconst = ifconst;
			return p;
		}
		else {
			yyerror( "�����ظ�\n" );
		}
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
	if (lookup( name->idtype, identifiers ) && (lookup( name->idtype, identifiers )->defined == 1)) {
		yyerror( "���������Ѵ���\n" );
	}
	//�������δ�������Ҵ�ʱΪ��������
	
		Type *proto;
		int size = 0;
		Tree fundec = args;
		int i = 0;//��������ĸ���
		if (fundec != NULL) {
			while (!strcmp( fundec->name, "funcDecList" ) || !strcmp( fundec->name, "funcDec" )) {
				i += 1;
				fundec = fundec->r;
			}
		}
		fundec = args;
		proto = (Type*)malloc( i * sizeof( Type ) );
		proto[i] = NULL;//����ĩβΪ0
		for (int n = 0;n < i;n++) {
			Symbol cur = findIfExist( fundec->l->l->l, fundec->l->l->r, fundec->l->l->type );
			proto[n] = cur->type;
			proto[n]->u.sym = cur;
			if (cur->ifconst)
				proto[n]->op = CONST;
		}
			//�˴�����ʡ��size,��Ϊoffsize��install�и���
			Type newFunc = func( type->ty, proto );
			newFunc->u.f.funcSize = identificaionOffset;
			newFunc->u.f.args = i;
			install( name->idtype, &identifiers, GLOBAL );
			lookup( name->idtype, identifiers )->type = newFunc;
			if (type->ty->op != VOID) {
				aftReturn = newNode( "PUSH", NULL, NULL, PUSH, name->type, 3 );
			}
			Tree nop = newNode( "nop", args, explist, NOP, name->opType, 2 );
			Tree addrl=newNode( "function", nop, aftReturn, NOP, name->opType, 2 );
			/*
			������Ԫʽ��*/
			if(explist!=NULL){
				if (!strcmp(name->idtype,"main"))
				{
					expGen( explist, 0, midMainUpdate(  newFunc ) );
				}
				else
					expGen(explist,0 ,  midCurUpdate( name->idtype,newFunc ));
				printf( "����%s����Ԫʽ\n", name->idtype );
			}
			
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

