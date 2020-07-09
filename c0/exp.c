/*
//表达式文件需要处理的是已知的symbol的处理
1.类型检查、转化
2.检查、更新符号表（转换后）
3.NAME是否存在与符号表中（当前scope）
4.更新运算符的运算类型：ADD->ADDI,g更新op值
处理函数
expr1(单变量，如自增自减，sizeof，强制类型转换)
expr2(双变量，+=*%/ 逻辑比较符)
expr3(:? 条件选择符，还没想好怎么处理···)

在未定义的时候 int\double都作为临时变量生成
*/
#include "c.h"
/*无论是什么操作！！！！！所有的exp结束后，都必须把结果存到eax里，如果作为右操作数，存到ebx里*/

//单操作符
//只处理规定的简单操作符
//操作符连接的exp（必是当前即可操作的，意味者所有操作数要查看自己当前）
//这里还缺少类型转换，先不实现，等到大体框架出来再错误检查
//SUBLEX:XOR %eax 0xffffffff
//		 INC EAX
//NOTLEX:CMP EAX 0
Tree exprOPSingle( Tree oprand, Tree op ){
	 if (!strcmp( op->name, "SUB" )|| !strcmp( op->name, "NOT" )) {
		//取负数
		if (oprand->opType <= FLOAT) {
			//无论是常量还是变量都可以参与运算
			op->l=oprand;
			op->opType = oprand->opType;
			return op;
		}
		else
		{
			yyerror("变量类型错误，不可对当前数据进行操作" );
			return NULL;
		}
	}
	else if (!strcmp( op->name, "SIZEOF" )) {
		 op->l = oprand;
		//类型大小
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
				yyerror( "模零错误\n" );
			}
			else {
				op->r = oprand1->opType < oprand2->opType ? oprand1 : oprand2;
				op->l = oprand1->opType < oprand2->opType ? oprand2 : oprand1;
				op->opPr = MOD;
				op->opType = op->r->opType;
				op->type = 0;//即不能进行赋值操作
				/*if (oprand1->opType != oprand2->opType) {
					//如果需要类型转换 建立一个新节点 用来类型转换 孩子节点指向待转换值与目标值，CVXX
				//设置该操作
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
					//当前临时变量可以复用
					//好像没什么要做的
				}
				
				op->offset = tempSym->offset;
				return op;
			}
		}
		else
		{
			yyerror( "含有不能运算的类\n" );
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
				//指针加减
				//mov $1,addr
				//lsh $1 ,2
				//mov $2 ,addrp
				//add $2,$1
				return op;
			}
			else {
				yyerror( "指针操作错误" );
				return NULL;
			}
		}
		else if (!strcmp( op->name, "DIV" ))
		{
			if ((oprand2->type == 0 && (oprand2->u.ifdiv == 1) || oprand2->type == 1 && (oprand2->sym->ifdiv == 1)))
			{
				yyerror( "模零错误\n" );
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
			op->type = 0;//即不能进行赋值操作
			Symbol tempSym = lookup( stringd( temp ), identifiers );
			if (tempSym == NULL) {
				tempSym = install( stringd( temp ), &identifiers, level );
				
				tempSym->offset = identificaionOffset+ temp;
				temp++;
				tempSym->temporary = 1;

			}
			else {
				//当前临时变量可以复用
				//好像没什么要做的
			}
			
			maxTemp = (temp > maxTemp) ? temp : maxTemp;
			op->offset = tempSym->offset;
			
			return op;
			
		}
	}
	else if (!strcmp( op->name, "RELOP" )) {
		//逻辑比较 

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
			yyerror( "未知错误\n" );
		}
		if (oprand1->type <= 1 && oprand2->type <= 1) {
			op->l = oprand1;
			op->r =  oprand2 ;
			op->opType = op->l->opType;
			op->type = 0;//即不能进行赋值操作
			if (oprand1->opType <= FLOAT && oprand1->opType <= FLOAT)
			{

				/*if (oprand1->opType != oprand2->opType) {
					//如果需要类型转换 建立一个新节点 用来类型转换 孩子节点指向待转换值与目标值，CVXX
				//设置该操作
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
				//当前临时变量可以复用
				//好像没什么要做的
			}
			
			op->offset = tempSym->offset;
			return op;
		}
		else {
			yyerror( "节点不可操作\n" );
		}
	}
	else if (!strcmp( op->name, "BXOR" ) || !strcmp( op->name, "BOR" ) || !strcmp( op->name, "BAND" )) {
		if (oprand1->type <= 1 && oprand2->type <= 1) {
			if (!strcmp( op->name, "BXOR" ))op->opPr = BXOR;
			else if (!strcmp( op->name, "BOR" ))op->opPr = BOR;
			else if (!strcmp( op->name, "BAND" ))op->opPr = BAND;
			op->r = oprand1->opType < oprand2->opType ? oprand1 : oprand2;
			op->l = oprand1->opType < oprand2->opType ? oprand2 : oprand1;

			op->opType = op->r->opType;//op的右操作数是更高级的类型
			op->type = 0;//即不能进行赋值操作
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
			//此时处理声明的情况
			op->r = oprand2;
			op->l = oprand1;
			op->opPr = ASGN;
			op->opType = op->l->opType;//左侧的类型是复制最终类型
			op->type = 0;//即不能进行赋值操作
			return op;
		}
		else if (oprand1->type == 1 && oprand2->type <= 1) {
			op->r = oprand2;
			op->l = oprand1;
			//如果左侧是一个INDIR，删除该节点，指向其左节点
			op->opPr = ASGN;
			op->opType = op->l->opType;//左侧的类型是复制最终类型
			op->type = 0;//即不能进行赋值操作
			/*if (oprand1->opType != oprand2->opType) {
				//如果需要类型转换 建立一个新节点 用来类型转换 孩子节点指向待转换值与目标值，CVXX
			//设置该操作
				Tree a = newNode( "TRA", op->r, NULL, CVC - 1 + op->r->opType, op->l->opType, op->l->type );
				//将等于的右侧类型转换为左侧的，可能丢失精度，我不管了
				op->r = a;
			}*/
				
			return op;
		}
		else
		{
			yyerror( "左值不可赋值或者右值不合理\n" );
			return NULL;
		}
	}
	else if (!strcmp( op->name, "OR" ) || !strcmp( op->name, "AND" )) {
		//我得头快要从脖子上掉下来了
		// ：（
		//真假值之间的比较
		//除非是0
		//否则都是真
		//cmp
		//jne/je assLine+2
		//cmp
		//assLine+2:提前打好
		if (oprand1->type <= 1 && oprand2->type <= 1) {
			op->l = oprand1;
			op->r = oprand2;
			op->type = 0;
			op->opType = CONST;
			if (!strcmp( op->name, "OR" )) {
				//建立两个cmp与jump,如果左边为假（cmp op1 0;jne 下二条语句assLine+2;cmp op2 0 ）
				op->opPr = NE;
			}
			else {
				//建立两个cmp与一个je,如果左边为真（cmp op1 0;je assLine+2下两条语句（跳过下一句）;cmp op2 0 ）
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
			yyerror( "变量未定义\n" );
		}
	}
}

Tree getVarName( Tree name ) {
	//如果是一个变量
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
		yyerror( "未定义的变量\n" );
	}
	//去表中取偏移值
	//指令
		//取地址
		//从地址取数
}

Tree getFuncName( Tree name, Tree arglist ) {
	//如果能在函数表中找到当前的函数
	//建立新结点CALL
	//CALL->l=建立空变量
	//空变量左侧指向ARG列表
	Symbol func = lookup( name->idtype, functions);
	if (func->type->op == FUNCTION) {
		//当前变量是函数名
		//创建临时变量 
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
	//CALL的时候就无脑压全部的栈再jump到标号

	//碰到ARG就无脑压栈n次

	//CALL->l->r是参数偏移量，每个变量加一，设定numofvar

	//不要搞这个了 直接pop出来
	//mov到一个内存值

	//POP全部寄存器出来后恢复正常


}
Tree getArrayName( Tree name,Tree index ) {
	//如果是一个变量，且是一个数组
	//去表中取偏移值
	//从参数中获得另一偏移量
	//指令
		//取地址
		//从地址+偏移量取数
	//NAME改名addr 
	
	Tree offset= newNode( "offset", NULL, NULL, NOP, INT, 0 );
	offset->intgr = index->intgr;
	//暂时只考虑保存位置，type信息由以上type参数保存
	Tree addrl = newNode( "ADDRG", name, offset, NOP, name->ty->type->op, 0 );
	//注意在声明的时候name->ty->op存的是ARRAY,name->ty->type->op存的是元素的类型
	return newNode( "ARRAY", name, offset, INDIR, name->ty->type->op, name->type );

}
/*生成的参数节点右边是单个表达式，左边是表达式列表,当左边NULL时说明已经没有参数
	节点操作：ARG：按照字节大小push
	要点：后序遍历
*/

Tree setConstants( Tree cons ) {
	//没有存进constants，有则通过constants中的名称在开始汇编前放入DATA段
	if (!strcmp( cons->name, "INTNUM" )) {
		strcpy( cons->name, "CNST" );
		cons->opType = INT;
		cons->opPr = INDIR;
		cons->type = 0;
		//直接作为立即数使用
		return cons;

	}
	else if(!strcmp( cons->name, "APPROXNUM" )) {
		strcpy( cons->name, "CNST" );
		cons->opType = 0;
		cons->opPr = FLOAT;
		cons->type = 0;
		//直接作为立即数使用
		return cons;
	}
	else
	{
		//STRING
		strcpy( cons->name, "CNST" );
		cons->opType = ARRAY;
		cons->opPr = INDIR;
		cons->type = 0;
		//暂时只考虑保存位置，type信息由以上type参数保存
		return newNode( "INDIR", cons, NULL, INDIR, ARRAY, 0 );
		
	}
	
}
//直接在语义匹配的时候放置到constant里。在生成汇编的时候检查constant
