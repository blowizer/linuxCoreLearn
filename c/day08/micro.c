#include <stdio.h>

#define P printf
#define M int main( void ) {
#define I \
	int n; \
	printf("请输入一个整数:"); \
	scanf("%d", &n);
#define END return 0; }

M
	P ("helloWrold!\n");
	I
	P ("你输入的数据是%d的一半!\n", n+n);
END

