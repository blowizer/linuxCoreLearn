#include <stdio.h>

int main( void )
{
	char c;
	char *pc = &c;
	int i = 1090;
	int *pi = &i;
	short s;
	short *ps = &s;
	int **ppi = &pi;
	//int ***pppi = &ppi;
	
	printf("&i=%p\n", &i);
	printf("pi=%p\n", pi);
	printf("&pi=%p\n", &pi);
	printf("ppi=%p\n", ppi);
	printf("*ppi=%p\n", *ppi);
	printf("**ppi=%d\n", **ppi);
	
}

