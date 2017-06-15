#include <stdio.h>
#include <string.h>

int main( void )
{
	char str[] = "this/is/maomao/chong";
	char *p = strrchr(str, '/');
	printf("p=%s\n", p);
	return 0;
}

