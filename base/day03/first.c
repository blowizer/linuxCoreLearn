#include <stdio.h>
#include <signal.h>

void handler(int s)
{
}

int main( void )
{
	signal(SIGINT, handler);
	signal(15, handler);
	while ( 1 )
		;
	return 0;
}

