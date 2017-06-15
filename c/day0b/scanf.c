#include <stdio.h>

int main( void )
{
	int x, y;
	
/*
	scanf("%2d%2d", &x, &y);
	printf("x=%d,y=%d\n", x, y);
	scanf("%*d%d", &x);
	printf("x=%d\n", x);
*/
	
	char c;
	char str[100];
	scanf("%[^\n]", str); //读取[]里面有的字符
	scanf("%*c%c", &c);
	scanf("%*[^\n]"); scanf("%*c");
	printf("str=%s\n", str);
	printf("c=[%c]\n", c);
}

