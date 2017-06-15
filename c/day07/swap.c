#include <stdio.h>

int swap(int* a, int* b)
{
	printf("a=%p\n", a);
	printf("b=%p\n", b);
	*a = *a ^ *b;
	*b = *a ^ *b;
	*a = *a ^ *b;
	printf("a=%d, b=%d\n", *a, *b);
}

int main( void )
{
	int x = 10;
	int y = 20;
	
	printf("&x=%p\n", &x);
	printf("&y=%p\n", &y);
	
	printf("x=%d, y=%d\n", x, y);
	swap(&x, &y);
	printf("x=%d, y=%d\n", x, y);
}

