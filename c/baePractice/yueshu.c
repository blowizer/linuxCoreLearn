#include <stdio.h>

int main( void )
{
	int m;
	int n;
	int r;

	printf("求最大公约数!\n");
	printf("请输入两个数:");
	scanf("%d%d", &m, &n);

	r = m%n;
	while ( r != 0 )
	{
		m = n;
		n = r;
		r = m%n;
	}

	printf("最大公约数是%d\n", n);

	return 0;
}

