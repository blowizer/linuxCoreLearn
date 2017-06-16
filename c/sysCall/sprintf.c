#include <stdio.h>

int main( void )
{
	int i = 123;
	double d = 99.99;
	char *name = "furong";
	char buf[1024] = {};
	
	sprintf(buf, "name=%s|i=%d|d=%f|", name, i, d);
	sprintf(buf, "%d", 123);
	printf("buf=%s\n", buf);
}

