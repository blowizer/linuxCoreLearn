/*
 *  程序功能：在屏幕上显示hello world
 *
 */
#include  \
<stdio.h> // 预处理行

// C程序有且必有的一个main函数
// C中的潜规则，默认类型为int
int main( void )
{
	#include "haha"
	printf("hello world\n");
/*
		\a  喇叭
		\b  退格
		\n  换行
		\r  回车
		\t  水平制表
		\v  垂直制表
		\\  \本身
		\"
*/
	printf("abc\vd\n");
		
	return 0; //0表示正常，非0标识错误
}

