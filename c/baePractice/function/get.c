#include <stdio.h>

#include "clear.h"

int get(int a, int b)
{
	int n;
	if ( b < a ) 
		n = b, b = a, a = n;
	
	printf("[%d,%d]\n", a, b);
	
	do {
		printf("input an integer: ");
		if ( scanf("%d", &n) != 1 )
			clear();
	} while (n<a || b<n);
}

