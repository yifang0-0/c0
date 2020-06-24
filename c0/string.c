#include "limits.h"
#include "c.h"
#include "dataStructure.h"
#define STR_HASH_SIZE 32
#define STR_HASH_SHIFT 2
//extern char* string ARGS( (char* str) );
//extern char* stringn ARGS( (char* str,int len) );
//extern char* stringd ARGS((int n));
//
static struct string {
	char *str;
	int len;
	struct string *link;
}*buckets[32];

 struct string bucket;

char* string(char* str) {
	char *s;
	for (s = str;*s;s++);
	return stringn( str, s - str );
}

char* stringd( int n ) {
	char str[8], *s = str + sizeof( str );
	unsigned m;
	*--s = '\0';
	if (n == INT_MIN) {
		m = (unsigned)INT_MAX + 1;
	}
	
	else if( n < 0 )
		m = -n;
	else m = n;
	if (m == 0) *--s = '0';
	else {
		do *--s = m % 10 + '0';
		while ((m /= n) != 0);
		if (n < 0)
			*--s = '-';
	}
	
	return stringn( s, str + sizeof( str ) - s );
}

char* stringn( char*str, int len ) {
	unsigned int h;
	char *end;
	struct string *p;
	h = hash( str, STR_HASH_SHIFT, STR_HASH_SIZE );
	end = str + len;
	for (p = buckets[h];p;p = p->link) {
		if (len == p->len) {
			char *s1 = str, *s2 = p->str;
			do {
				if (s1 == end)
					return p->str;
			} while (*s1++ == *s2++);
		}
	}
	static char*next, *strlimit;
	if (next + len + 1 >= strlimit) {
		/* 如果现有地址不够存储str（） */
		int n = len + 4 * 128;
		if(next!=NULL)
		next =(char*)realloc( next, n );
		else next = (char*)malloc( n );
		/*if (next == melloc) {
			for (p = buckets[h];p->link;p = p->link) {
				//分配失败，找到最后一个结点（其link域为null）
			}
			next = p->str;
			if (p->len < n) {
				error( "no spare room\n" );
				exit( 1 );

			}
		}*/
	
		strlimit = next + n;
	}
	p=(struct string*)malloc(sizeof( struct string ));
	p->len = len;
	//p->str = str;
	for (p->str = next;str <= end;) {
		*next++ = *str++;
	}
	*next++ = '\0';
	//p->len = len;
	p->link = buckets[h];
	buckets[h] = p;
	//将新字符串插在头部，如果是新字符那就指向初始化后的一个空bucket结构
	//newStringList( p->str );
	return p->str;
	;
}

stringList getNumber( char* m) {
	stringList newList = (stringList)malloc( sizeof( struct stringlist ) );
	newList->a = stringn( m, strlen( m ) );
	newList->i= stringNum++;
	newList->next = constString->next;
	constString->next = newList;
	return  newList;
	
}