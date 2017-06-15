#include <stdio.h>

int main( void )
{
	int i = 1;
	int sum = 0;

lab:
	sum += i++;

	if ( i <= 100 )
		goto lab;
	
	printf("sum=%d\n", sum);
}

