
//#include "config.h"
/*c.h定义了编译器的全局结构和部分全局函数*/

/*如果定义了__STDC__就需要把完整的ansi参数类型作为参数生成类型列表*/

//extern void outs( char* );

//op由操作数类型（后四位）+操作动作编号（倒数5位之后）组成 如ADDI:ADD<<4+I ADD与I都实现定义

/*
分配的形式
struct T *p;
p= allocate(sizeof *p,a);//仅仅依赖于指针而不是依赖于指针指向的类型的分配方式可以防止将分配空间分给错误的类型
*/

#pragma  once  
#include "c.h"

#ifndef _SAAKAA_DATA_BASE_HEAD   
#define _SAAKAA_DATA_BASE_HEAD
#include <string.h>
#include <stdlib.h>
#include"stdbool.h"
#include <stdio.h>
# include<stdarg.h>
#include "limits.h"
#define generic(op) ((op)&~15)
#define optype(op) ((op)&15)
#define opindex(op) ((op)>>4)

enum {
	CHAR = 1, UNSIGNEDCHAR,INT,UNSIGNED, FLOAT,
	ARRAY, FUNCTION, POINTER, VOID,CONST
};//类型修饰符

enum {
	NOP=0,ADDRF=1,ADDRG,ADDRL,CNST,BCOM,
	CVC,CVI, CVF, CVU,CVP,
	INDIR,NEG,ADD,BAND,BOR,
	BXOR,DIV,LSH,MOD,MUL,
	RSH,SUB,ASGN,
	EQ,GE,GT,LE,LT,NE,
	ARG,CALL,RET,JUMP,LABEL,
	PUSH,POP
};//操作符


/*************************typedef**********************************/
typedef struct coord {
	char *file;
	unsigned x, y;
}Coordinate;


typedef struct type *Type;
typedef struct field *Field;
typedef struct symbol *Symbol;
typedef struct table *Table;
/*************************input*******************************/

extern int yylex( );
extern int yylineno;
extern char *yytext;
extern Coordinate src;
/*************************list*********************************/
typedef struct list *List;
struct list {
	void *x;
	List link;
};
//***********************global********************************/
typedef struct node *Node;


enum {
	C = CHAR,
	I = INT,
	U = UNSIGNED,
	F = FLOAT,
	P = POINTER,
	V = VOID

};

//**********************alloc*****************************///
//alloc data

struct block {
	struct block *next;
	char *limit;
	char *avail;
	//可分配空间的首地址
};



/***********************symbol*****************************/
extern int label;
typedef union value {
	char sc;
	short ss;
	int i;
	unsigned char uc;
	unsigned short us;
	unsigned  int u;
	float f;
	double d;
	void *p;
	int ifdiv;
}Value;

struct symbol {
	char *name;
	int size;
	int scope;
	Symbol up;
	Coordinate src;
	Type type;
	int sclass;
	int ifdiv;
	int offset;
	union {
		struct {
			Value v;
			Symbol loc;
		}c;
		struct {
			Type *proto;
		}f;
		struct {
			unsigned cfields : 1;
			unsigned vfields : 1;
			Field flist;//一串域名，用来表示struct
		}s;
		Symbol *idlist;//标志enum，指向一串symbol，u的域内是int value,结尾为null;
		int value;
		
	}u;
	unsigned addressed;
	unsigned generated:1;
	unsigned temporary:1;
	int defined;
	int ifconst;
};


enum { CONSTANT = 1, LABLES, GLOBAL, PARAM, LOCAL };
extern Table constants;
extern Table externals;
extern Table globals;
extern Table identifiers;
extern Table labels;
extern Table types;
extern int level;
//extern Type;
extern int roundNow ;
extern int roundMaxTimes ;
int stringNum ;
void enterscop( );

void exitscope( );
//创建标志符
Symbol install( char*name, Table*tpp, int level);
Table table( Table
	tp, int level );
//添加列表节点
//void buildNewVar( Table tp, int lev, Symbol s );
Symbol SymbolExist( Table tp, char*name );
//创建常量
Symbol constant( Type ty, Value  v);
Symbol intconst( int n );
Symbol doubleconst( double n );
int genlabel( int i );
Symbol genident( int scals, int lev, Type ty );
Symbol temporary( int scals, int lev, Type ty );
Symbol newtemp( int scals, int tc );
Symbol firstInit( char*name );
int hash( char*name, int  HASH_SHIFT, int HASH_SIZE );
Symbol lookup( const char *name, Table tp );

/**************************Types******************************/
//type
//type typedef

#define isqual(t) ((t)->op>=CONST)
#define unqual(t) (isqual(t)?(t)->type:(t))

#define isconst(t)   ((t)->op==CONST)
#define isarray(t)   ((t)->op==ARRAY)
#define isfunc(t)   ((t)->op==FUNCTION)
#define ischar(t)   ((t)->op==CHAR)
#define isint(t)   ((t)->op>=CHAR&&(t)->op<=UNSIGNED)
#define isfloat(t)   ((t)->op==FLOAT)
#define isdouble(t)   ((t)->op==DOUBLE)


extern Type chartype;
extern Type inttype;
extern Type floattype;
extern Type signedchartype;
extern Type unsignedchartype;
extern Type unsignedinttype;
extern Type voidtype;
extern Type voidptype;


struct field {
	char *name;
	Type type;
	int offset;
	short bitsize;
	short lsb;
	Field link;
};


struct type {
	int op;
	Type type;
	int size;
	int align;
	union {
		Symbol sym;
		//Type *functype;
		struct  {
			Type *proto;
			int funcSize;
			int args;
		}f;
	}u;
	Table tb;//记录当前的符号表，退出之后不会被丢弃
};
//类型表只有一个
static Type type( int op, Type ty, int size, void *sym );
Type arrayType( Type ty, int n );
void rmtype( int lev );
 void typeInit( );
Type PRT( Type TY );
Type func( Type ty, Type *proto );
int eqtype( Type ty1, Type ty2, int ret );
Type promote( Type ty );
char *vtoa( Type ty, Value v );
/******************************String**************************/
//string type

//string func


char* string( char* str );

char* stringd( int n );

char* stringn( char*str, int len );


Type btot( int tc );


/***********************gen***************************/
extern int assLine ;//打印汇编条数
extern int functionNumber;//函数个数：
extern int constantsNumber;//常量个数：
extern int identificaionOffset ;//域内变量偏移值：
extern int fieldNumber ;//作为跳转的标号
extern int temp;
extern int maxTemp ;
/*ast node*/
struct ast {
	union {
		char *idtype;
		int intgr;
		float dou;
		struct string *str;
		//struct ifo *i;
		Value u;
		Symbol sym; //符号即存取符号表入口
		Type ty;    //类型即存取类型		
	};//如果是数值 constant name 需要用到这个
	//储存变量的值 常数类型（前三项），变量类型（struct ifo*）
	char name[15];//存储节点名称
	Coordinate info; //存储节点位置
	//char op1[15];
	//char op2[15];
	//char op3[15];
	int offset;
	struct ast *l;
	struct ast *r; //是否还需要指向下一个结点的？
	int opPr; //存储节点功能
	int opType;//操作类型
	//左孩子右兄弟
	int type;//0不能进行赋值操作const 1可以进行赋值操作，2是保留字符，3是其他
};
typedef struct ast* Tree;
/**********************exp*****************************/
Tree exprCOMMA( Tree right );


Tree exprOPSingle( Tree oprand, Tree op );
Tree exprOPDouble( Tree oprand1, Tree oprand2, Tree op );
Tree getVarName( Tree name );
Tree getFuncName( Tree name, Tree explist );
Tree getArrayName( Tree name, Tree index );
Tree setConstants( Tree cons );

Value newValue( int type, Value oldValue, int oldType );
int transferAssignDecl( Tree type, Tree varList );
Tree varDec( Tree type, Tree vl, int ifConst );
Symbol findIfExist( Tree var, Tree type, int ifconst );
void okayToDec( Tree newsymbol, Type type, Tree value );
void setNewSymbol( Symbol newsym, Type type );
Tree funcDef( Tree type, Tree name, Tree args, int ifconst, Tree explist );
Tree changeToUnsigned( Tree oldType );


Tree createList( const char * name, Tree l, Tree r );
Tree createListL( const char * name, Tree l, Tree r );
Tree setArgs( Tree exp, Tree explist );
Tree funcVarDec( Tree name, Tree type, int ifconst );
Tree ifStatement( Tree state1, Tree exp, Tree state2 );
Tree breakState( Tree brk );
Tree Return( Tree ret );
struct ifo {
	// 变量的树结点信息
	char *name;
	int* varid;// 变量在表中的地址
	char *type;
	int size;
	int num;
};


/* 函数根节点表 */
struct funcList {
	int num;
	struct ast* func;
};


void yyerror( const char *s, ... );
/* 返回值是struct ast的构造新节点函数 */
Tree newast( const char*name, int num, ... );
/* 删除抽象语法树 */
void treefree( struct ast *a );
/* 遍历抽象语法树 */
double eval( struct ast *a );
/* 打印抽象语法树的信息 */
void eval_print( struct ast*a, int level );
/* 如何存储数组？type=int/float/char 从地址取值 */
//Tree findTheRight( const char*name, int op, int num, ... );

Tree newNode( const char*name, Tree l, Tree r, int oppr, int opty, int type );

 typedef struct labelStack {
	int label;
	struct labelStack*  last;
}*LabelStack;
 extern LabelStack countinueStack;
 extern LabelStack breakStack;
 int popStack( LabelStack oldStack );
 int getStack( LabelStack oldStack );
 void pushStack( int i, LabelStack oldStack );
 void initialStack( LabelStack Stack );
 void Initial( );
 struct mid* expGen( Tree expOp, int ifeax, struct mid* m );
 struct mid* opMidGen( Tree midOp, int ifeax, struct mid* m );
 struct mid {
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
 };
 struct midrest {
	 struct mid* func;
	 char*  funcName;
	 Type funcType;
	 struct midrest* next;
 };
 struct midall {
	 struct mid* main;//主函数不需要记录名称和类别，可以直接在tb中寻找
	 Type funcType;
	 struct midrest* midRest;
 };
 extern struct midall *midAll;
 int newStringList( char* newS );
 void initialStringList( );
 struct mid* midCurUpdate( char* funcName, Type funcType );

 struct stringlist {
	 char* a;
	 int i;
	 struct stringlist * next;
 };
 typedef struct stringlist *stringList;
 extern stringList constString;
 int getNumber( char* m );

 extern FILE *fpWrite;
 extern struct mid*cur;

 void generateData( FILE *fpWrite );
 void generateBss( FILE *fpWrite );
 void printfidentifiers( FILE *fpWrite, Table tbb, int level );
 void printfGlobal( FILE *fpWrite, Table tbb, int level );
 void generateAsm( );
 void printfString( FILE *fpWrite );
#endif