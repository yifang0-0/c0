#include "dataStructure.h"
#include <string>

/*
�ڵ���Ϣ�����˸������͵Ļ�����Ϣ��
	���ŵ�sym�� 
	���͵�ty��
	constant���͵�ֵ�� u
	constant���͵������� idtype
	ȡ��ַ���͵�ƫ�����򣨣�
	ԭʼ����info��
	���ҽڵ� l r
	�洢�ڵ�����name��
	�洢�ڵ㹦����opPr
		����ת��ָ��
			ָ���Ŀ�Ĳ�����������opType
			ָ���Դ������������ͨ������ڵ������
	ָ��Ĳ��������ͣ�0const 1���Ʊ��� 2������ʶ�� 3������

	����generateʱ���ȫ�ֱ���
		��ӡ�������: int assLine
		����������functionNumber=0
		����������constantsNumber=0
		���ڱ���ƫ��ֵ��identificaionOffset=0
		��ǰ�ڵ���������������Ҳ����� ifRight 0���������ʹ��eax��1�Ҳ�����ʹ��ebx
��������   operation
��׺       type[]
Ŀ�Ĳ����� tar
Դ����1   sou1
Դ����2   sou2
sou: imm
	 reg
*/
int assLine=0;//��ӡ�������
int functionNumber = 0;//����������
int constantsNumber = 0;//����������
int identificaionOffset = 0;//���ڱ���ƫ��ֵ��