#include <stdio.h>

int passw()
{
	int d;
	printf("input pas:");
	scanf("%d", d);
	return d==123;
}

int main( void )
{
	if ( passw() == 1 )
	{
		printf("login ok!");		
	}
	else {
		printf("login failed!\n");
	}
}

