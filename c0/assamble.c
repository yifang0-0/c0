//生成汇编
# include "c.h"
//1：开头

void generateAsm( ) {
	
	
	FILE *fpWrite = fopen( "data.txt", "a" );
	if (fpWrite == NULL) { 
		return 0; 
		yyerror( "写入文件失败\n" );
	}
	fprintf( fpWrite, "\%include \"io.asm\"\n" );
	generateData( fpWrite );
	generateBss( fpWrite );
	generateMain( fpWrite );


}
void generateMain( FILE *fpWrite ) {

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
	fprintf( fpWrite, "section \.data\n" );
	printfString( fpWrite );
	printfGlobal( fpWrite, constants, CONSTANT );
	printfGlobal( fpWrite,identifiers, GLOBAL );
	//遍历constan
	//遍历string

	//遍历identifiers

}
void generateStart( FILE *fpWrite ) {
	fprintf( fpWrite, "_start:\n" );

}

void generateFuncHead( FILE *fpWrite,int offset ) {
	fprintf( fpWrite, "    push ebp\n" );
	fprintf( fpWrite, "    mov ebp,esp\n" );
	fprintf( fpWrite, "    push ebx\n" );
	fprintf( fpWrite, "    sub esp,%d\n" );
	
}


void generateBss( FILE *fpWrite ) {
	fprintf( fpWrite, "section \.bss\n" );
	printfidentifiers( fpWrite, identifiers, GLOBAL );
}
