#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

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
	int   fd;
	int   ret;
	pid_t pid;
	socklen_t len;
	char sendbuf[512] = {};
	char recvbuf[512] = {};
	struct sockaddr_in addr;
	
	bzero(&addr, sizeof(addr));
	
	if ( (fd=socket(PF_INET, SOCK_STREAM, 0)) == -1)
		ERR_EXIT("socket");
	
	addr.sin_family = AF_INET;
	addr.sin_port   = htons(10000);
	inet_pton(AF_INET, "192.168.0.200", &addr.sin_addr);
	len = sizeof(addr);
	if ( connect(fd, (struct sockaddr*)&addr, len) == -1)
		ERR_EXIT("connect");
	
	if ((pid=fork()) == -1)
		ERR_EXIT("fork");
	if ( pid == 0 ) {
		for ( ; ; ) {
			ret = read(fd, recvbuf, sizeof(recvbuf));
			if ( ret == -1)
				ERR_EXIT("read");
			if ( ret == 0 ) {
				printf("peer close!\n");
				break;
			}
			recvbuf[ret] = 0;
			printf("%s\n", recvbuf);
			bzero(recvbuf, sizeof(recvbuf));
		}
		close(fd);
		exit(EXIT_SUCCESS);
	} else {
		while ( fgets(sendbuf, 512, stdin) != NULL ){
			if ( write(fd, sendbuf, strlen(sendbuf)) == -1)
				ERR_EXIT("write");
		}
		close(fd);
		exit(EXIT_SUCCESS);
	}

	return 0;
}

