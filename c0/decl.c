#include "dataStructure.h"
/*
树节点定义部分
	事实上这部分节点在遍历的时候只要做到
		初始化：TypeInitial
		创建新种类
			结构*暂时不考虑的
			指针*暂时不考虑的
			函数
			数组
		读取限定符
		unsigned 影响类型
		const 必须在创建时赋值
	
变量声明不建立存取树
变量定义先取地址，assgin,mov回源地址

	每一类的操作方式
		声明 Tree varDec(Tree type,Tree var,int ifConst)
		newNode("DEC",TYPE,VAR,0,TYPE->OP,IFCONST)
			①：if（ifConst）不断查找varlist的左节点是否为空，如果空则完成操作
				查找：lookup()不存在、存在但type相同且defined=0
				记录：当前域中的变量个数（建立节点时，以便为栈分配空间），变量名由变量表自动生成，在表中保存当前的偏移量n
				(实际偏移应是esp+n-size)
				n=n+type->size
				不生成任何语句！
			if(ifConst==0)但没有assgin ：错误，必须声明时定义
		
		定义	
			①：
				普通节点定义
				if（no const）找到一个节点，
				查找：lookup()不存在、存在但type相同且defined=0
				其左子树是assign，
				//由于匹配 能出现在此处的一定有类型符号
				检查assgin左右节点类型转换是否可能
					char* 对 constant string
					pointer 对 pointer
					其他《=float以下的转换与assgin相同
				失败 输出错误
				成功 正常建立了节点 在identificaiton表中新建节点
				n=n+type-size
				sym->defined=1
				由于assgin是特别设置（没有取数存数环节）
			if(const) 同上 在constants表中建立节点 不改变n
		②：
			函数定义
					Tree functionDef(Tree returnType,Tree name,Tree decList,Tree compost){ 
					type()//建立function的类 可以检查否重定义
					Tree return=newNode("PUSH",returnType,null,PUSH,return->op,0)//函数值不能作为左值
				
				左子树递归使用varDec()，然后pop
					popArgs= newNode( "ARGPOP", VAR, VARLIST, POP, VAR->type, 1 );//打印pop eax ;mov eax n 更新n=n+typesize
				newNode("NOP",popArgs，compost,0,0,0)
					newNode("PROC",NOP，returnType) //打印当前函数名 NAME UESE EAX EBX ECX EDX
		③：Tree arrayDef(Tree type,Tree var,int ifConst,Tree exp){
		//在Tree varDec发现var-l-name!=name 而是==var,跳进来
					Type()
					install()
					var-l=var
					var-r=exp
				//和普通变量的区别 此时要建立新的Type array,其他步骤都一样，唯一的就是sym->offset=n,n+=name->sym->ty->Type->size*n
					var-l=var
					var-r=null
					sym->offset=n,n+=4(不定长度的指针)
					return VAR
		}





					

		}
				
				
				返回值在右侧

		

*/