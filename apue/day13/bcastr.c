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
	char buf[1024] = {};
	struct sockaddr_in addr = {};
	struct sockaddr_in caddr = {};
	
	if ( (fd=socket(PF_INET, SOCK_DGRAM, 0)) == -1)
		ERR_EXIT("socket");
	int op = 1;
	setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &op, sizeof(op));
	
	addr.sin_family = AF_INET;
	addr.sin_port = htons(9898);
	inet_pton(AF_INET, "192.168.0.255", &addr.sin_addr);
	if ( bind(fd, (struct sockaddr*)&addr, sizeof(addr)) == -1)
		ERR_EXIT("bind");
	
	socklen_t len = sizeof(caddr);
	recvfrom(fd, buf, 1024, 0, (struct sockaddr*)&caddr, &len);
	printf("%s:buf=%s\n", inet_ntoa(caddr.sin_addr), buf);

	close(fd);
}

