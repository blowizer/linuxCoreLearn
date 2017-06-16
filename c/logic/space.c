#include <stdio.h>

int main( void )
{
	char c;
/*	 夏攀想的思路
	while ( (c=getchar()) != EOF )
	{
		if ( c == ' ' )
		{
			printf("%c", c);
			while ( (c=getchar()) == ' ')
				;
		}
		printf("%c", c);
	}
*/
/* 杜兴铎的思路 */

	while ( (c=getchar()) != EOF )
	{
		if ( c == ' ')
		{
			while ( (c=getchar()) == ' ')
				;
			printf(" ");
		}
		printf("%c", c);
	}

	return 0;
}

