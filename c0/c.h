#pragma once
//#include "config.h"
/*c.h定义了编译器的全局结构和部分全局函数*/
#ifdef __STDC__
#define ARGS(list) list
#else
#define ARGS(list) ()
#endif
/*如果定义了__STDC__就需要把完整的ansi参数类型作为参数生成类型列表*/

//extern void outs( char* );
#define NULL ((void*)0)
#define NEMLEMS(a) ((int)(sizeof(a))/sizeof((a)[0]))
#define roundup(x,n) (((x)+((n)-1))&(~((n)-1)))

#define sizeop(n) ((n)<<10)
//op由操作数类型（后四位）+操作动作编号（倒数5位之后）组成 如ADDI:ADD<<4+I ADD与I都实现定义
#define generic(op) ((op)&~15)
#define optype(op) ((op)&15)
#define opindex(op) ((op)>>4)
//#include "alloc.c"
//#include "sym.c"
//#include "types.c"
//#include "list.c"
//#include "string.c"
#include "limits.h"
enum { PERM = 0, FUNC, STMT };
enum {
	CHAR = 1, UNSIGNEDCHAR,INT,UNSIGNED, FLOAT,
	ARRAY, FUNCTION, POINTER, VOID, 
	STRUCT, UNION, ENUM ,FUNCTION, CONST,
	SHORT, LONG, VOLATILE, DOUBLE
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

enum { AUT0 = 1, REGISTER, STATIC, EXTERN };

enum {
	AND = 38 << 4,
	NOT = 39 << 4,
	OR = 40 << 4,
	COND = 41 << 4,
	RIGHT = 42 << 4,
	FIELD = 43 << 4
};

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

extern unsigned char *cp;
extern unsigned char *limit;
extern char *firstfile;
extern char *file;
extern char *line;
extern int lineno;
extern int t;
extern char *token;
extern Symbol tsym;
extern Coordinate src;
/*************************list*********************************/
typedef struct list *List;
struct list {
	void *x;
	List link;
};
//***********************global********************************/
typedef struct node *Node;
struct node {
	short op;
	short count;
	Symbol syms[3];
	Node kids[2];
	Node link;
	//Xnode x; //后端存放相应的各个节点数据
};
enum {
	F = FLOAT,
	I = INT,
	U = UNSIGNED,
	P = POINTER,
	V = VOID,
	B = STRUCT
};

//**********************alloc*****************************///
//alloc data

struct block {
	struct block *next;
	char *limit;
	char *avail;
	//可分配空间的首地址
};
union align {
	long l;
	char *p;
	double d;
	int( *f ) ARGS( (void) );
};
union header {
	struct block b;
	union align a;
};

static struct block
first[] = { {NULL},{NULL},{NULL} },
*arena[] = { &first[0],&first[1] ,&first[2] };

static struct block *freeblocks;//static 会自动初始化,此时的freeblock已经有地址有内容了
void* allocate( unsigned long n, unsigned a );

void* newarray( unsigned long m, unsigned long n, unsigned a );

void deallocate( unsigned a );

/***********************symbol*****************************/


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
	unsigned defined;
};

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

enum { CONSTANT = 1, LABLES, GLOBAL, PARAM, LOCAL };
extern Table constants;
extern Table externals;
extern Table globals;
extern Table identifiers;
extern Table labels;
extern Table types;
extern int level;
//extern Type;
level = GLOBAL;

void enterscop( );

void exitscope( );
//创建标志符
Symbol install( char*name, Table*tpp, int level, int arena );
Table table( Table tp, int level );
//添加列表节点
//void buildNewVar( Table tp, int lev, Symbol s );
Symbol SymbolExist( Table tp, char*name );
//创建常量
Symbol constant( Type ty, Value  v);
Symbol intconst( int n );
Symbol doubleconst( double n );
Symbol genlable( int i );
Symbol genident( int scals, int lev, Type ty );
Symbol temporary( int scals, int lev, Type ty );
Symbol newtemp( int scals, int tc );
Symbol firstInit( char*name );
unsigned hash( char*name, unsigned  HASH_SHIFT, unsigned HASH_SIZE );
Symbol lookup( const char *name, Table tp );

/**************************Types******************************/
//type
//type typedef

#define isqual(t) ((t)->op>=CONST)
#define unqual(t) (isqual(t)?(t)->type:(t))

#define isvolatile(t) ((t)->op==VOLATILE\
						||(t)->op==VOLATILE+CONST)
#define isconst(t)   ((t)->op==CONST\
						||(t)->op==VOLATILE+CONST)
#define isarray(t)   ((t)->op==ARRAY)
#define isstruct(t)   ((t)->op==STRUCT)
#define isunion(t)   ((t)->op==UNION)
#define isfunc(t)   ((t)->op==FUNCTION)
#define ischar(t)   ((t)->op==CHAR)
#define isint(t)   ((t)->op>=CHAR&&(t)->op<=UNSIGNED)
#define isfloat(t)   ((t)->op==FLOAT)
#define isdouble(t)   ((t)->op==DOUBLE)
#define isenum(t)   ((t)->op==ENUM)

extern Type chartype;
extern Type inttype;
extern Type shorttype;
extern Type floattype;
extern Type doubletype;
extern Type longdoubletype;
extern Type longinttype;
extern Type signedchartype;
extern Type unsignedchartype;
extern Type unsignedinttype;
extern Type unsignedshorttype;
extern Type unsignedlongtype;
extern Type voidtype;
extern Type voidptype;
extern Type funcptype;

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
			int size;
		}f;
	}u;
};
//类型表只有一个
static Type type( int op, Type ty, int size, void *sym );
Type arrayType( Type ty, int n );
/******************************String**************************/
//string type

//string func

static struct string {
	char *str;
	int len;
	struct string *link;
}*buckets[1024];

char* string( char* str );

char* stringd( int n );

char* stringn( char*str, int len );


Type btot( int tc );

/*************************interface******************************/
typedef struct metrics {
	unsigned char size, align, outofline;
} Metrics;
typedef struct interface {
	Metrics charmetric;
	Metrics shortmetric;
	Metrics intmetric;
	Metrics longmetric;
	Metrics floatmetric;
	Metrics doublemetric;
	Metrics ptrmetric;
	Metrics structmetric;
	unsigned little_endian : 1;//小端
	unsigned mulops_calls : 1;
	unsigned wants_callb : 1;
	unsigned wants_argb : 1;
	unsigned left_to_right : 1;
	unsigned wants_dag : 1;
	unsigned unsigned_char : 1;
	void( *address )(Symbol p, Symbol q, long n);
	//void( *blockbeg )(Env *);
	//void( *blockend )(Env *);
	void( *defaddress )(Symbol);
	void( *defconst )  (int suffix, int size, Value v);
	void( *defstring )(int n, char *s);
	void( *defsymbol )(Symbol);
	void( *emit )    (Node);
	void( *export )(Symbol);
	void( *function )(Symbol, Symbol[], Symbol[], int);
	Node( *gen )     (Node);
	void( *global )(Symbol);
	void( *import )(Symbol);
	void( *local )(Symbol);
	void( *progbeg )(int argc, char *argv[]);
	void( *progend )(void);
	void( *segment )(int);
	void( *space )(int);
	/*
	void( *stabblock )(int, int, Symbol*);
	void( *stabend )  (Coordinate *, Symbol, Coordinate **, Symbol *, Symbol *);
	void( *stabfend ) (Symbol, int);
	void( *stabinit ) (char *, int, char *[]);
	void( *stabline ) (Coordinate *);
	void( *stabsym )  (Symbol);
	void( *stabtype ) (Symbol);*/
	//Xinterface x;
} Interface;
typedef struct binding {
	char *name;
	Interface *ir;
} Binding;

extern Binding bindings[];
extern Interface *IR;

/**********************exp*****************************/
Tree exprCOMMA( Tree right );

/***********************gen***************************/
extern int assLine = 0;//打印汇编条数
extern int functionNumber = 0;//函数个数：
extern int constantsNumber = 0;//常量个数：
extern int identificaionOffset = 0;//域内变量偏移值：


Value newValue( int type, Value oldValue, int oldType );
Tree varDec( Tree type, Tree vl, int ifConst );
void okayToDec( Tree newsymbol, Tree type, Tree value );
void setNewSymbol( Symbol newsym, Type type );