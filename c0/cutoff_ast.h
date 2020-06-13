/* 定义抽象语法树 */
/*interface with flex*/

# include "dataStructure.h"

extern char* yytext;
extern int yylineno;
void yyerror( const char *s, ... );
/* 返回值是struct ast的构造新节点函数 */
Tree newast(const char*name,int op,int num,...);
/* 删除抽象语法树 */
void treefree(struct ast *a);
/* 遍历抽象语法树 */
double eval(struct ast *a);
/* 打印抽象语法树的信息 */
void eval_print(struct ast*a,int level);
/* 如何存储数组？type=int/float/char 从地址取值 */
//Tree findTheRight( const char*name, int op, int num, ... );