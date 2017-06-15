#include <stdio.h>

char w[7][10] = {
	"星期天", "星期一", "星期二",
	"星期三", "星期四", "星期五", "星期六"
};

 static char * to_chesese( int week )
{
	return w[week];
}

int main( void )
{
	printf("%s\n", to_chesese(3));
}

