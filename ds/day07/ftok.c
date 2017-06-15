#include <stdio.h>
#include <errno.h>
#include <sys/ipc.h>

int main( void )
{
	if ( ftok() == -1)
		perror("ftok");
}

