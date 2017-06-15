#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main( void )
{
	int i;
	int j;
	int max;
	int min;
	//int sec;
	int a[5];

	srand(time(NULL));
	
	for (i=0; i<5; i++)
		a[i] = rand()%100 + 1;

	for (i=0; i<5 || !printf("\n"); i++)
		printf("%d ", a[i]);
	
	//sec = max = a[0];
	/*
	for (i=1; i<5; i++) 
	{
		if ( a[i] > max ){
			//sec = max;
			max = a[i];
		}
	}*/
	
	//有时形，有时不行,那就是不行
	//printf("max=%d, sec=%d\n", max, sec);
	
	/*
	for (i=0; i<5; i++) {
		min = i;
		for (j=i; j<5; j++)
			if ( a[j] < a[min])
				min = j;
		
		int tmp = a[min];
		a[min] = a[i];
		a[i] = tmp; 
	}
	*/

	for (i=0; i<5; i++)
		for (j=i; j<5; j++)
			if ( a[j] < a[i] ) {
				int tmp = a[i];
				a[i] = a[j];
				a[j] = tmp;
			}

	for (i=0; i<5 || !printf("\n"); i++)
		printf("%d ", a[i]);
	
	return 0;
}

