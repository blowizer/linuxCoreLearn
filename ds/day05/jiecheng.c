#include <stdio.h>

int jiecheng(int n)
{
	if ( n <= 1 )
		return 1;
	else
		return jiecheng(n-1)*n;
}

int main_( void )
{
	printf("%d\n", jiecheng(3));
	
	return 0;
}

