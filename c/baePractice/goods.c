#include <stdio.h>

#pragma pack(2)
typedef struct goods
{
	char name[18];
	double price;
	char special;
	int num;
	short sales;
} goods; //__attribute__((packed))
#pragma pack(0)

int main( void )
{
	//一个变量的地址一般会是这个变量所占字节数的整数倍
	printf("sizeof gooods=%d\n", sizeof(goods));
}

