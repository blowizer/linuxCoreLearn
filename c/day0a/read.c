#include <stdio.h>
#include <stdlib.h>

int main( void )
{
	char buf[1024] = {};
	
	FILE *fp = fopen("hehe.txt", "r");
	//fscanf(fp, "%s", buf);
	fgets(buf, 1024, fp);
	fprintf(stderr, "%s\n", buf);
	
	fclose(fp);
	
	return 0;
}

