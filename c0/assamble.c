//生成汇编
# include "c.h"
//1：开头

void generateAsm( ) {
	FILE *fpWrite = fopen( "data2.txt", "w+" );
	if (fpWrite == NULL) { 
		
		yyerror( "写入文件失败\n" );
		exit( 0 );
	}
	//fprintf( fpWrite, "%%include \"io.asm\"\n" );
	//fclose( fpWrite );
	//fpWrite = fopen( "data.txt", "a+" );
	generateData( fpWrite );
	generateBss( fpWrite );
	generateStart( fpWrite );
	generateMain( fpWrite );
	//generateOtherFunc( fpWrite );
	fclose( fpWrite );

}
/*
void generateOtherFunc( FILE *fpWrite ) {
	while()
	scanMidEqual( fpWrite );
}
*/

void generateMain( FILE *fpWrite ) {
	scanMidEqual( fpWrite );
}
void printfString( FILE *fpWrite ) {
	stringList newList = constString->next;
	while (newList != NULL) {
		fprintf( fpWrite, "    ?str_%d bd \"%s\"00h\n", newList->i, newList->a );
	}
	//return -1;
}
void printfConstant( FILE *fpWrite );
void generateData( FILE *fpWrite ) {
	//数据段的输出
	fprintf( fpWrite, "section .data\n" );
	printfString( fpWrite );
	printfGlobal( fpWrite, constants, CONSTANT );
	printfGlobal( fpWrite,identifiers, GLOBAL );
	//遍历constan
	//遍历string

	//遍历identifiers

}
void generateStart( FILE *fpWrite ) {
	fprintf( fpWrite, "section .text\n" );
	//fprintf( fpWrite, "_start:\n" );

}

void generateFuncHead( FILE *fpWrite,int offset ) {
	fprintf( fpWrite, "    push ebp\n" );
	fprintf( fpWrite, "    mov ebp,esp\n" );
	//fprintf( fpWrite, "    push ebx\n" );
	fprintf( fpWrite, "    sub esp,%d\n",offset*4 );
	
}


void generateBss( FILE *fpWrite ) {
	fprintf( fpWrite, "section .bss\n" );
	printfidentifiers( fpWrite, identifiers, GLOBAL );
}
