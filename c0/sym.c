#define sym_HASH_SHIFT 1
#define sym_HASH_SIZE 32
#include "c.h"
#define equalp(x)  v.x==p->sym.u.c.v.x

struct table {
	int level;
	struct entry {
		struct entry*link;
		struct symbol sym;
	}*buckets[32];
	Symbol all;
	Table previous;
};

static struct table
cns = { CONSTANT },
ext = { GLOBAL },
ids = { GLOBAL },
tys = { GLOBAL };
Table constants = &cns;
Table externals = &ext;
Table identifiers = &ids;
//Table globals = &ids;
Table types = &tys;
Table labels;
//初始化所有table的level
//<sys.c function>



void enterscop( ) {
	++level;
}

void exitscope( ) {
	rmtype( level );
	if (types->level == level)
		types = types->previous;
	if (identifiers->level == level)
		identifiers = identifiers->previous;
	--level;
}

//创建标志符
Symbol install( char*name, Table*tpp, int level ) {
	Table tp = *tpp;
	struct entry*p = (struct entry*)malloc( sizeof( struct entry ) );;
	unsigned h = (unsigned)hash( name, sym_HASH_SHIFT, sym_HASH_SIZE );
	if (level > 0 && tp->level < level)
	{//如果不在同一层则需要新建立一系列表
		tp = *tpp = table( tp, level );
	}
	//p = (struct entry*)malloc( sizeof( struct entry ) );
	p->sym.name = name;
	p->sym.scope = level;
	p->sym.up = tp->all;
	tp->all = &p->sym;
	p->link = tp->buckets[h];
	tp->buckets[h] = p;
	return &p->sym;
}
//void initTable( )
Table table( Table tp, int level ) {
	Table newTb;
	newTb = (Table)malloc( sizeof( struct table ) );//给fun类型表分配的空间默认是第二块
	int i = 0;
	for( i = 0;i < sym_HASH_SIZE;i++ ){
		newTb->buckets[i] = NULL;
	}
	newTb->previous = tp;
	newTb->level = tp->level + 1;
	if (tp)newTb->all = tp->all;
	else newTb->all = NULL;
	return newTb;
}

Symbol SymbolExist( Table tp, char*name ){
	struct entry* p;
	
	int index = 0;
	index = hash( name, sym_HASH_SHIFT, sym_HASH_SIZE );
	p = tp->buckets[index];
	while (p!= NULL) {		
		if (p->sym.name==name) {
			//string 保证此时读入的name如果出现过，使用的是同一个地址
			return &p->sym;
		}
		p = p->link;
	}
	return NULL;
}

Symbol constant( Type ty, Value v )
{
	struct entry *p;
	unsigned int h = v.u&(sym_HASH_SIZE - 1);
	ty = unqual( ty );
	for (p = constants->buckets[h];p;p = p->link) {
		if (eqtype( ty, p->sym.type, 1 )) {
			switch (ty->op) {
			case CHAR: if (equalp( sc )) return &p->sym;break;		
			case INT: if (equalp( i )) return &p->sym;break;
			case UNSIGNED: if (equalp( u )) return &p->sym;break;
			case ARRAY:
			case FUNCTION:
			case POINTER:if (equalp( p )) return &p->sym;break;			

			}
		}
	}
	p = (struct entry*)malloc( sizeof( struct entry ) );
	p->sym.name = vtoa( ty, v );
	p->sym.scope = CONSTANT;
	p->sym.type = ty;
	p->sym.u.c.v = v;
	p->link = constants->buckets[h];
	p->sym.up = constants->all;
	constants->all = &p->sym;
	constants->buckets[h] = p;
	//if (ty->u.sym && !ty->u.sym->addressed)
	//	(*IR->defsymbol)(&p->sym);
	//p->sym.defined = 1;
	return &p->sym;
}

Symbol intconst( int n ) {
	Value v;
	v.i = n;
	return constant( inttype, v );
}

Symbol allsymbols( Table tp ) {
	return tp->all;
}
int genlabel( int i ) {
	//static int label = 1;
	label += i;
	return label - i;
}


Symbol temporary( int scals, int lev, Type ty ) {
	Symbol p = genident( scals, lev, ty );
	p->temporary = 1;
	return p;
}



int hash( char*name, int  HASH_SHIFT, int HASH_SIZE ) {
	unsigned temp = 0;
	unsigned i = 0;
	while (name[i] != '\0')
	{
		temp = ((temp << HASH_SHIFT) + name[i]) % HASH_SIZE;
		++i;
	}
	return temp;
}

Symbol lookup( const char *name, Table tp ) {
	struct entry *p;
	unsigned h = (unsigned)hash( name, sym_HASH_SHIFT, sym_HASH_SIZE );
	do
		for (p = tp->buckets[h]; p; p = p->link)
			if (strcmp(name , p->sym.name)==0)
				return &(p->sym);
	while ((tp = tp->previous) != NULL);
	return NULL;
}

Symbol firstInit( char*name) {
	Symbol sym=(Symbol)malloc(sizeof(struct symbol));
	sym->name = name;
	sym->defined = 0;
	
	sym->src.x = yylineno;
	return sym;
}
char *vtoa( Type ty, Value v ) {
	char buf[50];

	ty = unqual( ty );
	switch (ty->op) {
	case INT:      return stringd( v.i );/*
	case UNSIGNED: return stringf( (v.u&~0x7FFF) ? "0x%X" : "%U", v.u );
	case FLOAT:    return stringf( "%g", (double)v.d );
	case ARRAY:
		if (ty->type == chartype 
			 || ty->type == unsignedchartype)
			return v.p;
		return stringf( "%p", v.p );
	case POINTER:  return stringf( "%p", v.p );
	//case FUNCTION: return stringf( "%p", v.g );*/
	}
	 return NULL;
}
Symbol genident( int scls, Type ty, int lev ) {
	Symbol p;
	p = (Symbol)malloc( sizeof( struct symbol ) );
	p->name = stringd( genlabel( 1 ) );
	p->scope = lev;
	p->sclass = scls;
	p->type = ty;
	p->generated = 1;

	return p;
}
void subprintfArrayValue( FILE *fpWrite, int op, struct entry* p ) {
	 fprintf( fpWrite, "    %s", p->sym.name );
}
void subprintfValue( FILE *fpWrite, int op, struct entry* p ) {
	switch (op) {
	case CHAR: fprintf( fpWrite, "db /'%c/'/n", p->sym.u.c.v.sc );break;
	case UNSIGNEDCHAR:
		fprintf( fpWrite, "db %x/n", p->sym.u.c.v.uc );break;
	case INT: fprintf( fpWrite, "dd %x/n", p->sym.u.c.v.i );break;
	case UNSIGNED: fprintf( fpWrite, "dd %x/n", p->sym.u.c.v.u );break;
	//case ARRAY:  subprintfConstantValue( fpWrite, op,  p )
	}
}

void subConstantPrintf( FILE *fpWrite ,int op,struct entry* p) {
	if(p->sym.defined){
		fprintf( fpWrite, "    %s", p->sym.name );
		subprintfValue( fpWrite, op, p );
	}
}
void subIdentifiersPrintf( FILE *fpWrite, int op, struct entry* p ) {
	if (p->sym.defined==0) {
		fprintf( fpWrite, "    ?%s", p->sym.name );
		switch (op) {
		case UNSIGNEDCHAR:
		case CHAR: fprintf( fpWrite, "resb 1/n");break;
		
		case INT: 
		case UNSIGNED: fprintf( fpWrite, "resd 1/n" );break;

		case ARRAY:switch (p->sym.type->op) {
			case UNSIGNEDCHAR:
			case CHAR: fprintf( fpWrite, "resb %d/n", p->sym.type->size );break;

			case INT:
			case UNSIGNED: fprintf( fpWrite, "resd %d/n", p->sym.type->size/4);break;

			//case ARRAY:  subprintfConstantValue( fpWrite, op,  p )
		}
			//case ARRAY:  subprintfConstantValue( fpWrite, op,  p )
		}
	}
}

void printfGlobal( FILE *fpWrite,Table tbb ,int level) {
	Symbol p=allsymbols( tbb );
	//struct entry *p;
	while (p) {
		//数组
		//name times n 初始值 我秃了，数组咋搞
		//name 
		//dd 1h
		//dd 2h
		//dd 3h
		//......
		//非数组
		//name db/dw/dd 值
		int op = p->type->op;
		subConstantPrintf( fpWrite, op, p );
		p = p->up;
	}

}
void printfidentifiers( FILE *fpWrite, Table tbb, int level ) {
	Symbol p = allsymbols( tbb );
	//struct entry *p;
	while (p) {
		int op = p->type->op;
		subIdentifiersPrintf( fpWrite, op, p );
		p = p->up;
	}

}