#include "dataStructure.h"
#include <string>

/*
节点信息包括了各种类型的基本信息：
	符号的sym域 
	类型的ty域
	constant类型的值域 u
	constant类型的名称域 idtype
	取地址类型的偏移量域（）
	原始结点的info域
	左右节点 l r
	存储节点名称name域
	存储节点功能域opPr
		类型转换指令
			指令的目的操作数类型域opType
			指令的源操作数类型域（通常由左节点决定）
	指令的操作数类型（0const 1名称变量 2保留标识符 3其他）

	设置generate时候的全局变量
		打印汇编条数: int assLine
		函数个数：functionNumber=0
		常量个数：constantsNumber=0
		域内变量偏移值：identificaionOffset=0
		当前节点是左操作数还是右操作数 ifRight 0左操作数，使用eax，1右操作数使用ebx
操作名称   operation
后缀       type[]
目的操作符 tar
源操作1   sou1
源操作2   sou2
sou: imm
	 reg
*/
int assLine=0;//打印汇编条数
int functionNumber = 0;//函数个数：
int constantsNumber = 0;//常量个数：
int identificaionOffset = 0;//域内变量偏移值：