#pragma once
//#define VAR_HASH_SIZE 11
//#define VAR_HASH_SHIFT 4

# include "c.h"
/* 变量表 */



/*
函数定义时建立一个hash顺序链表存取变量
没有退出函数的时候出现大括号就在现有的表格中头结点后插入新的结点，一旦退出当前块需要删除结点
如何实现删除当前块内结点？
1.链表结点包含一个标志位，记录是否为当前块的变量
2.每个块建立不同的hash表，hash表本身呈链状相连
*/



