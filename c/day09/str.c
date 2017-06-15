#include <stdio.h>
#include <string.h>

int main( void )
{
	char a[100] = {'h','e','\0','w','o'};
	puts(a);
	puts("litao");
	char *p = a;
	*p = 'H';
	puts(a);
	p = "litao";
	printf("%c\n", *p);
	// *p = 'L'; 段错误 编译通过
	char const *q = NULL;
	q = "litao";
	//*q = 'L'; 编译通不过
	p = a;
	strcpy(a, "NB");
	puts(a);
	q = a+3;
	puts(q);
	//*q = 'W'; 不允许,q的const标识q保存的字符串常量地址，把所指向的目标当作常量
	const double pi = 3.14;	
	char * const r = a;
	//r = a; 编译不过
	*r = 'H';
	puts(a);
	
	char const * const rq = a;
	
	char *str; //野指针
	printf("sizeof(str)=%d\n", sizeof(str));
	printf("sizeof(a)=%d\n", sizeof(a));
	//scanf("%s", str);
	strcpy(str, "heeh");

	return 0;
}

