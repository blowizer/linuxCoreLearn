#include <stdio.h>

int main( void )
{
	volatile const int ci = 10;
	
	int* p = (int*)&ci;
	
	*p = 20;

	printf("*p=%d\n", *p);
	printf("ci=%d\n", ci);
}

