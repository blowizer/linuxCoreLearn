#include <stdio.h>

int main( void )
{
	char hex[] = "0x12ab";
	int dig = 0;
	int he;
	int i = 0;

	hex[i] == '0';
	i++;
	if (hex[i]=='x' || hex[i]=='X')
		i++;
	
	while ( (he=hex[i]) != '\0' ) {
		if ( he>='0' && he<='9')
			he = he-'0';
		else if ( he>='a' && he<='f')
			he = he-'a'+10;
		else if ( he>='A' && he<='F')
			he = he-'A'+10;

		dig = dig*16 + he;

		i++;
	}

	printf("dig=%d\n", dig);
}
	

