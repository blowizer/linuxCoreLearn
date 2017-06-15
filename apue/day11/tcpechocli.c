#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define ERR_EXIT(m) \
	do { \
		fprintf(stderr, "[%s][%d]:%s %s\n", __FILE__, __LINE__, m, strerror(errno)); \
		exit(EXIT_FAILURE); \
	} while ( 0 )

int main( void )
{
	int connfd;
	socklen_t len;
	struct sockaddr_in addr;
	char buf[1024] = {};
	
	memset(&addr, 0x00, sizeof(addr));
	
	if ( (connfd=socket(PF_INET, SOCK_STREAM, 0)) == -1)
		ERR_EXIT("socket");
	
	addr.sin_family = AF_INET;
	addr.sin_port   = htons(5188);
	inet_aton("192.168.0.200", &addr.sin_addr);
	len = sizeof(addr);
	if ( connect(connfd, (struct sockaddr*)&addr, len) == -1)
		ERR_EXIT("connect");
	
	while ( fgets(buf, 1024, stdin) != NULL ) {
		if ( write(connfd, buf, strlen(buf)) == -1)
			ERR_EXIT("write");
		memset(buf, 0x00, sizeof(buf));
	}

	close(connfd);
	return 0;
}

