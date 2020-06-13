/*�洢����*/
#define __STDC__ 1
#include"c.h"
extern void*allocate (ARGS(unsigned long n, unsigned a));
extern void deallocate (ARGS(unsigned a) );
/*
�������ʽ
struct T *p;
p= allocate(sizeof *p,a);//����������ָ�������������ָ��ָ������͵ķ��䷽ʽ���Է�ֹ������ռ�ָ����������
*/
#define NEW(p,a) ((p)=allocate(sizeof*(p),(a)))
#define NEW0(p,a) memset(NEW((p),(a)),0,sizeof*(p))

//static struct block
//first[] = { {NULL},{NULL},{NULL} },
//*arena[] = { &first[0],&first[1] ,&first[2] };
//
//static struct block *freeblocks;//static ���Զ���ʼ��,��ʱ��freeblock�Ѿ��е�ַ��������

void* allocate( unsigned long n, unsigned a ) {
	struct block *ap;

	ap = arena[a];
	n = roundup( n, sizeof( union align ) );
	while ((ap->avail) + n > ap->limit) {
		if ((ap->next) = freeblocks!= NULL){
		freeblocks = freeblocks->next;
		ap=ap->next;
		}	
		else
		{
			unsigned m = sizeof( union header ) + n + 10 * 1024;
			ap->next = malloc( m );
			ap = ap->next;
			if (ap == NULL) {
				error( "insufficient memory\n" );
				return NULL;
			}
			ap->limit = (char*)ap + m;
		}
		ap->avail = (char*)((union header*)ap + 1);
		ap->next = NULL;
		arena[a] = ap;
	}
	ap->avail += n;
	return ap->avail - n;
}

void* newarray( unsigned long m, unsigned long n, unsigned a ) {
	return allocate( m*n, a );
}

void deallocate(unsigned a )
{	
	arena[a]->next = freeblocks;
	freeblocks = first[a].next;
	first[a].next = NULL;
	arena[a] = &first[a];
}


