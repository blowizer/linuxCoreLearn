#include <stdio.h>

int main( void )
{
	int i,j;
	int a[5][5] = {	
			{0,0,0,0,0},
			{0,1,1,1,0},
			{0,0,1,0,0},
			{0,0,1,0,0},
			{0,0,0,0,0},
		};
	
	for (i=0; i<5; i++) {
		for (j=0; j<5; j++)
			printf("%d", a[i][j]);
		printf("\n");
	}

	for (i=0; i<5; i++) {
		for (j=0; j<5; j++)
			a[j][i] = a[4-i][j];
	}

	printf("\n");
	for (i=0; i<5; i++) {
		for (j=0; j<5; j++)
			printf("%d", a[i][j]);
		printf("\n");
	}
}

