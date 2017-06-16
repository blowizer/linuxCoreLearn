#include <stdio.h>

int main( void )
{
	char c;
	char stat = '?';

	while ( (c=getchar()) != EOF )
	{
		if ( c == ' ' && stat != ' ')
		{
			printf("%c", c);
		}
		else if ( c != ' ' )
		{
			printf("%c", c);
		}
		stat = c;
	}
}

