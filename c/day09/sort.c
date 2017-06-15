#include <stdio.h>

#define swap(a, b) {	 \
		typeof(a) t = a; \
		a = b; \
		b = t; \
	}

int main( void )
{
	const int a=10, b=8, c=20, d=60, e=100, f=32;
	const int *p[6] = {&a, &b, &c, &d, &e, &f};
	
	int i;
	int j;
	
	for (i=0; i<6; i++)
		for (j=i+1; j<6; j++)
			if ( *p[i] > *p[j] )
				swap(p[i], p[j]);
	
	for (i=0; i<6; i++)
		printf("%d ", *p[i]);
	printf("\n");
	
	return 0;
}

