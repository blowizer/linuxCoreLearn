#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <poll.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define ERR_EXIT(m) \
do { \
	fprintf(stderr, "[%s][%d] %s %s\n", \
	 __FILE__,__LINE__, m, strerror(errno)); \
	exit(EXIT_FAILURE);\
} while ( 0 )

void echo_cli(int fd)
{
	int  ret;
	char sendbuf[1024];
	char recvbuf[1024];
	struct pollfd fds[2];
	int fd_stdin  = fileno(stdin);
	fds[0].fd     = fd_stdin;
	fds[0].events = POLLIN;
	fds[1].fd     = fd;
	fds[1].events = POLLIN;
	
	while ( 1 ) {
		if ( poll(fds, 2, -1) == -1)
			ERR_EXIT("poll");
		if ( fds[0].revents & POLLIN ) {
			memset(sendbuf, 0x00, sizeof(sendbuf));
			if ( fgets(sendbuf, 1024, stdin) == NULL)
				break;
			write(fd, sendbuf, strlen(sendbuf));
		}
		
		if ( fds[1].revents & POLLIN ) {
			bzero(recvbuf, sizeof(recvbuf));
			if ( (ret=read(fd, recvbuf, 1024)) == -1)
				ERR_EXIT("read");
			else if ( ret == 0 ){
				printf("sever close!\n");
				break;
			}
			printf("%s", recvbuf);
		}
	}
}

int main( void )
{
	int  fd;
	struct sockaddr_in addr;
	
	memset(&addr, 0x00, sizeof(addr));
	
	if ( (fd=socket(PF_INET, SOCK_STREAM, 0)) == -1)
		ERR_EXIT("socket");
	addr.sin_family = AF_INET;
	addr.sin_port   = htons(9999);
	inet_aton("192.168.0.200", &addr.sin_addr);
	if ( connect(fd, (struct sockaddr*)&addr, sizeof(addr)) == -1)
		ERR_EXIT("connect");

	echo_cli(fd);
	
	close(fd);
}

