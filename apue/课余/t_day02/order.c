#include <stdio.h>
#include <arpa/inet.h>

int main( void )
{
	unsigned a = 0X12345678;
	unsigned char *p = (unsigned char*)&a;
	
	printf("%X %X %X %X\n", p[0], p[1], p[2], p[3]);
	a = htonl(a);
	p = (unsigned char *)&a;
	printf("%X %X %X %X\n", p[0], p[1], p[2], p[3]);
}

