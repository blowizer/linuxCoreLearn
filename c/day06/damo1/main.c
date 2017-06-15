#include <stdio.h>

#include "check.h"
#include "convert.h"

int main( void )
{
	char c;
	
	do {
		scanf("%c", &c);
		if ( isLower(c) ) {
			printf("%c", toUpper(c));
		} else if ( isNum(c) ) {
			toChinese(c);
		} else {
			printf("%c", c);
		}
	} while ( c != '\n' );	

	return 0;
}

