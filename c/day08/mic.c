#include <stdio.h>

//C语言预先定义的宏
int main( void )
{
	printf("%s\n", __FILE__);//获得当前文件的文件名
	printf("%d\n", __LINE__);//获得当前行号
	printf("%s\n", __DATE__);//获得日期
	printf("%s\n", __TIME__);//获得时间
	printf("%d\n", __STDC__);//表示C语言
	
	return 0;
}

