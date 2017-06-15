#include <stdio.h>

int main( void )
{
	register int i = 5;
	volatile const int b = 20;
	
	printf("%p\n", &b);
	//printf("%p\n", &i);
	
	for (i=0; i<5; i++)
		printf("%d万岁万岁万万岁!\n", i);
}

