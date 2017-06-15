#include <stdio.h>
#include <stdlib.h>

int main( void )
{
	FILE *fp = fopen("hehe.txt", "w");
	if ( fp == NULL )
		exit(EXIT_FAILURE);

	fprintf(fp, "how are your!");
	
	fclose(fp);
	
	return 0;
}

