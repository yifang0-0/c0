#include "c.h"
//> int i=3; int b=5;int main(){int i=2;i=i+b;}
/*
���̣��ȴ���Ԫʽ����generateHead,���Ż���Ԫʽ
��Ҫ����label������
*/
/*
�ڵ���Ϣ�����˸������͵Ļ�����Ϣ��
	���ŵ�sym�� 
	���͵�ty��
	constant���͵�ֵ�� u
	constant���͵������� idtype
	ȡ��ַ���͵�ƫ�����򣨣�
	ԭʼ����info��
	���ҽڵ� l r
	�洢�ڵ�����name��
	�洢�ڵ㹦����opPr
		����ת��ָ��
			ָ���Ŀ�Ĳ�����������opType
			ָ���Դ������������ͨ������ڵ������
	ָ��Ĳ��������ͣ�0const 1���Ʊ��� 2������ʶ�� 3������

	����generateʱ���ȫ�ֱ���
		��ӡ�������: int assLine
		����������functionNumber=0
		����������constantsNumber=0
		���ڱ���ƫ��ֵ��identificaionOffset=0
		��ǰ�ڵ���������������Ҳ����� ifRight 0���������ʹ��eax��1�Ҳ�����ʹ��ebx
��������   operation
��׺       type[]
Ŀ�Ĳ����� tar
Դ����1   sou1
Դ����2   sou2
sou: imm
	 reg
		
	ʵ�ִ�ӡ
	data�ΰ���constants������ȫ�ֱ�����identification���в����ģ�
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
  int assLine=0;//��ӡ�������
  int functionNumber =0;//����������
  int constantsNumber =0;//����������
  int identificaionOffset=0 ;//���ڱ���ƫ��ֵ��
  int fieldNumber=0 ;//��Ϊ��ת�ı��
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
	  if (Stack == NULL)yyerror( "�ڴ����ʧ��\n" );
	  Stack->label = label;
	  Stack->last = NULL;
}
  void pushStack(int i, LabelStack oldStack ) {
	  LabelStack newStack = (LabelStack)malloc( sizeof( struct labelStack ) );
	  if (newStack == NULL)yyerror( "�ڴ����ʧ��\n" );
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
  �м��������
	ֻҪ�ڵ���Ϣ����nop�Ķ���Ҫ������Ԫʽ��
	
�����Ӻ�������
	������֮ǰ������������������ڴﵽ
	Specifire NAME FunDecList SEMI ʱ���к�������
	��CONSTLEX�� Specifire NAME FunDecList Compst	
	Tree funcDef(Tree type,Tree name,Tree args,int ifconst,Tree explist )
	�����˺���������
		field��Ӱ�쾿��Ӧ�������ж�
	��������֪���ˣ�����
	ÿһ�ζ��������ž�level+1�ǿ��е�
	����ÿһ���˳���ǰlevel��Ҫ��compst��Գɹ���function��Գɹ�ʱ��ʱ���˳���ǰlevel������ ��ƥ���state��function��ʱ�������ǰ�㼶ɾ����ǰ���ű�

	ÿһ����һ���������壬����Ƿ�Ϊmain������ǣ���Ҫstartup
	k��ʼ������Ԫʽ
	������Ԫʽ���ݽṹ
	struct mid{
	int op
	int op1
	int op2
	int op3
	struct mid next};
	ͬʱ��Ҫ�����ַ�������
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
	  //����ӽڵ�ΪҶ�ڵ�
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
		//����ӽڵ�ΪҶ�ڵ�
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
		//����ӽڵ�ΪҶ�ڵ�
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
	  //�����ǰ�ڵ��������NOP�������ɣ�
	  //INDIR CNST
	  //����ǲ����� ��Ԫ
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
	  //�����call
	  //call op1��name
		  newMid->op = "call";
		  newMid->op1 = midOp->r->idtype;
		  newMid->op1Size =midOp->intgr;//Ҫ�ӵ���push��ȥ�Ĳ�������
		  newMid->op2 = NULL;
		  newMid->op2Size = 0;
		  newMid->ifeax = ifeax;
	  }
	  if (newMid->opNUM == RET) {
		  //�����call
		  //call op1��name
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
		  //�����pop
		//POP op1�ǲ�����
		//op1 Size�����Ǹ��Ĵ���
		//����ifeax
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
		  //�����pop
		//POP op1�ǲ�����
		//op1 Size�����Ǹ��Ĵ���
		//����ifeax
		  newMid->op = "jump";
		  newMid->op1 = NULL;
		  newMid->op1Size = midOp->intgr;
		  newMid->op2 = NULL;
		  newMid->op2Size = 0;
		  newMid->ifeax = ifeax;
	  }
	  else if (newMid->opNUM == LABEL) {
		  //�����pop
		//POP op1�ǲ�����
		//op1 Size�����Ǹ��Ĵ���
		//����ifeax
		  newMid->op = "label";
		  newMid->op1 = NULL;
		  newMid->op1Size = midOp->intgr;
		  newMid->op2 = NULL;
		  newMid->op2Size = 0;
		  newMid->ifeax = ifeax;
	  }
	  else if (newMid->opNUM == EQ) {
		  //�����pop
		//POP op1�ǲ�����
		//op1 Size�����Ǹ��Ĵ���
		//����ifeax

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
	 //�����INDIRNAME
	 //����mov
	 //op1size=op2Size
	 //op2Size����optype����
		  
		  newMid->op1 = "reg";//Ŀ����ifeax����
		  if (!strcmp( midOp->name, "CNST" )) {//������
			  newMid->op = "movimm";
			  newMid->op2 = "0imm";
			  newMid->op2Size = midOp->intgr;//��ʱop2���������
			  newMid->op1Size = regsize[midOp->opType];
		  }
		  else if( !strcmp( midOp->name, "ARRAY" ) ) {
			  newMid->op2 = midOp->l->idtype;
			  newMid->op2Size = midOp->intgr;//��Ҫע�������size
			  newMid->op1Offset = lookup( newMid->op2, identifiers )->offset;
			  newMid->op2Offset = midOp->r->intgr;
		  }
		  else if (!strcmp( midOp->name, "INDIRNAME" )) {//ȫ�ֱ���
			  newMid->op = "movname";
			  newMid->op2 = midOp->l->idtype;//��������ͨ������ֱ��ȡ��
			  newMid->op2Size = midOp->intgr;
		  }
		  else if (!strcmp( midOp->name, "INDIREXP" )) {//���ر���
			  newMid->op = "movebp";
			  newMid->op2 ="0ebp";//��������ͨ������ֱ��ȡ��
			  
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
	  //��������ۣ������߲���INDIR������ֱ��push eax
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
		  //arg�Ĳ���һֱ���ұߵ�exp optype
	  }
	  //��������
	  else if (newMid->opNUM <= SUB&& newMid->opNUM > NEG) {
		  //����Ƿ�Ҫ����eax\edx������ifeax����
		  newMid->op = midOp->name;
		  //���жϵ�һ��
		  if (midOp->l->opPr!=INDIR) {
			  newMid->op1 = "0ebp";
			  newMid->op1Offset = midOp->l->offset;
		  }
		  else {
			  newMid->op1 = "eax";
			  newMid->op2Offset = 0;
			  //�Լ�ȡ�÷ŵ�edx
		  }
		  if (midOp->r->opPr != INDIR) {
			  newMid->op2 = "0ebp";
			  newMid->op2Offset = midOp->r->offset;
		  }
		  else {
			  newMid->op2 = "edx";
			  newMid->op2Offset = 0;
			  //�Լ�ȡ�÷ŵ�edx
		  }
		  newMid->resultOffset = midOp->offset;
		  newMid->op1Size = regsize[midOp->l->opType];
		  newMid->op2Size = regsize[midOp->r->opType];
		  newMid->ifeax = ifeax;
		  //arg�Ĳ���һֱ���ұߵ�exp optype
	  }
	  else if (newMid->opNUM== ASGN) {
		  newMid->op = "assign";
		  if (!strcmp( midOp->l->name, "INDIRNAME" )) {
			  //ȫ�ֱ�����ͨ�����ֶ�ȡ
			  if(midOp->l->l==NULL)
			  newMid->op1 = midOp->l->idtype;
			  else
				  newMid->op1 = midOp->l->l->idtype;
		  }
		  else if (!strcmp( midOp->l->name, "INDIREXP" )) {
			  //���ر���ͨ��ebp+offet��ȡ
			  newMid->op1 ="0ebp";
			  newMid->op1Offset =midOp->l->offset;
		  }
		  if (!strcmp( midOp->r->name, "INDIRNAME" )) {
			  //�Ѿ����й����������edx��
			  newMid->op2 = midOp->r->idtype;
		  }
		  else if(!strcmp( midOp->r->name, "INDIREXP" )) {
			  //�ұ��Ǳ��ʽ
			  newMid->op2 = "0ebp";
			  newMid->op2Offset = midOp->r->offset;
			  //�Լ�ȡ�÷ŵ�edx
		  }
		  else if (!strcmp( midOp->r->name, "CNST" )) {
			  newMid->op2 = "imm";
			  newMid->op2Size=midOp->r->intgr;
		  }
		  else {
			  //�ұ��Ǳ��ʽ
			  newMid->op2 = "0ebp";
			  newMid->op2Offset = midOp->r->offset;
			  //�Լ�ȡ�÷ŵ�edx
		  }
		  //newMid->op1Size = regsize[midOp->opType];
		  //newMid->op2Size = newMid->op1Size;
		  newMid->ifeax = ifeax;//���ifeaxΪ�棬��Ҫ�Ȱ�mov edx->eax,��eax����Ӧ�ص�
		
	  }
	  
	  //��ʱ����
	  else if (newMid->opNUM == ADDRG) {
		  //ȡ��ַ,���ص�ȫ�ǵ�ַ
		  newMid->op = "mov";
		  newMid->op1 = "reg"; 
		  newMid->op1Size = 4;
		  newMid->op2Size = 4;
		  newMid->op2 = midOp->l->idtype;
		  newMid->op1Offset = 0;
		  newMid->op2Offset = 0;
		  
		  newMid->ifeax = ifeax;
		  //arg�Ĳ���һֱ���ұߵ�exp optype
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
  ȫ����Ԫʽ����֮��ͷ�����midAll�ṹ��

  */
  //ÿ������һ���µģ�����һ��midRest,����struct mid������
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
  }//��������ĳ����������Ԫʽ
 struct mid* midMainUpdate(  Type funcType ) {
	 midAll->main = (struct mid*)malloc( sizeof( struct mid ) );
	 midAll->funcType = funcType;
	 return midAll->main;
 }//����main����Ԫʽ

 //��Ҫʵ����ʱ����
 //1.ջ�Ĵ�СӦ���ǵ�ǰ�����б��ر���+��ʱ����
 //2.

  //������Ԫʽ
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
	 //��ʼ����Ҫ�Ѳ���ת��,Ӧ�������Ǹ� ��ͷ֮��
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
		 //fsetpos( fpWrite, &home ); /*���ļ�fp�Ķ�дλ������Ϊ�ϴα����λ��*/
		 //fgets( st, 100, fpWrite );
		 //fprintf( fpWrite, "\n" ); /*��ȡ�ļ���һ��*/
		// puts( st );
	 }
 }