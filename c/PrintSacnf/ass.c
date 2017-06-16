#include <stdio.h>

int main( void )
{
	int i = 5;

	i *= 2 + 3;

	printf("i=%d\n", i);
	printf("/=%d\n", i/=5-2);
	printf("<<=%d\n", i<<1+2);
	printf("i=%d\n", i);
}

