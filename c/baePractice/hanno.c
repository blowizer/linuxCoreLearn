#include <stdio.h>

void move(char x, char y)
{
	static int cnt = 0;
	printf("%d %c => %c\n", ++cnt, x, y);
}

void hanno(int n, char a, char b, char c)
{
	if ( n == 1 )
		move(a, c);
	else {
		hanno(n-1, a, c, b);
		move(a, c);
		hanno(n-1, b, a, c);
	}
}

int main( void )
{
	hanno(3, 'A', 'B', 'C');
	return 0;
}

