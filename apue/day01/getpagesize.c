#include <stdio.h>

#include <unistd.h>

int main( void )
{
	int i = getpagesize();
	
	printf("i=%d\n", i);
}

