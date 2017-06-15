#include <stdio.h>

int main(int argc, char *argv[])
{
	int i;
	printf("argc=%d\n", argc);
	for (i=0; i<argc; i++)
		printf("%d: %s\n", i, argv[i]);
	printf("\n");
	
	for (i=0; argv[i]!=NULL; i++)
		printf("%s\n", argv[i]);

	return 0;
}
