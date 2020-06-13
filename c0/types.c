#include "c.h"

#define type_HASH_SIZE 128
//typedef struct type *Type;
static Symbol pointersym;
//struct type {
//	int op;
//	Type type;
//	int size;
//	int align;
//	union {
//		Symbol sym;
//		Type *functype;
//	}u;
//};
//extern Type chartype;
//extern Type inttype;
//extern Type shorttype;
//extern Type floattype;
//extern Type doubletype;
//extern Type longdoubletype;
//extern Type longinttype;
//extern Type signedchartype;
//extern Type unsignedchartype;
//extern Type unsignedinttype;
//extern Type unsignedshorttype;
//extern Type unsignedlongtype;
//extern Type voidtype;
//extern Type voidptype;
//

static struct entry {
	struct entry*link;
	struct type type;
}*typetable[128];

static int maxlevel;

void rmtype( int lev ) {
	if (maxlevel >= lev) {
		int i = 0;
		maxlevel = 0;
		for (;i <( typetable );i++) {
			struct entry *tn, **tq = &typetable[i];
			while (tn->type.op != NULL) {
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


static Type type( int op, int size, int align, Type ty, void *sym ) {
	unsigned h = (op ^ ((unsigned)ty) >> 3)&(type_HASH_SIZE - 1);
	struct entry *tm;
	if (op != FUNCTION && (op != ARRAY || size > 0)) {
		for (tm = typetable[h];tm;tm = tm->link) {
			if (tm->type.type == ty &&
				 tm->type.op == op &&
				 tm->type.align == align &&
				 tm->type.size == size &&
				 tm->type.u.sym == sym
				 )
				return &tm->type;
		}
	}
	tm->type.type = ty;
	tm->type.op = op;
	tm->type.align = align;
	tm->type.size = size;
	tm->type.u.sym = sym;
	tm->type.type = ty;
	//memset( &tm->type.x, 0, sizeof( tm->type.x ) );
	tm->link = typetable[h];
	typetable[h] = tm;
	return &tm->type;
}

void typeInit( ) {
#define mm(v,name,op,metrics) {Symbol p=install(string(name ),&types,GLOBAL,PERM );v=type(op,0,IR->metrics.size,IR->metrics.align,p);p->type=v;p->addressed=IR->metrics.outofline;}
	mm( chartype, "char", INT, charmetric );
	mm( inttype, "int", INT, intmetric );
	mm( floattype, "float", FLOAT, floatmetric );
	mm( doubletype, "double", FLOAT, doublemetric );
	mm( shorttype, "short", INT, shortmetric );
	mm( longinttype, "long int", INT, longmetric );
	//mm( longdoubletype, "long double", FLOAT, doublemetric );
	mm( unsignedchartype, "unsigned char", INT, charmetric );
	mm( signedchartype, "signed char", INT, charmetric );
	mm( unsignedinttype, "unsigned int", UNSIGNED, intmetric );
	mm( unsignedshorttype, "unsigned short", UNSIGNED, shortmetric );
	mm( unsignedlongtype, "unsigned long", UNSIGNED, longmetric );
	
#undef mm	

	Symbol p;
	p = install( string( "void" ), &types, GLOBAL, PERM );
	voidtype = type( VOID, NULL, 0, 0, p );
	p->type = voidtype;

	pointersym= install( string( "T*" ), &types, GLOBAL, PERM );
	pointersym->addressed = IR->ptrmetric.outofline;
}

Type PRT( Type TY ) {
	return type( POINTER, TY, IR->ptrmetric.size, IR->ptrmetric.align, pointersym );
}

Type deref( Type ty ) {
	if (isptr( ty ))
		ty = ty->type;
	else
		error( "type error: %s\n", "pointer expected" );
	return isenum( ty ) ? unqual( ty )->type : ty;
}
Type array( Type ty, int n, int a ) {
	assert( ty );
	if (isfunc( ty )) {
		error( "illegal type `array of %t'\n", ty );
		return array( inttype, n, 0 );
	}
	if (isarray( ty ) && ty->size == 0)
		error( "missing array size\n" );
	if (ty->size == 0) {
		if (unqual( ty ) == voidtype)
			error( "illegal type `array of %t'\n", ty );
		/*else if (Aflag >= 2)
			warning( "declaring type array of %t' is undefined\n", ty );
*/
	}
	else if (n > INT_MAX / ty->size) {
		error( "size of `array of %t' exceeds %d bytes\n",
			   ty, INT_MAX );
		n = 1;
	}
	return type( ARRAY, ty, n*ty->size,
				 a ? a : ty->align, NULL );
}

Type atop( Type ty ) {
	if (isarray( ty ))
		return ptr( ty->type );
	error( "type error: %s\n", "array expected" );
	return ptr( ty );
}
Type qual( int op, Type ty ) {
	if (isarray( ty ))
		ty = type( ARRAY, qual( op, ty->type ), ty->size,
				   ty->align, NULL );
	else if (isfunc( ty ))
		warning( "qualified function type ignored\n" );
	else if (isconst( ty ) && op == CONST
			  || isvolatile( ty ) && op == VOLATILE)
		error( "illegal type `%k %t'\n", op, ty );
	else {
		if (isqual( ty )) {
			op += ty->op;
			ty = ty->type;
		}
		ty = type( op, ty, ty->size, ty->align, NULL );
	}
	return ty;
}
Type func( Type ty, Type *proto ) {
	if (ty && (isarray( ty ) || isfunc( ty )))
		error( "illegal return type `%t'\n", ty );
	ty = type( FUNCTION, ty, 0, 0, NULL );
	ty->u.f.proto = proto;
	//ty->u.f.oldstyle = style;
	return ty;
}

Type freturn( Type ty ) {
	if (isfunc( ty ))
		return ty->type;
	error( "type error: %s\n", "function expected" );
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

//�ṹ��ö��
//ͨ�����ʶ��u.sym���б�����ű���ڣ�symbol�ṹ�������u.s
Type newstruct( int op, char*tag ) {
	Symbol p;
	if (*tag == 0) {
		tag = stringd( genlable( 1 ) );
	}
	else {
		if(p=lookup(tag,types)!=NULL&&(p->scope==level||p->scope==PARAM&&level==PARAM+1)) {
			if (p->type->op == op && !p->defined)
				return p->type;
			error( "redefinition of `%s' previously defined at %w\n",
				   p->name, &p->src );
		}
		p = install( tag, &types, level, PERM );
		p->type = type( op, NULL, 0, 0, p );
		if (p->scope > maxlevel)
			maxlevel = p->scope;
		p->src = src;
		return p->type;
	}
}
Field newfield( char *name, Type ty, Type fty ) {
	Field p, *q = &ty->u.sym->u.s.flist;

	if (name == NULL)
		name = stringd( genlabel( 1 ) );
	for (p = *q; p; q = &p->link, p = *q)
		if (p->name == name)
			error( "duplicate field name `%s' in `%t'\n",
				   name, ty );
	NEW0( p, PERM );
	*q = p;
	p->name = name;
	p->type = fty;
	return p;
}


int eqtype( Type ty1, Type ty2, int ret ) {
	if (ty1 == ty2)
		return 1;
	if (ty1->op != ty2->op)
		return 0;//��������Ƿ���ܼ���
	switch (ty1->op) {
	case ENUM: case UNION: case STRUCT:
	case UNSIGNED: case INT: case FLOAT:
		return 0;
	case POINTER:  return eqtype( ty1->type, ty2->type, 1 );
	case VOLATILE: case CONST + VOLATILE:
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
				if (promote( ty ) != (isenum( ty ) ? ty->type : ty))
					return 0;
			}
			return 1;
		}
	}
				   return 0;
	}
	assert( 0 ); return 0;
}


Type promote( Type ty ) {
	ty = unqual( ty );
	switch (ty->op) {
	case ENUM:
		return inttype;
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
	case FLOAT:
		if (ty->size < doubletype->size)
			return doubletype;
	}
	return ty;
}
//��������Ƿ����
Type compose( Type ty1, Type ty2 ) {
	if (ty1 == ty2)
		return ty1;
	assert( ty1->op == ty2->op );
	switch (ty1->op) {
	case POINTER:
		return ptr( compose( ty1->type, ty2->type ) );
	case CONST + VOLATILE:
		return qual( CONST, qual( VOLATILE,
					 compose( ty1->type, ty2->type ) ) );
	case CONST: case VOLATILE:
		return qual( ty1->op, compose( ty1->type, ty2->type ) );
	case ARRAY: { Type ty = compose( ty1->type, ty2->type );
		if (ty1->size && (ty1->type->size && ty2->size == 0 || ty1->size == ty2->size))
			return array( ty, ty1->size / ty1->type->size, ty1->align );
		if (ty2->size && ty2->type->size && ty1->size == 0)
			return array( ty, ty2->size / ty2->type->size, ty2->align );
		return array( ty, 0, 0 );    }
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
		assert( *p1 == NULL && *p2 == NULL );
		return func( ty, ltov( &tlist, PERM ), 0 ); }
	}
	assert( 0 ); return NULL;
}
//������ӳ��Ϊ��Ӧ�����ͺ�׺
//
int ttob( Type ty ) {
	switch (ty->op) {
	case CONST: case VOLATILE: case CONST + VOLATILE:
		return ttob( ty->type );
	case VOID: case INT: case UNSIGNED: case FLOAT:
		return ty->op + sizeop( ty->size );
	case POINTER:
		return POINTER + sizeop( voidptype->size );
	case FUNCTION:
		return POINTER + sizeop( funcptype->size );
	case ARRAY: case STRUCT: case UNION:
		return STRUCT;
	case ENUM:
		return INT + sizeop( inttype->size );
	}
	assert( 0 ); return INT;
}
//�����ͺ�׺ӳ��Ϊ��Ӧ������
Type btot( int op, int size ) {
#define xx(ty) if (size == (ty)->size) return ty;
	switch (optype( op )) {
	case F:
		xx( floattype );
		xx( doubletype );
		xx( longdoubletype );
		assert( 0 ); return 0;
	case I:
		if (chartype->op == INT)
			xx( chartype );
		xx( signedchartype );
		xx( shorttype );
		xx( inttype );
		xx( longinttype );
		//xx( longlong );
		assert( 0 ); return 0;
	case U:
		if (chartype->op == UNSIGNED)
			xx( chartype );
		xx( unsignedchartype );
		xx( unsignedshorttype );
		xx( unsignedinttype );
		xx( unsignedlongtype );
		//xx( unsignedlonglong );
		assert( 0 ); return 0;
	case P:
		xx( voidptype );
		xx( funcptype );
		assert( 0 ); return 0;
	}
#undef xx
	assert( 0 ); return 0;
}
//
//int hasproto( Type ty ) {
//	if (ty == 0)
//		return 1;
//	switch (ty->op) {
//	case CONST: case VOLATILE: case CONST + VOLATILE: case POINTER:
//	case ARRAY:
//		return hasproto( ty->type );
//	case FUNCTION:
//		return hasproto( ty->type ) && ty->u.f.proto;
//	case STRUCT: case UNION:
//	case VOID:   case FLOAT: case ENUM:  case INT: case UNSIGNED:
//		return 1;
//	}
//	assert( 0 ); return 0;
//}
///* fieldlist - construct a flat list of fields in type ty */
//Field fieldlist( Type ty ) {
//	return ty->u.sym->u.s.flist;
//}
