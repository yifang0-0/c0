#include "c.h"
/*
树节点定义部分
	事实上这部分节点在遍历的时候只要做到
		初始化：TypeInitial
		创建新种类
			结构*暂时不考虑的
			指针*暂时不考虑的
			函数
			数组
		读取限定符
		unsigned 影响类型
		const 必须在创建时赋值
	
变量声明不建立存取树
变量定义先取地址，assgin,mov回源地址

	每一类的操作方式
		声明 Tree varDec(Tree type,Tree var,int ifConst)
		newNode("DEC",TYPE,VAR,0,TYPE->OP,IFCONST)
			①：if（ifConst）不断查找varlist的左节点是否为空，如果空则完成操作
				查找：lookup()不存在、存在但type相同且defined=0
				记录：当前域中的变量个数（建立节点时，以便为栈分配空间），变量名由变量表自动生成，在表中保存当前的偏移量n
				(实际偏移应是esp+n-size)
				n=n+type->size
				不生成任何语句！
			if(ifConst==0)但没有assgin ：错误，必须声明时定义
		
		定义	
			①：
				普通节点定义
				if（no const）找到一个节点，
				查找：lookup()不存在、存在但type相同且defined=0
				其左子树是assign，
				//由于匹配 能出现在此处的一定有类型符号
				检查assgin左右节点类型转换是否可能
					char* 对 constant string
					pointer 对 pointer
					其他《=float以下的转换与assgin相同
				失败 输出错误
				成功 正常建立了节点 在identificaiton表中新建节点
				n=n+type-size
				sym->defined=1
				由于assgin是特别设置（没有取数存数环节）
			if(const) 同上 在constants表中建立节点 不改变n
		②：
			函数定义
					Tree functionDef(Tree returnType,Tree name,Tree decList,Tree compost){ 
					type()//建立function的类 可以检查否重定义
					Tree return=newNode("PUSH",returnType,null,PUSH,return->op,0)//函数值不能作为左值
				
				左子树递归使用varDec()，然后pop
					popArgs= newNode( "ARGPOP", VAR, VARLIST, POP, VAR->type, 1 );//打印pop eax ;mov eax n 更新n=n+typesize
				newNode("NOP",popArgs，compost,0,0,0)
					newNode("PROC",NOP，returnType) //打印当前函数名 NAME UESE EAX EBX ECX EDX
		③：Tree arrayDef(Tree type,Tree var,int ifConst,Tree exp){
		//在Tree varDec发现var-l-name!=name 而是==var,跳进来
					Type()
					install()
					var-l=var
					var-r=exp
				//和普通变量的区别 此时要建立新的Type array,其他步骤都一样，唯一的就是sym->offset=n,n+=name->sym->ty->Type->size*n
					var-l=var
					var-r=null
					sym->offset=n,n+=4(不定长度的指针)
					return VAR
		}
	
		}
				
				
				返回值在右侧
*/

/*
这是不需要在程序之前生成的函数内定义
*/

void setNewSymbol( Symbol newsym, Type type ) {
	newsym->defined = 1;
	newsym->offset = identificaionOffset;
	newsym->type = type;
	newsym->size = type->size;
}
void okayToDec(Tree newsymbol,Type type,Tree valueNode,int ifconst ) {
	Symbol newsym ;
	if (ifconst) {
		newsym = install( newsymbol->idtype, &constants, CONSTANT );
		identificaionOffset -= 1;
		strcpy( newsymbol->name, "INDIRNAME" );
	}
	else {
		newsym = install( newsymbol->idtype, &identifiers, level );
		strcpy( newsymbol->name, "INDIREXP" );
		
	}
	newsymbol->opType = type->op;
	newsym-> type= type;
	newsym->ifconst = ifconst;
	setNewSymbol( newsym, type );
	newsymbol->offset = newsym->offset;
	if(valueNode !=NULL){	
		newsym->u.c.v = newValue( type->op, valueNode->u, valueNode->opType );
		newsym->defined = 1;
	}
	else newsym->defined = 0;
	newsymbol->r->opPr = NOP;
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
		default:yyerror( "输入错误得到类型\n" );
		}
	}
	else if (oldType == INT) {
		switch (type) {
		case CHAR:newValue.sc = (char)(oldValue.i);break;
		case UNSIGNEDCHAR:newValue.uc = (unsigned char)(oldValue.i);break;
		case INT:newValue.i = (int)(oldValue.i);break;
		case UNSIGNED:newValue.u = (unsigned)(oldValue.i);break;
		case FLOAT:newValue.f = (float)(oldValue.i);break;
		default:yyerror( "输入错误得到类型\n" );
		}
	}
	return newValue;
}
//判断是否可以进行转换
int transferAssignDecl(Tree type,Tree Var ) {
	if (type->ty->op <= FLOAT && Var->opType <= FLOAT) {
			return 1;
		}
//类型转换
	return 0;
}




Tree varDec( Tree type, Tree vl, int ifConst ) {
	Tree varList = vl;
	
	if (ifConst==1) {//可能出现两种情况：常量或非常量
		//varList可能出现的两种情况：varlist，var
		while (!strcmp( varList->name, "varList" )) {

			if (!strcmp( varList->l->name, "Var" )) {
				//如果存在一个没有赋值的变量，报错
				yyerror( "未在常量定义时赋值\n" );
			}
			else if (!strcmp( varList->l->name, "ASSIGN" ))
			{
				if (!strcmp( varList->l->l->name, "NAME" )) {
					//判断是否能够复制
					char* newsymbol = varList->l->l->idtype;
					if (//是否已经在表中存在
						(lookup( newsymbol, constants
						 ) == NULL /*|| lookup( newsymbol, constant
						 )->defined == 0//常量不存在未定义问题
						 */)
						 &&
						 (lookup( newsymbol, identifiers
						 ) == NULL)
						 )
					{
						/*
						if (!transferAssignDecl( type, varList )) {
							yyerror( "失败的类型转换，左右两边操作数不可赋值\n" );
						}*/
						//所有条件都符合,可以开始定义
						okayToDec( varList->l->l, type->ty, varList->l->r ,ifConst);
						varList->type = 0;
						//在这里需要插入一个生成读ebp的东西
						//此时可以抛弃name
					}
					else {
						yyerror( "变量重复定义！" );
					}

					//如果可以，就先添加symbol
						//指令为：mov esp+n immidient
				}
				else
				{
					yyerror( "暂时不支持数组赋值\n" );
				}
				varList->l->opType = varList->l->l->opType;
			}
			
			varList = varList->r;
			if (varList == NULL)break;
		}
	}
	else {//此时既可以有等于也可以没有，没有时还要考虑数组（仅实现一维数组）
		Tree newDecl;
			while (!strcmp( varList->name, "varList" )) {
				char* newsymbol = varList->l->name;
				//判断是否已经在表中存在
				if (!strcmp( newsymbol, "Var" )) {
					//未定义
					newDecl = varList->l->l;
					if (!strcmp( newDecl->name, "NAME" )) {
						newsymbol = newDecl->idtype;//idtype
						if (
							//这里的查找与NULL相关，不太对
							((lookup( newsymbol, constants ) != NULL)
							||
							(lookup( newsymbol, identifiers ) != NULL) 
							&& lookup( newsymbol, identifiers )->scope == level 
							&& lookup( newsymbol, identifiers )->defined != 0
							)
							) {
							yyerror( "声明类型冲突或定义后重复声明\n" );
						}
						else {
							//开始声明
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
							yyerror( "声明类型冲突或定义后重复声明\n" );
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
									yyerror( "不可用的指数类型\n" );
								}
							}
							okayToDec( varList->l->l, ty, NULL, ifConst );
						}
					}
					
					
				}
				
				else if (!strcmp( varList->l->name, "ASSIGN" ))
				{
					if (!strcmp( varList->l->l->name, "NAME" )) {
						//判断是否能够复制
						newsymbol = varList->l->l->idtype;
						if (
							((lookup( newsymbol, constants ) != NULL)
							||
							(lookup( newsymbol, identifiers ) != NULL) && lookup( newsymbol, identifiers )->scope==level && lookup( newsymbol, identifiers )->defined != 0
							)
							) {
							yyerror( "声明类型冲突或定义后重复声明\n" );
						}
						else
							okayToDec( varList->l->l, type->ty, varList->l->r, ifConst );
						
					}
					else yyerror( "暂时不支持数组赋值\n" );
					varList->l->opType = varList->l->l->opType;
				}
				
				//Tree examErrorNoAssign = varList;
				varList = varList->r;
				if (!varList)break;
			}
	}
	return newNode( "DEC", type, vl,NOP, type->ty->op, ifConst );
}

Symbol findIfExist( Tree type,Tree var ,int ifconst) {
	if(!strcmp(var->name,"NAME")){
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
			yyerror( "声明重复\n" );
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
			yyerror( "声明重复\n" );
		}
	}
	
	else {
		yyerror( "声明重复\n" );
	}
	
}
Tree funcHeadDef( Tree type, Tree name, Tree args, int ifconst ) {

	Tree aftReturn = NULL;

	//检查是否存在
	if (lookup( name->idtype, functions ) && (lookup( name->idtype, functions )->defined == 1)) {
		yyerror( "函数定义已存在\n" );
	}
	//如果函数未被定义且此时为函数定义

	Type *proto;
	int size = 0;
	Tree fundec = args;
	int i = 0;//计算参数的个数
		while (fundec != NULL&&(!strcmp( fundec->name, "funcDecList" ) || !strcmp( fundec->name, "funcDec" ))) {
			i += 1;
			fundec = fundec->r;
		}
	
	fundec = args;
	proto = (Type*)malloc( i * sizeof( Type ) );
	proto[i] = NULL;//函数末尾为0
	
	for (int n = 0;n < i;n++) {
		Symbol cur = findIfExist( fundec->l->l, fundec->l->r, fundec->l->l->type );
		proto[n] = cur->type;
		proto[n]->u.sym = cur;
		if (cur->ifconst)
			proto[n]->u.sym->ifconst= 1;
	}
	level -= 1;
	//此处可以省略size,因为offsize在install中更新
	Type newFunc = func( type->ty, proto );
	//newFunc->u.f.funcSize = identificaionOffset+maxTemp;
	newFunc->u.f.args = i;
	install( name->idtype, &functions, GLOBAL );
	lookup( name->idtype, functions )->type = newFunc;
	level += 1;
	if (type->ty->op != VOID) {
		aftReturn = newNode( "ret", NULL, NULL, PUSH, name->type, 3 );
	}
	Tree nop = newNode( "nop", args, NULL, NOP, name->opType, 2 );
	Tree addrl = newNode( "function", nop, aftReturn, NOP, name->opType, 2 );
	addrl->idtype = name->idtype;
	return addrl;
}
Tree funcDef(Tree funcdec,Tree explist ) {
		/*
		制造四元式！*/
	char* name = funcdec->idtype;
	Type newFunc = lookup( name, functions )->type;
	funcdec->l->r = explist;
	newFunc->u.f.funcSize = identificaionOffset + maxTemp;
		if(explist!=NULL){
			if (!strcmp(name,"main"))
			{
					
					struct mid* main= midMainUpdate( newFunc );
					//struct mid* main2 = main;
					curMid = main;
				expGen( explist, 0, main );
			}
			else {
				struct mid* otherFunc=midCurUpdate( name, newFunc );
				curMid = otherFunc;
				expGen( explist, 0,otherFunc );
			}
			
			printf( "生成%s的四元式\n", name );
		}
			
			return funcdec;

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
		yyerror( "不可设置为unsigned的类型\n" );
	}
	return oldType;
}
//函数声明暂时不实现了，必须要阉割点功能了

