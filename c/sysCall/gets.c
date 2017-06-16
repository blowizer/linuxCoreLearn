#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main( void )
{
	char buf[1024] = {};
	
	//gets(buf);//丢弃\n
	fgets(buf, 1024, stdin);//不丢弃\n
	int n = strlen(buf);
	//printf("len=%d,buf=%s\n", n, buf);
	buf[n-1] = 0;
	puts(buf);//自动加\n
	//fputs(buf, stdout);
}

