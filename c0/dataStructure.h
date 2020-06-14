#pragma once
//#define VAR_HASH_SIZE 11
//#define VAR_HASH_SHIFT 4
#include <string.h>
# include<stdlib.h>
#include"stdbool.h"
# include<stdio.h>
# include<stdarg.h>
# include "c.h"
/* 变量表 */

struct ifo {
	// 变量的树结点信息
	char *name;
	int* varid;// 变量在表中的地址
	char *type;
	int size;
	int num;
};

/*ast node*/
struct ast {
	union {
		char *idtype;
		int intgr;
		double dou;
		//struct ifo *i;
		Value u;
		Symbol sym; //符号即存取符号表入口
		Type ty;    //类型即存取类型		
	};//如果是数值 constant name 需要用到这个
	//储存变量的值 常数类型（前三项），变量类型（struct ifo*）
	char name[15];//存储节点名称
	Coordinate info; //存储节点位置
	struct ast *l;
	struct ast *r; //是否还需要指向下一个结点的？
	int opPr; //存储节点功能
	int opType;//操作类型
	//左孩子右兄弟
	int type;//0const 1名称变量 2保留标识符 3其他
};
typedef struct ast* Tree;
/* 函数根节点表 */
struct funcList {
	int num;
	struct ast* func;
};


/*
函数定义时建立一个hash顺序链表存取变量
没有退出函数的时候出现大括号就在现有的表格中头结点后插入新的结点，一旦退出当前块需要删除结点
如何实现删除当前块内结点？
1.链表结点包含一个标志位，记录是否为当前块的变量
2.每个块建立不同的hash表，hash表本身呈链状相连
*/

 int hash( char * key,int HASH_SHIFT,int HASH_SIZE )
{
	int temp = 0;
	int i = 0;
	while (key[i] != '\0')
	{
		temp = ((temp << HASH_SHIFT) + key[i]) % HASH_SIZE;
		++i;
	}
	return temp;
}

struct  vaList {
	struct ifo* hashList[11];
	struct vaList * nextHashList;
};

struct vaList * variable=NULL;
