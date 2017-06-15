#include <stdio.h>

int main( void )
{
	int year = 2000;	
	
	printf("%d\n", !year%4);
	
	printf("%d\n", 2+3 && 3+5);

	printf("9&8=%d\n", 9&8);
	printf("9|7=%d\n", 9|7);
	printf("9|7=%d\n", 9|7);
	printf("9^7=%d\n", 9^7);
	printf("~9=%d\n", ~9);

	int x = 1232435;
	printf("%d\n", x&0x1);
	printf("%d\n", x|0x08);

	int a = 7;
	int b = 6;

/*
	a = a^b;
	b = a^b; // (a^b)^b
	a = a^b; // (a^b)^a
*/
/*
	a = a*b; // 42
	b = a/b; // 42/6
	a = a/b; // 42/7
*/
/*
	a = a+b;
	b = a-b;
	a = a-b;
*/
	
	printf("a=%d,b=%d\n", a,b);
}

