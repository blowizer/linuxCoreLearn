#include <stdio.h>

int main( void )
{
	int i;
	int a[8] = {11,22,33,44,55,66,77,88};
	int b[5] = {};
	
	//b = {1,2,3,4,5};
	b[0] = 99;
	b[1] = 88;
	scanf("%d", &b[2]);
	
	for (i=0; i<8; i++)
		printf("%d\n", a[i]);

	printf("\n\n\n");
	for (i=0; i<5; i++)
		printf("%d\n", b[i]);

}

