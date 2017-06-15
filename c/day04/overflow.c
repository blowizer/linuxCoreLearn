#include <stdio.h>

int main( void )
{
	int x = 123;
	int a[5] = {1,2,3,4,5};
	int y = 456;
	int i;

	for (i=-1; i<=7; i++)
		printf("%d ", a[i]);
	printf("\n");

	printf("&x=%p\n&y=%p\n", &x, &y);
	printf("a+5=%p\na+6=%p\n", a+5, a+6);
	*(a+5) = 110;
	printf("x=%d\n", x);
	
	for (i=-1; i<=7; i++)
		a[i] = 0;
}

