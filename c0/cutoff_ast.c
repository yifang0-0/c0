//变长参数函数所需的头文件
/* va_start，函数名称，读取可变参数的过程其实就是在堆栈中，使用指针,遍历堆栈段中的参数列表,从低地址到高地址一个一个地把参数内容读出来的过程 */
# include"cutoff_ast.h"

int i = 0;
int printSlash[200] = {0,0,};

// 生成的ast树可以看作左孩子右兄弟

char *opname( int op ) {
	static char *opnames[] = {
	"",
	"CNST",
	"ARG",
	"ASGN",
	"INDIR",
	"CVC",
	"CVD",
	"CVF",
	"CVI",
	"CVP",
	"CVS",
	"CVU",
	"NEG",
	"CALL",
	"*LOAD*",
	"RET",
	"ADDRG",
	"ADDRF",
	"ADDRL",
	"ADD",
	"SUB",
	"LSH",
	"MOD",
	"RSH",
	"BAND",
	"BCOM",
	"BOR",
	"BXOR",
	"DIV",
	"MUL",
	"EQ",
	"GE",
	"GT",
	"LE",
	"LT",
	"NE",
	"JUMP",
	"LABEL",
	"AND",
	"NOT",
	"OR",
	"COND",
	"RIGHT",
	"FIELD"
	}, *suffixes[] = {
		"0", "F", "D", "C", "S", "I", "U", "P", "V", "B",
		"10","11","12","13","14","15"
	};

	if (generic(op) >= AND && generic(op) <= FIELD && opsize( op ) == 0)
		return opnames[opindex( op )];
	return stringf( "%s%s%s",
					opindex( op ) > 0 && opindex( op ) < NELEMS( opnames ) ?
					opnames[opindex( op )] : stringd( opindex( op ) ),
					suffixes[optype( op )], opsize( op ) > 0 ? stringd( opsize( op ) ) : "" );
}

Tree newast( const char*name, int num, ... ) {
	va_list valist;
	src.x +=strlen(name) ;
	Tree a = (Tree)malloc( sizeof( struct ast ) );// 新生成的父节点
	Tree temp = (Tree)malloc( sizeof( struct ast ) );
	a->info.file = file;
	a->info.x = yylineno;
	a->info.y = src.x -= strlen( name );
	//printf("newNODE!nameis=%s numis=%d\n",name,num);
	//printf( "yytext=%s\n", yytext );
	//printf("sizeof(struct ast)=%d\n",sizeof(struct ast));
	if (!a || !temp)
	{
		yyerror( "out of space", a );
		exit( 0 );
	}
	;
	//a->type = name;
	strcpy( a->type, name );
	a->l = NULL;
	a->r = NULL;
	temp->l = NULL;
	temp->r = NULL;
	va_start( valist, num );
	if (num > 0) {
		temp = va_arg( valist, struct ast* );// 取变长参数列表中的第一个结点设为a的左孩子
		a->l = temp;

		if (num >= 2) // 可以规约到a的语法单元>=2
		{
			for (i = 0; i < num - 1; ++i)// 取变长参数列表中的剩余结点，依次设置成兄弟结点
			{
				temp->r = va_arg( valist, struct ast* );
				temp = temp->r;
			}
		}
	}
	else {
		// 没有子节点,即第一次读入的时候
		//a的种类：非关键字情况下的种类:取决于symbol
		// number id type var其中只有var需要有name
		int t = va_arg( valist, int );
		a->line = t;

		if ((!strcmp( a->name, "STRINGNUM" )))// "ID,TYPE,INTEGER，借助union保存yytext的值
		{
			char* strinfo;
			strinfo = (char*)malloc( sizeof( char )* sizeof(&yytext) );strcpy( strinfo, yytext );
			a->sym=string( strinfo );
		}
		else if (!strcmp( a->name, "INTNUM" )) { 
			a->u.i = atoi( yytext );
		}
		else if (!strcmp( a->name, "APPROXNUM" )) {
			a->u.f = ( atof( yytext ) );
		}
		else if (!strcmp( a->name, "NAME" )) {
		/*	char*t;t = (char*)malloc( sizeof( char* ) * 16 );strcpy( t, yytext );
			a->i= (struct ifo*)malloc( sizeof( struct ifo ) );
		    a->i->name  = t ;
			a->i->varid = -1;*/
			a->sym = firstInit( name );
			strcpy( a->idtype, yytext );
		}
		else if (!strcmp( a->type, "TYPE" )) {
			if (!strcmp( yytext, "char" )) {
				a->ty = chartype;
				a->opType =CHAR ;
				
			}
			else if (!strcmp( yytext, "int" )) {
				a->ty = inttype;
				a->opType = INT;
			}
			else if (!strcmp( yytext, "float" )) {
				a->ty = floattype;
				a->opType = FLOAT;
			}
			else if (!strcmp( yytext, "string" )) {
				a->ty = voidptype;
				a->opType = CHAR;
			}
			else if (!strcmp( yytext, "void" )) {
				a->ty = voidptype;
				a->opType = VOID;
			}
			else {
				yyerror( "该类型暂未实现\n" );
			}
		}

	}
	va_end( valist );
	 //eval_print(a,num);
//	printf("a->type%s ",a->type);
	return a;
}
Tree newNode( const char*name, Tree l, Tree r, int oppr, int opty, int type) {

	Tree a = (Tree)malloc( sizeof( struct ast ) );// 新生成的父节点
	if (!a )
	{
		yyerror( "out of space", a );
		exit( 0 );
	}
	strcpy( a->type, name );
	a->l = NULL;
	a->r = NULL;
	a->opPr = oppr;
	a->opType = opty;
	a->type = type;
	return a;
}

/* 这只是一个打印结点信息的函数 */
void eval_print( struct ast*a, int level ) {
	if (a != NULL) {
		
		if (a->line != -1) { // 产生空的语法单元不需要打印信息
			if (a->l != NULL &&a->l->r != NULL&& a->l->r->line != -1)
				printSlash[level] = 1;//有兄弟节点那么子节点的子节点在这一列需要打印竖线
			else printSlash[level] = 0;//如果没有兄弟节点那么这一列子节点的子节点不需要打印竖线 该节点可能是之前结点的兄弟结点，所以需要清零
			if (level!=0&&a->r == NULL)printSlash[level - 1] = 0;
			for (int i = 0; i < level; i++)// 孩子结点相对父节点缩进2个空格
			{
				if (i == level - 1)printf( "|__" );
				else {
					if (printSlash[i]==1) { printf( "|  " ); }
					else printf( "   " );
				}
				/*int a(int a){int a;}*/
			}
			printf( "%s ", a->type );// 打印语法单元名字,STRINGNUM/NAME/TYPE(CHAR/INT/BOOL/DOUBLE)要打印yytext的值
			if ((!strcmp( a->type, "STRINGNUM" )) || (!strcmp( a->type, "TYPE" )))printf( ":%s ", a->idtype );
			else if (!strcmp( a->type, "INTNUM" ))printf( ":%d", a->intgr );
			else if (!strcmp( a->type, "APPROXNUM" ))printf( ":%f", a->dou );
			printf( "(%d)", a->line );
			printf( "\n" );
		}
		

		eval_print( a->l, level + 1 );// 遍历左子树
		eval_print( a->r, level );// 遍历右子树
	}
	//

}
void yyerror(const char*s, ... ) // 变长参数错误处理函数
{
	va_list ap;
	va_start( ap,s );
	fprintf( stderr, "%d:error:", yylineno );
//eval_print(a,a->line);
	vfprintf( stderr, s, ap );
	fprintf( stderr, "\n" );
	va_end( ap );
}
void treefree( struct ast *a ) {
	if (a != NULL) {
		if (a->l != NULL)treefree( a->l );
		if (a->r != NULL)treefree( a->r );
		free( a );
	}
	else printf( "this is a bad node\n" );
}