#include <stdio.h>

int main( void )
{
	char c;
	int stat = 0;
	
	while ( (c=getchar()) != EOF )
	{
		if ( c == ' ' )
		{
			if ( ++stat == 1 )
			{
				printf("%c", c);
			}
		}
		else
		{
			stat = 0;
			printf("%c", c);
		}
	}
	
	return 0;
}

