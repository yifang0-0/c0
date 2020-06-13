#pragma once
#include "string.h"
#include"dataStructure.h"
//关于存储类型定义，函数、变量类型表
bool isVar( struct ast*a );
//类型判别器
bool typeChecker( struct ast* a );
//类型转换器
//变量赋值
bool varAssign( struct ast* a );
//表达式
	//中间操作符
bool midOperation( struct ast* a);

void* buildNewVar( struct ast* a );

struct ifo* varNotExist( struct ast* a );

struct ifo* searchVar( char *a );
