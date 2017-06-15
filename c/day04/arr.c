#include <stdio.h>

int main( void )
{
	int a[5] = {11,22,33,44,55};

	printf("a=%p\n", a);
	printf("a+1=%p\n", a+1);
	printf("&a[1]=%p\n", &a[1]);
	printf("a[1]=%d\n", a[1]);
	printf("*(a+1)=%d\n", *(a+1));
	printf("*(1+a)=%d\n", *(1+a));
	printf("1[a]=%d\n", 1[a]);
	
	return 0;
}

