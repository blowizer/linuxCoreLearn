#include <stdio.h>

void show(int x[], int len)
{
	printf("sizeof=%d\n", sizeof(x));
	int i;
	for (i=0; i<len; i++)
		printf("%d ", x[i]);
	printf("\n");
}

void show2(int *x, int len)
{
	printf("sizeof=%d\n", sizeof(x));
	int i;
	for (i=0; i<len; i++)
		printf("%d ", x[i]);
	printf("\n");
}

int strLen(char *s)
{
	int i = 0;
	while ( *s++ )
		i++;
	return i;
}

int main( void )
{
	printf("%d\n", strLen("hehe"));
	//int a[5] = {1,2,3,4,5};
	//show2(a, 5);
	return 0;
}

