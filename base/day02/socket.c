#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/un.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


int main( void )
{
	int fd;
	struct sockaddr_un su;

	memset(&su, 0x00, sizeof(su));

	if ( (fd=socket(AF_UNIX, SOCK_STREAM,0))==-1)
		perror("sockaddr_uncket"),exit(-1);
	
	su.sun_family = AF_UNIX;
	memcpy(su.sun_path, "my.s", strlen("my.s"));
	bind(fd, (struct sockaddr*)&su, sizeof(su));
	
	return 0;
}

