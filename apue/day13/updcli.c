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
	socklen_t len;
	char buf[1024] = {};
	struct sockaddr_in addr = {};
	
	if ( (fd=socket(PF_INET, SOCK_DGRAM, 0)) == -1)
		ERR_EXIT("socket");
	
	addr.sin_family = AF_INET;
	addr.sin_port   = htons(9999);
	inet_aton("192.168.0.200", &addr.sin_addr);
	len = sizeof(addr);
	while ( fgets(buf, 1024, stdin) != NULL ) {
		sendto(fd, buf, sizeof(buf), 0, (struct sockaddr*)&addr, len);
		memset(buf, 0x00, sizeof(buf));
		recvfrom(fd, buf, sizeof(buf), 0, NULL, NULL);
		printf("%s", buf);
		memset(buf, 0x00, sizeof(buf));
	}
}

