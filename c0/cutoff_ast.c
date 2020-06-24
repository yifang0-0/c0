//变长参数函数所需的头文件
/* va_start，函数名称，读取可变参数的过程其实就是在堆栈中，使用指针,遍历堆栈段中的参数列表,从低地址到高地址一个一个地把参数内容读出来的过程 */
# include"c.h"
extern char* yytext;
 Coordinate src;
int i = 0;
int printSlash[200] = {0,0,};

Tree newast( const char*name, int num, ... ) {
	va_list valist;
	src.x +=strlen(name) ;
	Tree a = (Tree)malloc( sizeof( struct ast ) );// 新生成的父节点
	Tree temp = (Tree)malloc( sizeof( struct ast ) );
	
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
	strcpy( a->name, name );
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
		//a->line = t;

		if ((!strcmp( a->name, "STRINGNUM" )))// "ID,TYPE,INTEGER，借助union保存yytext的值
		{
			char* strinfo;
			strinfo = (char*)malloc( sizeof( char )* sizeof(&yytext) );strcpy( strinfo, yytext );
			//string( strinfo );
			stringList newList;
			newList=getNumber( yytext );
			a->intgr = newList->i;
			//按常量处理
			//string 类型常量必须保存在data段

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
			//a->sym = firstInit( name );
			a->idtype = (char*)malloc( (1+strlen(yytext)));
			strcpy( a->idtype, yytext );
		}
		else if (!strcmp( a->name, "TYPE" )) {
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
				a->ty = voidtype;
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
		yyerror( "out of space\n" );
		exit( 0 );
	}
	strcpy( a->name, name );
	a->l = l;
	a->r = r;
	a->opPr = oppr;
	a->opType = opty;
	a->type = type;
	return a;
}

/* 这只是一个打印结点信息的函数 */
void eval_print( struct ast*a, int level ) {
	if (a != NULL) {
		
		if (a) { // 产生空的语法单元不需要打印信息
			if (a->l != NULL &&a->r != NULL)
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
			printf( "%s ", a->name );// 打印语法单元名字,STRINGNUM/NAME/TYPE(CHAR/INT/BOOL/DOUBLE)要打印yytext的值
			if ((!strcmp( a->name, "STRINGNUM" )))printf( ":%s ", a->idtype );
			else if (!strcmp( a->name, "TYPE" )) {
				printf( ":%s ", a->ty->u.sym->name );
			}
			else if (!strcmp( a->name, "NAME" )) {
				printf( ":%s ", a->idtype );
			}
			else if (!strcmp( a->name, "CNST" )) {
				if (a->opPr == FLOAT) {
					printf( " :%f ", a->u.f );
				}
				else if (a->opPr == INT) {
					printf( " :%d ", a->u.i );
				}
			}
			//printf( "(%d)", a->line );
			printf( "\n" );
		}
		

		eval_print( a->l, level+1 );// 遍历左子树
		eval_print( a->r, level+1 );// 遍历右子树
	}
	//

}
/*
int hash( char * key, int HASH_SHIFT, int HASH_SIZE )
{
	int temp = 0;
	int i = 0;
	while (key[i] != '\0')
	{
		temp = ((temp << HASH_SHIFT) + key[i]) % HASH_SIZE;
		++i;
	}
	return temp;
}*/
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
