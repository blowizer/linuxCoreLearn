#include <stdio.h>

int main( void )
{
	int i,j;
	int a[3][5] = {
		{1,2,3},
		{4,5},
		{6}	
	};
	
	for (i=0; i<3; i++) {
		for (j=0; j<5; j++)
			printf("%d ", *(a[i]+j));
		printf("\n");
	}
}

