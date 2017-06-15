#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define ERR_EXIT(m) \
do { \
	fprintf(stderr, "[%s][%d] %s %s\n", \
	 __FILE__,__LINE__, m, strerror(errno)); \
	exit(EXIT_FAILURE);\
} while ( 0 )

int main( void )
{
	int fd;
	struct sockaddr_in addr = {};
	
	if ( (fd=socket(PF_INET, SOCK_DGRAM, 0)) == -1)
		ERR_EXIT("socket");
	int op = 1;
	setsockopt(fd, SOL_SOCKET, SO_BINDTODEVICE, "eth0", 5); 
	addr.sin_family = AF_INET;
	addr.sin_port = htons(9898);
	inet_pton(AF_INET, "224.2.2.2", &addr.sin_addr);
	
	sendto(fd, "multi cast", strlen("multi cast"), 0, (struct sockaddr*)&addr, sizeof(addr));

	close(fd);
}

