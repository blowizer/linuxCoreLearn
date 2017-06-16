#include <stdio.h>

int main( void )
{
	char c;
	int stat = 0;

	while ( (c=getchar()) != EOF ) {
		if ( c==' '||c=='\n'||c=='\t' ) {
			stat = 0;
			printf("%c", c);
		} else if ( stat == 0 ) {
			stat = 1;
			//printf("\n%c", c);
			printf("%c", c>='a'&&c<='z'?c-32:c);
		} else {
			printf("%c", c);
		}
	}

	printf("\n");

	return 0;
}

