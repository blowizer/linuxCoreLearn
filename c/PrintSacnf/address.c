#include <stdio.h>

int main( void )
{
	int a = 20;

	*&a = 30;

	printf("%u\n",*&a);
}

