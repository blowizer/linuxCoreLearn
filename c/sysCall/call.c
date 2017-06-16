#include <stdio.h>
#include <stdlib.h>

int main( void )
{
	int *p = malloc(sizeof(int)*5);
	//int *p = calloc(5, sizeof(int));
	int i = 0;
	
	for (i=0; i<5; i++) {
		p[i] = i+1;
		//printf("%d ", p[i]);
	}
	
	printf("\np=%p\n", p);
	int *q = realloc(p, 10);
	/*
	for (i=0; i<10; i++) {
		printf("%d ", p[i]);
	}
	*/
	
	//p = realloc(p, 20);
	printf("q=%p\n", q);
}

