#include <stdio.h>

int main( void )
{
	char c;
	int wc = 0;
	int lc = 0;
	int cc = 0;
	int stat = 0;

	while ( (c=getchar()) != EOF )
	{
		cc++;
		if ( c == '\n' )
			lc++;
		if ( c==' '||c=='\n'||c=='\t' )
		{
			stat = 0;
		}
		else if ( stat == 0 )
		{
			stat = 1;
			wc++;
			//printf("wc=%d\n", wc);
		}
		//printf("%c %d\n", c, stat);
	}

	printf("cc=%d, wc=%d, lc=%d\n", cc, wc, lc);

	return 0;
}

