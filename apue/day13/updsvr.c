#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#define ERR_EXIT(m) \
	do { \
		fprintf(stderr, "[%s][%d]:%s %s\n", __FILE__, __LINE__, m, strerror(errno)); \
		exit(EXIT_FAILURE); \
	} while ( 0 )


int main( void )
{
	int fd;
	int ret;
	char buf[1024];
	socklen_t len;
	struct sockaddr_in addr = {};
	struct sockaddr_in caddr = {};
	
	if ( (fd=socket(PF_INET, SOCK_DGRAM, 0)) == -1)
		ERR_EXIT("socket");
	
	addr.sin_family = AF_INET;
	addr.sin_port   = htons(9999);
	inet_aton("192.168.0.200", &addr.sin_addr);
	if ( bind(fd, (struct sockaddr*)&addr, sizeof(addr)) == -1)
		ERR_EXIT("bind");
	printf("bind!\n");
	len = sizeof(caddr);
	while ( 1 ) {
		if ( (ret=recvfrom(fd, buf, sizeof(buf), 0, 
			(struct sockaddr*)&caddr, &len)) == -1)
			ERR_EXIT("recvfrom");
		else if ( ret > 0 ) {
			printf("%s", buf);
			sendto(fd, buf, ret, 0, (struct sockaddr*)&caddr, len);
		}
	}
}

