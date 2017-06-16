#include <stdio.h>
/*
double
sque( x, y )
int x;
double y;
{
	return x + y;
}
*/

/*
void __attribute__((stdcall)) test(int i, int j)
{
	printf("%d,%d\n", i, j);
}
*/

void before(void) __attribute__((constructor));
void after(void) __attribute__((destructor));

void after(void)
{
	printf("after!\n");
}

int main( void )
{
/*
	int k = 1;
	test(k, k++);
	printf("k=%d\n", k);
*/
	printf("in main!\n");
	return 0;
}

void before(void)
{
	printf("before!\n");
}
