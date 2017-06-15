#include <stdio.h>

int main( int argc, char *argv[], char *env[] )
{
	int i=0;
	/*
	for(i=0; i<2*argc; i++) {
		if ( i != argc )
			printf("%s\n", argv[i]);
	}
	*/

	for (i=0; env[i]!=NULL; i++)
		printf("%d %s\n", i, env[i]);
}

