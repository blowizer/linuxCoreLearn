#include <stdio.h>

int main( void )
{
	int n = 10;
	
	printf("char=%d\n", sizeof(char));
	printf("short=%d\n", sizeof(short));
	printf("int=%d\n", sizeof(int));
	printf("long=%d\n", sizeof(long));
	printf("long long=%d\n", sizeof(long long));
	
	printf("float=%d\n", sizeof(float));
	printf("double=%d\n", sizeof(double));
	printf("long double=%d\n",sizeof(long double));
	
	printf("n=%d\n", sizeof(n));
	printf("n=%d\n", sizeof n);
	printf("n+2=%d\n", sizeof(n+2));
	printf("n+2.5=%d\n", sizeof(n+2.5));
	printf("n=20=%d\n", sizeof(n=20));
	printf("n=%d\n", n);

	return 0;
}

