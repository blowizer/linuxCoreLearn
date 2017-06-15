#include <stdio.h>

int main( void )
{
	int car; //分配一块内存空间，垃圾数据
	float price;

	int bird = 10; //初始化

	printf("car=%d\n", car);
	printf("price=%f\n", price);
	printf("bird=%d\n", bird);

	bird = 20; //给变量赋值

	return 0;
}

