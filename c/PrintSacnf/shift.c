#include <stdio.h>

int main( void )
{
	int i = 0X78563412;
	printf("%#X\n", (char)i);
	printf("%#X\n", (char)(i>>8));
	printf("%#X\n", (char)(i>>16));
	printf("%#X\n", (char)(i>>24));

	int a = 0X12;
	int b = 0X34;
	int c = 0X56;
	int d = 0X78;
	int j = (d<<24) | (c<<16) | (b<<8) | a;
	printf("%#X\n", j);

	return 0;
}

