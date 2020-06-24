#include "c.h"

#define type_HASH_SIZE 32
//typedef struct type *Type;
static Symbol pointersym;
Type chartype;
Type inttype;
Type floattype;
Type signedchartype;
Type unsignedchartype;
Type unsignedinttype;
Type voidtype;
Type voidptype;
static struct entry {
	struct entry*link;
	struct type type;
}*typetable[32];

static int maxlevel;

void rmtype( int lev ) {
	if (maxlevel >= lev) {
		int i = 0;
		maxlevel = 0;
		for (;i <(type_HASH_SIZE);i++) {
			struct entry *tn, **tq = &typetable[i];
			while ( (tn=*tq) != NULL) {
				if (tn->type.op == FUNCTION) {
					tq = &tn->link;
				}
				else if (tn->type.u.sym&&tn->type.u.sym->scope >= lev)
					*tq = tn->link;
				else {
					if (tn->type.u.sym&&tn->type.u.sym->scope >= maxlevel)
						maxlevel = tn->type.u.sym->scope;
					tq = &tn->link;
				}
			}

		}
	}
}


static Type type( int op, Type ty,int size,void *sym ) {
	unsigned h = (op ^ ((unsigned)ty) >> 3)&(type_HASH_SIZE - 1);
	struct entry *tm;
	if (op != FUNCTION && (op != ARRAY || size > 0)) {
		for (tm = typetable[h];tm;tm = tm->link) {
			if (tm->type.type == ty &&
				 tm->type.op == op &&
				 tm->type.size == size &&
				 tm->type.u.sym == sym
				 )
				return &tm->type;
		}
	}
	tm = (Type)malloc( sizeof( struct type ) );
	tm->type.type = ty;
	tm->type.op = op;
	tm->type.size = size;
	tm->type.u.sym = sym;
	//memset( &tm->type.x, 0, sizeof( tm->type.x ) );
	tm->link = typetable[h];
	
	typetable[h] = tm;
	return &tm->type;
}

void typeInit( ) {
#define mm(v,name,op,size) {Symbol p=install(string(name ),&types,GLOBAL);v=type(op,0,size,p);p->type=v;}
	mm( chartype, "char", CHAR, 1 );
	mm( inttype, "int", INT, 4 );
	mm( floattype, "float", FLOAT, 4 );
	mm( unsignedchartype, "unsigned char", UNSIGNEDCHAR, 1 );
	mm( unsignedinttype, "unsigned int", UNSIGNED, 4 );
	
#undef mm	

	Symbol p;
	p = install( string( "void" ), &types, GLOBAL);
	voidtype = type( VOID, NULL, 4,  p );
	p->type = voidtype;

	pointersym= install( string( "T*" ), &types, GLOBAL );
	
}

Type PRT( Type TY ) {
	return type( POINTER, TY,4,pointersym );
}


Type arrayType( Type ty, int n ) {
	//assert( ty );
	if (isfunc( ty )) {
		
		yyerror( "illegal type `array" );
		return arrayType( inttype, n );
	}
	if (isarray( ty ) && ty->size == 0)
		yyerror( "missing array size\n" );
	if (ty->size == 0) {}
	//	if (unqual( ty ) == voidtype)
			//error( "illegal type `array of %t'\n", ty );
		/*else if (Aflag >= 2)
			warning( "declaring type array of %t' is undefined\n", ty );
*/
	
	else if (n > INT_MAX / ty->size) {
		
		yyerror( "out\n" );
		n = 1;
	}
	return type( ARRAY, ty, n*ty->size,
				  NULL );
}



Type qual( int op, Type ty ) {
	if (isarray( ty ))
		ty = type( ARRAY, qual( op, ty->type ), ty->size,
				    NULL );
	else if (isfunc( ty ))
		yyerror( "qualified function type ignored\n" );
	else if (isconst( ty ) && op == CONST
			 )
		printf( "illegal type `%k %t'\n", op, ty );
	else {
		if (isqual( ty )) {
			op += ty->op;
			ty = ty->type;
		}
		ty = type( op, ty, ty->size, NULL );
	}
	return ty;
}
Type func( Type ty, Type *proto ) {
	if ( (isarray( ty ) || isfunc( ty )))
		printf( "illegal return type `%t'\n", ty );
	ty = type( FUNCTION, ty,ty->size, NULL );
	ty->tb = identifiers;
	ty->u.f.proto = proto;
	//ty->u.f.oldstyle = style;
	return ty;
}

Type freturn( Type ty ) {
	if (isfunc( ty ))
		return ty->type;
	yyerror( "type error:function expected\n" );
	return inttype;
}
int variadic( Type ty ) {
	if (isfunc( ty ) && ty->u.f.proto) {
		int i;
		for (i = 0; ty->u.f.proto[i]; i++)
			;
		return i > 1 && ty->u.f.proto[i - 1] == voidtype;
	}
	return 0;
}

//结构和枚举
//通过标记识别，u.sym域中保存符号表入口；symbol结构相关域是u.s



int eqtype( Type ty1, Type ty2, int ret ) {
	if (ty1 == ty2)
		return 1;
	if (ty1->op != ty2->op)
		return 0;//检查两类是否可能兼容
	switch (ty1->op) {
	
	case UNSIGNED: case INT: case FLOAT:
		return 0;
	case POINTER:  return eqtype( ty1->type, ty2->type, 1 );
	
	case CONST:    return eqtype( ty1->type, ty2->type, 1 );
	case ARRAY:    if (eqtype( ty1->type, ty2->type, 1 )) {
		if (ty1->size == ty2->size)
			return 1;
		if (ty1->size == 0 || ty2->size == 0)
			return ret;
	}
				   return 0;
	case FUNCTION: if (eqtype( ty1->type, ty2->type, 1 )) {
		Type *p1 = ty1->u.f.proto, *p2 = ty2->u.f.proto;
		if (p1 == p2)
			return 1;
		if (p1 && p2) {
			for (; *p1 && *p2; p1++, p2++)
				if (eqtype( unqual( *p1 ), unqual( *p2 ), 1 ) == 0)
					return 0;
			if (*p1 == NULL && *p2 == NULL)
				return 1;
		}
		else {
			if (variadic( p1 ? ty1 : ty2 ))
				return 0;
			if (p1 == NULL)
				p1 = p2;
			for (; *p1; p1++) {
				Type ty = unqual( *p1 );
				//if (promote( ty ) != (isenum( ty ) ? ty->type : ty))
					return 0;
			}
			return 1;
		}
	}
				   return 0;
	}
	return 0;
}


Type promote( Type ty ) {
	ty = unqual( ty );
	switch (ty->op) {
	case INT:
		if (ty->size < inttype->size)
			return inttype;
		break;
	case UNSIGNED:
		if (ty->size < inttype->size)
			return inttype;
		if (ty->size < unsignedinttype->size)
			return unsignedinttype;
		break;
	}
	return ty;
}
/*
Type canOperate( Type ty1, Type ty2 ) {//判断ty2是否可以转换为ty1
	if (ty1 == ty2)
		return ty1;

	switch (ty1->op) {
	case POINTER:
		return compose( ty1->type, ty2->type );
	case ARRAY: { Type ty = compose( ty1->type, ty2->type );
		if (ty1->size && (ty1->type->size && ty2->size == 0 || ty1->size == ty2->size))
			return arrayType( ty, ty1->size / ty1->type->size, 1 );
		if (ty2->size && ty2->type->size && ty1->size == 0)
			return arrayType( ty, ty2->size / ty2->type->size, 1);
		return arrayType( ty, 0, 0 );    }
	case FUNCTION: { Type *p1 = ty1->u.f.proto, *p2 = ty2->u.f.proto;
		Type ty = compose( ty1->type, ty2->type );
		List tlist = NULL;
		if (p1 == NULL && p2 == NULL)
			return func( ty, NULL, 1 );
		if (p1 && p2 == NULL)
			return func( ty, p1 );
		if (p2 && p1 == NULL)
			return func( ty, p2 );
		for (; *p1 && *p2; p1++, p2++) {
			Type ty = compose( unqual( *p1 ), unqual( *p2 ) );
			if (isconst( *p1 ) || isconst( *p2 ))
				ty = qual( CONST, ty );
			if (isvolatile( *p1 ) || isvolatile( *p2 ))
				ty = qual( VOLATILE, ty );
			tlist = append( ty, tlist );
		}
		//assert( *p1 == NULL && *p2 == NULL );
		return func( ty, ltov( &tlist, PERM ), 0 ); }
	}
	//assert( 0 ); 
	return NULL;
}
//检查类型是否兼容
Type compose( Type ty1, Type ty2 ) {
	if (ty1 == ty2)
		return ty1;
	assert( ty1->op == ty2->op );
	switch (ty1->op) {
	case POINTER:
		return ptr( compose( ty1->type, ty2->type ) );
	case CONST: 
		return qual( ty1->op, compose( ty1->type, ty2->type ) );
	case ARRAY: { Type ty = compose( ty1->type, ty2->type );
		if (ty1->size && (ty1->type->size && ty2->size == 0 || ty1->size == ty2->size))
			return arrayType( ty, ty1->size / ty1->type->size);
		if (ty2->size && ty2->type->size && ty1->size == 0)
			return arrayType( ty, ty2->size / ty2->type->size );
		return arrayType( ty, 0, 0 );    }
	case FUNCTION: { Type *p1 = ty1->u.f.proto, *p2 = ty2->u.f.proto;
		Type ty = compose( ty1->type, ty2->type );
		List tlist = NULL;
		if (p1 == NULL && p2 == NULL)
			return func( ty, NULL, 1 );
		if (p1 && p2 == NULL)
			return func( ty, p1);
		if (p2 && p1 == NULL)
			return func( ty, p2);
		for (; *p1 && *p2; p1++, p2++) {
			Type ty = compose( unqual( *p1 ), unqual( *p2 ) );
			if (isconst( *p1 ) || isconst( *p2 ))
				ty = qual( CONST, ty );
			if (isvolatile( *p1 ) || isvolatile( *p2 ))
				ty = qual( VOLATILE, ty );
			tlist = append( ty, tlist );
		}
		//assert( *p1 == NULL && *p2 == NULL );
		return func( ty, ltov( &tlist, PERM ), 0 ); }
	}
	//assert( 0 ); 
	return NULL;
}
//将类型映射为相应的类型后缀
*/