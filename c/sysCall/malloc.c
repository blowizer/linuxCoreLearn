#include <stdio.h>
#include <stdlib.h>

int main( void )
{
	int *p = (int*)malloc(sizeof(int));
	double *q = (double*)malloc(sizeof(double));
	printf("&p=%p\n", &p);
	printf("p=%p\n", p);
	printf("q=%p\n", q);
	int i=0;
	for (i=0; i<2; i++)
		p[i] = i+1;
	for (i=0; i<2; i++)
		printf("p[%d]=%d\n", i, p[i]);
	*p = 20;
	printf("*p=%d\n", *p);
	
	
	free(p);
	/*
	p = NULL;
	printf("*p=%d\n", *p);
	*/
}

