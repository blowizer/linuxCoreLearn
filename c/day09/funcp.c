#include <stdio.h>

void furong(int n ) {
	printf("芙蓉姐姐%d岁!\n", n);
}

void canglaoshi(int n) {
	printf("苍老师的腰围%d尺\n", n);
}

int main( void ) {
	void (*p)(int) = NULL;
	
	/*
 	函数指针不允许算术运算，只能赋值，对函数名取地址的符号可有可无
 	*/
	printf("sizeof p=%d\n", sizeof(p));
	printf("furong=%p\n", furong);
	printf("furong=%p\n", furong+1);
	printf("furong=%p\n", furong);
	printf("*furong=%p\n", *furong);

	p = &furong;
	(*p)(18);
	p(18);
	(*furong)(19);
	p = canglaoshi;
	p(32);
}

