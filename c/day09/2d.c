#include <stdio.h>

int main( void )
{
	int a[3][4];
	a 包含了3个元素，每个元素是int[4]
	a[0] a[1] a[2]
	
	a+1;
	&a+1;
	*(*(a+1)+2);
	*(a[1]+2);
	a[1][2];
}

