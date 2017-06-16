#include <stdio.h>

int main( void )
{
	int i = 12.34;
	double d = 1.2345678988888;
	float f = 1.2345678988888;

	printf("i=%d\n", i);
	printf("i=%f\n", i);//格式不对,输出的不是想要的
	printf("d=%d\n", d);
	printf("d=%d\n", (int)d);
	printf("d=%.15f\n", d);
	printf("f=%f\n", f);
	printf("f=%.15f\n", f);
	
	return 0;
}

