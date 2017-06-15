#include <stdio.h>

#define MIN(a, b) ({	\
	typeof(a) _a = a; \
	typeof(b) _b = b; \
	(_a) < (_b) ? (_a): (_b); \
})

int main( void )
{
	int a  = 120;
	int b = 20;
	
	printf("%d\n", MIN(++a, ++b));
}

