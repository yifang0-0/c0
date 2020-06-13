/*
//表达式文件需要处理的是已知的symbol的处理
1.类型检查、转化
2.检查、更新符号表（转换后）
3.NAME是否存在与符号表中（当前scope）
4.更新运算符的运算类型：ADD->ADDI,g更新op值
处理函数
expr1(单变量，如自增自减，sizeof，强制类型转换)
expr2(双变量，+=*%/ 逻辑比较符)
expr3(:? 条件选择符，还没想好怎么处理···)

*/
#include "datastructure.h"
Tree exprCOMMA(Tree right ) {
	right->ty = right->l->r->ty;
	right->sym = right->l->r->sym;
	right->op = RIGHT;
	return right;
}