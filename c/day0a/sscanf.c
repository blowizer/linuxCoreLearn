#include <stdio.h>

int main( void )
{
	char buf[] = "lilei 123|45.3";
	int i;
	double d;
	char name[10] = {};
	
	sscanf(buf, "%s%d|%lf", name, &i, &d);
	fprintf(stdout, "name=%s,i=%d,d=%f\n", name, i, d);
}

