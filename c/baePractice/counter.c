#include <stdio.h>

int counter( void )
{
	static int ctr = 1;
	
	return ++ctr;
}

int main( void )
{
	printf("%d\n", counter());
	printf("%d\n", counter());
	printf("%d\n", counter());
	printf("%d\n", counter());
}

