#include <stdio.h>

int main( void )
{
	int i;
	int a[10] = {1,1};

	for (i=2; i<10; i++)
		a[i] = a[i-1] + a[i-2];

	for (i=0; i<10; i++)
		printf("%d ", a[i]);
	printf("\n");

	return 0;
}

