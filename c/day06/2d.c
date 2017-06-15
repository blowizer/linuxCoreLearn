#include <stdio.h>

int main( void )
{
	int a[2][3] = {1,2,3,4,5,6};
	int* p = (int*)a;
	int i;
	printf("sizeof *a = %d\n", sizeof(*a));
	printf("sizeof a = %d\n", sizeof(a));

	for (i=0; i<6; i++)
		printf("%d ", *(p+i));
	printf("\n");
}

