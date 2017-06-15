#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main( void )
{
	int fd = fileno(stdout);
	printf("before!\n");
	close(fd);
	printf("after!\n");
}

