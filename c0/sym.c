#define sym_HASH_SHIFT 1
#define sym_HASH_SIZE 256
#include "c.h"
#define equalp(x)  v.x==p->sym.u.c.v.x

//typedef struct symbol *Symbol;
//typedef struct table *Table;

//extern Table constants;
//extern Table externals;
//extern Table globals;
//extern Table identifiers;
//extern Table labels;
//extern Table types;
//extern int level;
//extern Type;
//int level = GLOBAL;

//typedef struct coord {
//	char *file;
//	unsigned x, y;
//}Coordinate;
//enum{ CONSTANT = 1,LABLES,GLOBAL,PARAM,LOCAL };
//
//struct symbol {
//			char *name;
//			int size;
//			int scope;
//			Symbol up;
//			Coordinate src;
//			Type type;
//			union {
//					char* idtype;
//				int intgr;
//				double dou;
//			};
//};
//struct table {
//	int level;
//	struct entry {
//		struct entry*link;
//		struct symbol sym;
//	}*bucket[256];
//	Symbol all;
//	Table previous;
//};


struct table {
	int level;
	struct entry {
		struct entry*link;
		struct symbol sym;
	}*buckets[256];
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
Table globals = &ids;
Table types = &tys;
Table labels;
//初始化所有table的level
//<sys.c function>
void enterscop( ) {
	++level;
}

void exitscope( ) {
	rmtypes( level );
	if (types->level == level)
		types = types->previous;
	if (identifiers->level == level)
		identifiers = identifiers->previous;
	--level;
}

//创建标志符
Symbol install( char*name, Table*tpp, int level, int arena ) {
	Table tp = *tpp;
	struct entry *p;
	unsigned h = (unsigned)hash( name, 1, 256 );
	if (level > 0 && tp->level < level)
	{//如果不在同一层则需要新建立一系列表
		tp = *tpp = table( tp, level );
	}
	NEW0( p, arena );
	p->sym.name = name;
	p->sym.scope = level;
	p->sym.up = tp->all;
	tp->all = &p->sym;
	p->link = tp->buckets[h];
	tp->buckets[h] = p;
	return &p->sym;
}

Table table( Table tp, int level ) {
	Table new;
	NEW0( new, 1 );//给fun类型表分配的空间默认是第二块
	new->previous = tp;
	new->level = tp->level + 1;
	if (tp)new->all = tp->all;
	else new->all = NULL;
	return new;
}
//添加列表节点
//void buildNewVar( Table tp, int lev, Symbol s ) {
//	while (tp&&tp->level > lev) {
//		tp = tp->previous;
//		//找到symbol所属的level
//	}
//	int hashCode = hash( s->name );
//	if (tp&&tp->level == lev) {
//		Symbol p;
//		Coordinate sav;
//		//sav = s->src;
//		p = tp->all;
//		if (tp->bucket[hashCode]) {
//			while (p) {
//				if (p->name == s->name) {
//					error( "重复定义" );
//					exit( 1 );
//				}
//				p = p->up;
//			}
//		}
//		Table tpSameLevel = tp;
//		tp = tp->previous;
//		Symbol sCurLevel = tp->all;
//		//在当前这一层没有函数定义，如果在之前找到，需要从这一层已经定义的变量末尾用s->up连接
//		tp = tpSameLevel;
//		sCurLevel = tp;
//		s->up =
//			sCurLevel->up = s;
//		if (tp->bucket[hashCode] == NULL) {
//			tp->bucket[hashCode] = s;
//		}
//	}
//}
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
			case SHORT: if (equalp( ss )) return &p->sym;break;
			case INT: if (equalp( i )) return &p->sym;break;
			case UNSIGNED: if (equalp( u )) return &p->sym;break;
			case FLOAT: if (equalp( f )) return &p->sym;break;
			case DOUBLE: if (equalp( d )) return &p->sym;break;
			case ARRAY:
			case FUNCTION:
			case POINTER:if (equalp( p )) return &p->sym;break;			

			}
		}
	}
	NEW0( p, PERM );
	p->sym.name = vtoa( ty, v );
	p->sym.scope = CONSTANT;
	p->sym.type = ty;
	p->sym.sclass = STATIC;
	p->sym.u.c.v = v;
	p->sym.up = constants->buckets[h];
	p->link = constants->all;
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
	constant( inttype, v );
}
Symbol doubleconst( double n ) {
	Value v;
	v.d = n;
	constant( doubletype, v );
}

Symbol genlable( int i ) {
	static int label = 1;
	label += i;
	return label - i;

}

Symbol genident( int scals, int lev, Type ty ) {
	Symbol p;
	NEW0( p, lev >= LOCAL ? FUNC : PERM );
	p->name = stringd( genlable( 1 ) );
	p->scope = lev;
	//p->SCLASS = scls;
	p->type = ty;
	p->generated = 1;
	//if (lec=GLOBAL)
	//	(*IR->defsymbol)(p);
	return p;
}

Symbol temporary( int scals, int lev, Type ty ) {
	Symbol p = genident( scals, lev, ty );
	p->temporary = 1;
	return p;
}

Symbol newtemp( int scals, int tc ) {
	Symbol p = temporary( scals,LOCAL, btot(tc) );
	(*IR->local)(p);
	p->defined = 1;
	return p;
}

unsigned hash( char*name, unsigned  HASH_SHIFT, unsigned HASH_SIZE ) {
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
	unsigned h = (unsigned long)name&(sym_HASH_SIZE - 1);
	do
		for (p = tp->buckets[h]; p; p = p->link)
			if (name == p->sym.name)
				return &p->sym;
	while ((tp = tp->previous) != NULL);
	return NULL;
}

Symbol firstInit( char*name) {
	Symbol sym;
	sym->name = name;
	sym->defined = 0;
	sym->src.file = file;
	sym->src.x = lineno;
	return sym;
}
