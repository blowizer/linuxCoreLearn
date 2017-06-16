#include <stdio.h>

int main( void )
{
	char c = 'm';
	int a = 2;
	int i = -1;

	printf("%s\n", c=='f' ? "女" : "男");
	printf("you have ate %d apple%s\n", a, a>1?"s.":".");
	
	printf("abs %d = %d\n", i, i<0 ? -i : i);
	
	printf("%d\n", (a, i));
}

