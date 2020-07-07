#include "c.h"
//> int i=3; int b=5;int main(){int i=2;i=i+b;}
/*
流程：先打四元式，再generateHead,再优化四元式
还要处理：label的生成
*/
/*
节点信息包括了各种类型的基本信息：
	符号的sym域 
	类型的ty域
	constant类型的值域 u
	constant类型的名称域 idtype
	取地址类型的偏移量域（）
	原始结点的info域
	左右节点 l r
	存储节点名称name域
	存储节点功能域opPr
		类型转换指令
			指令的目的操作数类型域opType
			指令的源操作数类型域（通常由左节点决定）
	指令的操作数类型（0const 1名称变量 2保留标识符 3其他）

	设置generate时候的全局变量
		打印汇编条数: int assLine
		函数个数：functionNumber=0
		常量个数：constantsNumber=0
		域内变量偏移值：identificaionOffset=0
		当前节点是左操作数还是右操作数 ifRight 0左操作数，使用eax，1右操作数使用ebx
操作名称   operation
后缀       type[]
目的操作符 tar
源操作1   sou1
源操作2   sou2
sou: imm
	 reg
		
	实现打印
	data段包括constants与所有全局变量（identification表中残留的）
*/

int stringNum = 0;
 int roundNow = 0;
 int roundMaxTimes = 0;
 int temp = 0;
 int maxTemp = 0;
 //int args = 0;
 int offsetNumber = 0;
 int level;
	level=GLOBAL;
  int label = 0;
  int assLine=0;//打印汇编条数
  int functionNumber =0;//函数个数：
  int constantsNumber =0;//常量个数：
  int identificaionOffset=0 ;//域内变量偏移值：
  int fieldNumber=0 ;//作为跳转的标号
  int regsize[11] = { 0,1,1,4,4,4,4,4,4,4,4 };
  stringList constString;
   LabelStack countinueStack;
   LabelStack breakStack;
   struct midall *midAll;
   struct mid*cur;

   void initialStringList(  ) {
	   constString = (stringList)malloc( sizeof( struct stringlist ) );
	   constString->a = NULL;
	   constString->next = NULL;
   }
   int newStringList( char* newS ) {
	   stringList newList = (stringList)malloc( sizeof( struct stringlist ) );
	   newList->a = newS;
	   newList->i = stringNum++;
	   newList->next = constString->next;
	   constString->next = newList;
	   return  newList->i;
   }

  void initialStack( LabelStack Stack ) {
	  Stack = (LabelStack)malloc( sizeof( struct labelStack ) );
	  if (Stack == NULL)yyerror( "内存分配失败\n" );
	  Stack->label = label;
	  Stack->last = NULL;
}
  void pushStack(int i, LabelStack oldStack ) {
	  LabelStack newStack = (LabelStack)malloc( sizeof( struct labelStack ) );
	  if (newStack == NULL)yyerror( "内存分配失败\n" );
	  newStack->label = i;
	  newStack->last = oldStack;
  }
  int popStack( LabelStack oldStack ) {
	  LabelStack tempStack = oldStack->last;
	  if (tempStack != NULL) {
		  int i = oldStack->label;
		  oldStack->last = tempStack->last;
		  oldStack->label = tempStack->label;
		  free( tempStack );
		  return i;
	  }
	  return -1;
  }
  int getStack( LabelStack oldStack ) {
	  return oldStack->label;
  }

  void Initial( ) {
	  initialStack( countinueStack );
	  initialStack( breakStack );
	  initialStringList( );
	  midAllInitial( );
	  typeInit( );
	  printf( "> " );
  }

  /*
  中间代码生成
	只要节点信息不是nop的都是要生成四元式的
	
关于子函数变量
	：由于之前进行语义分析，所以在达到
	Specifire NAME FunDecList SEMI 时进行函数声明
	（CONSTLEX） Specifire NAME FunDecList Compst	
	Tree funcDef(Tree type,Tree name,Tree args,int ifconst,Tree explist )
	进行了函数的声明
		field的影响究竟应该怎样判定
	！！！我知道了！！！
	每一次读到大括号就level+1是可行的
	但是每一次退出当前level需要在compst配对成功、function配对成功时的时候，退出当前level，另外 在匹配成state与function的时候清除当前层级删除当前符号表

	每一出现一个函数定义，检查是否为main，如果是，需要startup
	k开始生成四元式
	定义四元式数据结构
	struct mid{
	int op
	int op1
	int op2
	int op3
	struct mid next};
	同时需要定义字符串数组
	reg_32
	{"eax","ebx","ecx","edx",...}
	reg_16
	{"ax","bx","cx,"dx",...}
	reg_8
	{"al","bl","cl,"dl",...}

  */


/*
if(!strcmp(nade->name,"EQ")
  //cmp %eax, 0
  //je  node->intgr
	printf("\
	
	cmp %eax, 0\n\
	je  %d\n\
	
	",node->intgr);

if(!strcmp(nade->name,"JUMP")
//JUMP LABEL
	printf("\

	jmp  %d\n\

	",node->intgr);

if(!strcmp(nade->name,"LABEL")
//LABEL:
	printf("\

	jmp  %d\n\

	",node->intgr);
	%d:\n\
*/
  struct mid* curMid;
  struct mid* expGen( Tree expOp, int ifeax, struct mid* m ) {
	  //如果子节点为叶节点
	  if (expOp != NULL) {
		  if (expOp->l != NULL) {

			  if (expOp->l->opPr == NOP) expGen( expOp->l, ifeax, m );
			  else expGen( expOp->l, 1, m );

		  }
		  if (expOp->r != NULL) {

			  if (expOp->r->opPr == NOP) expGen( expOp->r, ifeax, m );
			  else expGen( expOp->r, 0, m );

		  }
		  return opMidGen( expOp, ifeax, m );
	  }
	  return NULL;

  }
/*
   struct mid* expGen(Tree expOp,int ifeax , struct mid* m) {
		//如果子节点为叶节点
	  if(expOp!=NULL){
		  if (expOp->l != NULL) {

			  if (expOp->l->opPr == NOP) expGen( expOp->l, ifeax, m );
			  else opMidGen( expOp->l, 1, m );

		  }
		  if (expOp->r != NULL) {
			 
				  if (expOp->r->opPr == NOP) expGen( expOp->r, ifeax, m );
				  else expGen( expOp->r, 0, m );
			 
		  }
		  return opMidGen( expOp, ifeax, m );
	  }
	  return NULL;
	  
}
 */
  /*
   struct mid* expGen(Tree expOp,int ifeax , struct mid* m) {
		//如果子节点为叶节点
	  if (expOp->l != NULL) {
		  if (expOp->l->opPr!=NOP||(expOp->l->l != NULL || expOp->l->r != NULL)) {
			  if(expOp->l->opPr==NOP) expGen( expOp->l, ifeax, m );
			  else opMidGen( expOp->l, 1, m);
		  }
	  }
	  if(expOp->r != NULL) {
		  if (expOp->r->opPr != NOP ||( expOp->r->l != NULL || expOp->r->r != NULL)) {
			  if (expOp->r->opPr == NOP) expGen( expOp->r, ifeax, m );
			  else expGen( expOp->r,0,m );
		  }
	  }
	  return opMidGen( expOp, ifeax,m );
}*/
struct mid* opMidGen(Tree midOp,int ifeax, struct mid* m ) {
	  //如果当前节点操作符是NOP（不生成）
	  //INDIR CNST
	  //如果是操作符 二元
	printf(  "%s\n", midOp->name );
	  if (midOp->opPr == NOP)return m;
	  struct mid* newMid = (struct mid*)malloc( sizeof( struct mid ) );
	  //newMid->next = m;
	  newMid->opNUM = midOp->opPr;
	  newMid->next = NULL;
	  curMid->next = newMid;
	  curMid = newMid;
	  //newMid->opNUM = midOp->name;
	  if (newMid->opNUM == CALL) {
	  //如果是call
	  //call op1是name
		  newMid->op = "call";
		  newMid->op1 = midOp->r->idtype;
		  newMid->op1Size =midOp->intgr;//要加的是push进去的参数个数
		  newMid->op2 = NULL;
		  newMid->op2Size = 0;
		  newMid->ifeax = ifeax;
	  }
	  if (newMid->opNUM == RET) {
		  //如果是call
		  //call op1是name
		  newMid->op = "ret";
		  if (midOp->l == NULL) {
			  newMid->op1 = NULL;
			  newMid->op1Size = 0;
		  }
		  else
		  {
			  newMid->op1 = "retmov";
			  newMid->op1Offset = midOp->offset;
		  }
		  newMid->op2 = NULL;
		  newMid->op2Size = 0;
		  newMid->ifeax = ifeax;
	  }

	  else if (newMid->opNUM == POP) {
		  //如果是pop
		//POP op1是操作数
		//op1 Size决定那个寄存器
		//保存ifeax
		  if (!strcmp( midOp->name, "POPFUNC" )) {
			  newMid->op = "popfunc";
			  newMid->op1 = "reg";
			  newMid->op1Offset = midOp->offset;
		  }
		  else {
			  newMid->op = "pop";
			  newMid->op1 = "reg";
			  newMid->op1Size = regsize[midOp->opType];
		  }
		  newMid->op2 = NULL;
		  newMid->op2Size = 0;
		  newMid->ifeax = ifeax;
	  }
	  else if (newMid->opNUM == JUMP) {
		  //如果是pop
		//POP op1是操作数
		//op1 Size决定那个寄存器
		//保存ifeax
		  newMid->op = "jump";
		  newMid->op1 = NULL;
		  newMid->op1Size = midOp->intgr;
		  newMid->op2 = NULL;
		  newMid->op2Size = 0;
		  newMid->ifeax = ifeax;
	  }
	  else if (newMid->opNUM == LABEL) {
		  //如果是pop
		//POP op1是操作数
		//op1 Size决定那个寄存器
		//保存ifeax
		  newMid->op = "label";
		  newMid->op1 = NULL;
		  newMid->op1Size = midOp->intgr;
		  newMid->op2 = NULL;
		  newMid->op2Size = 0;
		  newMid->ifeax = ifeax;
	  }
	  else if (newMid->opNUM == EQ) {
		  //如果是pop
		//POP op1是操作数
		//op1 Size决定那个寄存器
		//保存ifeax

		  newMid->op = "EQ";
		  if (midOp->l->opPr != INDIR) {
			  newMid->op1 = "ebp";
			  newMid->op1Offset = midOp->l->offset;
		  }
		  else
			  newMid->op1 = "eax";
		  newMid->resultOffset = midOp->intgr;
		  newMid->op2 = NULL;
		  newMid->op2Size = 0;
		  newMid->ifeax = ifeax;
	  }
	  else if (newMid->opNUM == INDIR) {
	 //如果是INDIRNAME
	 //操作mov
	 //op1size=op2Size
	 //op2Size根据optype决定
		  
		  newMid->op1 = "reg";//目的由ifeax决定
		  if (!strcmp( midOp->name, "CNST" )) {//立即数
			  newMid->op = "movimm";
			  newMid->op2 = "0imm";
			  newMid->op2Size = midOp->intgr;//此时op2存放立即数
			  newMid->op1Size = regsize[midOp->opType];
		  }
		  else if( !strcmp( midOp->name, "ARRAY" ) ) {
			  newMid->op2 = midOp->l->idtype;
			  newMid->op2Size = midOp->intgr;//需要注意这里的size
			  newMid->op1Offset = lookup( newMid->op2, identifiers )->offset;
			  newMid->op2Offset = midOp->r->intgr;
		  }
		  else if (!strcmp( midOp->name, "INDIRNAME" )) {//全局变量
			  newMid->op = "movname";
			  newMid->op2 = midOp->l->idtype;//常量可以通过名字直接取得
			  newMid->op2Size = midOp->intgr;
		  }
		  else if (!strcmp( midOp->name, "INDIREXP" )) {//本地变量
			  newMid->op = "movebp";
			  newMid->op2 ="0ebp";//常量可以通过名字直接取得
			  
			  newMid->op2Offset = midOp->offset;
			  newMid->op2Size = regsize[midOp->opType];
		  }
		  else{

			  newMid->op2 = midOp->l->idtype;
			  newMid->op2Size = regsize[midOp->opType];
			  newMid->op1Size = regsize[midOp->opType];
		  }
		 
		  newMid->ifeax = ifeax;

	  }
	 
	  else if (newMid-> opNUM== ARG) {
	  //分情况讨论，如果左边不是INDIR，可以直接push eax
		  newMid->op = "push";
		  if (midOp->opPr != INDIR) {
			  newMid->op1 = "ebp";
			  newMid->op1Offset = midOp->r->offset;
		  }
		  else
			 newMid->op1 = "edx";
		  newMid->op1Size = regsize[midOp->opType];
		  newMid->op2 = NULL;
		  newMid->op2Size = 0;
		  newMid->ifeax = ifeax;
		  //arg的参数一直是右边的exp optype
	  }
	  //两操作数
	  else if (newMid->opNUM <= SUB&& newMid->opNUM > NEG) {
		  //最后是否要交换eax\edx内容由ifeax决定
		  newMid->op = midOp->name;
		  //先判断第一个
		  if (midOp->l->opPr!=INDIR) {
			  newMid->op1 = "0ebp";
			  newMid->op1Offset = midOp->l->offset;
		  }
		  else {
			  newMid->op1 = "eax";
			  newMid->op2Offset = 0;
			  //自己取得放到edx
		  }
		  if (midOp->r->opPr != INDIR) {
			  newMid->op2 = "0ebp";
			  newMid->op2Offset = midOp->r->offset;
		  }
		  else {
			  newMid->op2 = "edx";
			  newMid->op2Offset = 0;
			  //自己取得放到edx
		  }
		  newMid->resultOffset = midOp->offset;
		  newMid->op1Size = regsize[midOp->l->opType];
		  newMid->op2Size = regsize[midOp->r->opType];
		  newMid->ifeax = ifeax;
		  //arg的参数一直是右边的exp optype
	  }
	  else if (newMid->opNUM== ASGN) {
		  newMid->op = "assign";
		  if (!strcmp( midOp->l->name, "INDIRNAME" )) {
			  //全局变量可通过名字读取
			  if(midOp->l->l==NULL)
			  newMid->op1 = midOp->l->idtype;
			  else
				  newMid->op1 = midOp->l->l->idtype;
		  }
		  else if (!strcmp( midOp->l->name, "INDIREXP" )) {
			  //本地变量通过ebp+offet读取
			  newMid->op1 ="0ebp";
			  newMid->op1Offset =midOp->l->offset;
		  }
		  if (!strcmp( midOp->r->name, "INDIRNAME" )) {
			  //已经进行过处理，存放在edx中
			  newMid->op2 = midOp->r->idtype;
		  }
		  else if(!strcmp( midOp->r->name, "INDIREXP" )) {
			  //右边是表达式
			  newMid->op2 = "0ebp";
			  newMid->op2Offset = midOp->r->offset;
			  //自己取得放到edx
		  }
		  else if (!strcmp( midOp->r->name, "CNST" )) {
			  newMid->op2 = "imm";
			  newMid->op2Size=midOp->r->intgr;
		  }
		  else {
			  //右边是表达式
			  newMid->op2 = "0ebp";
			  newMid->op2Offset = midOp->r->offset;
			  //自己取得放到edx
		  }
		  //newMid->op1Size = regsize[midOp->opType];
		  //newMid->op2Size = newMid->op1Size;
		  newMid->ifeax = ifeax;//如果ifeax为真，需要先把mov edx->eax,再eax到相应地点
		
	  }
	  
	  //暂时废弃
	  else if (newMid->opNUM == ADDRG) {
		  //取地址,返回的全是地址
		  newMid->op = "mov";
		  newMid->op1 = "reg"; 
		  newMid->op1Size = 4;
		  newMid->op2Size = 4;
		  newMid->op2 = midOp->l->idtype;
		  newMid->op1Offset = 0;
		  newMid->op2Offset = 0;
		  
		  newMid->ifeax = ifeax;
		  //arg的参数一直是右边的exp optype
	  }
	  return m;
  }


  /*
  struct midall{
  struct mid* main;
  struct midrest{
	struct mid* func;
	char *funcName;
	Type funcType;
	struct midrest*next;
	}*midRest;
  }*midAll;
  全部四元式生成之后就放置在midAll结构里

  */
  //每次碰到一个新的，产生一个midRest,把其struct mid传出来
  void midAllInitial(){
	 // struct midall *midAll;
	  midAll = (struct midall*)malloc( sizeof( struct midall ) );
	  midAll->main = NULL;
	  midAll->midRest = NULL;
  }
  struct mid* midCurUpdate( char* funcName, Type funcType ) {
	  struct midrest *midcur;
	  midcur = (struct midrest*)malloc( sizeof( struct midrest ) );
	  midcur->next = midAll->midRest;
	  midcur->func = (struct mid*)malloc( sizeof( struct mid ) );
	  midcur->funcName = funcName;
	  midcur->funcType = funcType;
	  midAll->midRest = midcur;
	  return midcur->func;
  }//更新其他某个函数的四元式
 struct mid* midMainUpdate(  Type funcType ) {
	 midAll->main = (struct mid*)malloc( sizeof( struct mid ) );
	 midAll->funcType = funcType;
	 return midAll->main;
 }//更新main的四元式

 //需要实现临时变量
 //1.栈的大小应当是当前的所有本地变量+临时变量
 //2.

  //遍历四元式
 void scanMidEqual( FILE * fpWrite ) {
	 struct mid* midEqual=midAll->main;
	 if (midAll == NULL) {
		 yyerror( "no main!no entrance!\n" );
	 }
	 char*  funcName=NULL;
	 funcName = (char*)malloc( 4*sizeof(char) );
	 strcpy(funcName,"main");
	 Type funcType=midAll->funcType;
	// generateFuncHead( fpWrite ,funcType->u.f.funcSize);
	 scanMainEqual(  funcType, midEqual,fpWrite );
	 if (midAll->midRest != NULL) {
		 struct midrest* otherFuncMid = midAll->midRest;
		 midEqual = otherFuncMid->func;
		 funcName = otherFuncMid->funcName;
		 funcType = otherFuncMid->funcType;
		 while (otherFuncMid != NULL) {
			 midEqual = otherFuncMid->func;
			 funcName = otherFuncMid->funcName;
			 funcType = otherFuncMid->funcType;
			 fprintf( fpWrite, "%s:\n" ,funcName);
			 generateFuncHead( fpWrite, funcType->u.f.funcSize );
			 scanMainEqual( funcType, midEqual, fpWrite );
			 //printf( "\nend\n" );
		 }
	 }
}
 void scanMainEqual( Type funcType, struct mid* midEqual , FILE * fpWrite ) {
	 char* op;
	 int opNUM;
	 char* op1;
	 int op1Offset;
	 int op1Size;
	 int op2Size;
	 char* op2;
	 int op2Offset;
	 struct mid *next;
	 int ifeax;
	 int resultOffset;
	 //开始，需要把参数转移,应该是在那个 开头之后
	 int i;
	 generateFuncHead( fpWrite, funcType->u.f.funcSize );
	 if (i = funcType->u.f.args > 0) {
		 for (int a = 0;a < i;a++) {
			 int offset = funcType->u.f.proto[a]->u.sym->offset;
			 fprintf( fpWrite, "    mov [ebp-%d][ebp+%d]\n", offset * 4, 8 + a * 4 );
		 }
	 }
	 struct mid *cur = midEqual->next;
	 while (cur) {
		 op = cur->op;
		 opNUM = cur->opNUM;
		 op1 = cur->op1;
		 op2 = cur->op2;
		 op1Offset = cur->op1Offset;
		 op2Offset = cur->op2Offset;
		 op1Size = cur->op1Size;
		 op2Size = cur->op2Size;
		 next = cur->next;
		 ifeax = cur->ifeax;
		 resultOffset = cur->resultOffset;
		 fprintf( fpWrite, ";%s\n", op );
		 //fpos_t home;
		// char st[100];
		 //fgetpos( fpWrite, &home );
		 if (!strcmp( op, "call" )) {
			 fprintf( fpWrite, "    call %s\n", op1 );
			 if (op1Offset > 0)
				 fprintf( fpWrite, "    add esp,%d\n", op1Offset * 4 );
			 if (funcType->type != NULL)
				 fprintf( fpWrite, "    push ebx\n" );
		 }
		 else if (!strcmp( op, "popfunc" )) {
			 fprintf( fpWrite, "    mov [ebp-%d] ebx\n", op1Offset * 4 );
			 fprintf( fpWrite, "    pop ebx\n" );
		 }
		 else if (!strcmp( op, "label" )) {
			 fprintf( fpWrite, "    .label_%d\n", op1Size );
		 }
		 else if (!strcmp( op, "ret" )) {
			 if (!strcmp( op1, "retmov" ))
				 fprintf( fpWrite, "   mov ebx,[ebp-%d]\n", op1Offset*4 );
			 fprintf( fpWrite, "   leave\n" );
			 fprintf( fpWrite, "   ret\n" );
		 }
		 else if (!strcmp( op, "movebp" )) {//
			 if (ifeax)
				 fprintf( fpWrite, "   mov eax,[ebp-%d]\n", op2Offset*4 );
			 else
				 fprintf( fpWrite, "   mov edx,[ebp-%d]\n", op2Offset *4);
		 }
		 else if (!strcmp( op, "movname" )) {//
			 if (ifeax)
				 fprintf( fpWrite, "   mov eax,%s\n", op2 );
			 else
				 fprintf( fpWrite, "   mov edx,%s\n", op2 );
		 }
		 else if (!strcmp( op, "movimm" )) {//
			 if (ifeax)
				 fprintf( fpWrite, "   mov eax,dword %d\n", op2Size );
			 else
				 fprintf( fpWrite, "   mov edx,dword %d\n", op2Size );
		 }
		 else if (!strcmp( op, "EQ" )) {
			 if (!strcmp( op1, "ebp" ))
				 fprintf( fpWrite, "   cmp [ebp-%d],dword 0\n", op1Offset*4 );
			 else fprintf( fpWrite, "   cmp eax,dword 0\n" );
			 fprintf( fpWrite, "   je .label%d\n", resultOffset );
		 }
		 else if (!strcmp( op, "jump" )) {
			 fprintf( fpWrite, "   jmp .label%d\n", op1Size );

		 }
		 else if (!strcmp( op, "arg" )) {
			 if (!strcmp( op1, "ebp" ))
				 fprintf( fpWrite, "   push [ebp-%d]\n", op1Offset *4);
			 else
				 fprintf( fpWrite, "   push edx\n" );

		 }
		 else if (!strcmp( op, "SUB" )) {
			 //strlwr()
			 if (!strcmp( op1, "0ebp" )) {
				 fprintf( fpWrite, "   mov eax,[ebp-%d]\n", op1Offset*4 );
			 }
			 if (!strcmp( op2, "0ebp" )) {
				 fprintf( fpWrite, "   mov edx,[ebp-%d]\n", op2Offset *4);
			 }
			 else
				 fprintf( fpWrite, "   sub eax,edx\n" );
			 if (!ifeax)
				 fprintf( fpWrite, "   mov edx,eax\n" );
		 }
		 else if (!strcmp( op, "ADD" )) {
			 //strlwr()
			 if (!strcmp( op1, "0ebp" )) {
				 fprintf( fpWrite, "   mov eax,[ebp-%d]\n", op1Offset *4);
			 }
			 if (!strcmp( op2, "0ebp" )) {
				 fprintf( fpWrite, "   mov edx,[ebp-%d]\n", op2Offset*4 );
			 }

			 if (!ifeax) {
				 fprintf( fpWrite, "   add edx,eax\n" );
				 fprintf( fpWrite, "   mov [ebp-%d],edx\n", resultOffset * 4 );
			 }
			 else {
				 fprintf( fpWrite, "   add eax,edx\n" );
				 fprintf( fpWrite, "   mov [ebp-%d],eax\n", resultOffset * 4 );
			 }


		 }
		 else if (!strcmp( op, "MUL" )) {

		 }
		 else if (!strcmp( op, "BAND" )) {
			 if (!strcmp( op1, "0ebp" )) {
				 fprintf( fpWrite, "   mov eax,[ebp-%d]\n", op1Offset *4);
			 }
			 if (!strcmp( op2, "0ebp" )) {
				 fprintf( fpWrite, "   mov edx,[ebp-%d]\n", op2Offset*4 );
			 }
			 if (!ifeax) {
				 fprintf( fpWrite, "   and edx,eax\n" );
				 fprintf( fpWrite, "   mov [ebp-%d],edx\n", resultOffset * 4 );
			 }
			 else {
				 fprintf( fpWrite, "   and eax,edx\n" );
				 fprintf( fpWrite, "   mov [ebp-%d],eax\n", resultOffset * 4 );
			 }
		 }
		 else if (!strcmp( op, "BOR" )) {
			 //strlwr()
			 if (!strcmp( op1, "0ebp" )) {
				 fprintf( fpWrite, "   mov eax,[ebp-%d]\n", op1Offset*4 );
			 }
			 if (!strcmp( op2, "0ebp" )) {
				 fprintf( fpWrite, "   mov edx,[ebp-%d]\n", op2Offset*4 );
			 }
			 if (!ifeax) {
				 fprintf( fpWrite, "   or edx,eax\n" );
				 fprintf( fpWrite, "   mov [ebp-%d],edx\n", resultOffset * 4 );
			 }
			 else {
				 fprintf( fpWrite, "   or eax,edx\n" );
				 fprintf( fpWrite, "   mov [ebp-%d],eax\n", resultOffset * 4 );
			 }
		 }
		 else if (!strcmp( op, "BAND" )) {
			 //strlwr()
			 if (!strcmp( op1, "0ebp" )) {
				 fprintf( fpWrite, "   mov eax,[ebp-%d]\n", op1Offset*4 );
			 }
			 if (!strcmp( op2, "0ebp" )) {
				 fprintf( fpWrite, "   mov edx,[ebp-%d]\n", op2Offset*4 );
			 }
			 if (!ifeax) {
				 fprintf( fpWrite, "   and edx,eax\n" );
				 fprintf( fpWrite, "   mov [ebp-%d],edx\n", resultOffset * 4 );
			 }
			 else {
				 fprintf( fpWrite, "   and eax,edx\n" );
				 fprintf( fpWrite, "   mov [ebp-%d],eax\n", resultOffset * 4 );
			 }
		 }
		 else if (!strcmp( op, "BNOT" )) {
			 //strlwr()
			 if (!strcmp( op1, "0ebp" )) {
				 fprintf( fpWrite, "   mov eax,[ebp-%d]\n", op1Offset*4 );
			 }
			 if (!strcmp( op2, "0ebp" )) {
				 fprintf( fpWrite, "   mov edx,[ebp-%d]\n", op2Offset*4 );
			 }
			 if (!ifeax) {
				 fprintf( fpWrite, "   not edx,eax\n" );
				 fprintf( fpWrite, "   mov [ebp-%d],edx\n", resultOffset * 4 );
			 }
			 else {
				 fprintf( fpWrite, "   not eax,edx\n" );
				 fprintf( fpWrite, "   mov [ebp-%d],eax\n", resultOffset * 4 );
			 }
		 }
		 else if (!strcmp( op, "assign" )) {
		 //strlwr()
			 if (!strcmp( op2, "0ebp" )) {
				 fprintf( fpWrite, "   mov edx,[ebp-%d]\n", op2Offset*4 );
			 }
			 else if (!strcmp( op2, "imm" )) {
				 fprintf( fpWrite, "   mov edx,dword %d\n", op2Size );
			 }
			 else {
				 fprintf( fpWrite, "   mov edx,%s\n", op2 );
			 }
			 if (!strcmp( op1, "0ebp" )) {
				 fprintf( fpWrite, "   mov [ebp-%d],edx\n", op1Offset*4 );
			 }
			 else{
				 fprintf( fpWrite, "   mov [%s],edx\n", op1 );
			 }
			 if (ifeax)
				 fprintf( fpWrite, "   mov eax,edx\n" );
		 }
		 else if (!strcmp( op, "mov" )) {

			 fprintf( fpWrite, "   sub eax,edx\n" );
		 }
		 cur = next;
		 //fsetpos( fpWrite, &home ); /*将文件fp的读写位置设置为上次保存的位置*/
		 //fgets( st, 100, fpWrite );
		 //fprintf( fpWrite, "\n" ); /*读取文件第一行*/
		// puts( st );
	 }
 }