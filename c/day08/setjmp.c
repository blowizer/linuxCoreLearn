#include <stdio.h>
#include <setjmp.h>

jmp_buf env;

int div(int a, int b)
{
	if ( b == 0 )
		longjmp(env, 1);
	return a / b;
}

int wuliao( void )
{
	printf("input:");
	int i;
	scanf("%d", &i);
	if ( i == 0 )
		longjmp(env, 2);
}

int main( void )
{
	int ret;
	//setjmp将环境信息保存到全局变量env中,如果是第一次调用返回0,以后当遇到longjmp时,跳转到setjmp这里,并且会使setjmp的返回值为longjmp的第二个参数的值
	if ( (ret=setjmp(env)) == 0) { 
		div(2, 1);
		wuliao();
		printf("正常执行结束!\n");
	} else if ( ret == 1) {
		printf("除数不能为0!\n");
	} else if ( ret == 2) {
		printf("太无聊!\n");
	}
} 

