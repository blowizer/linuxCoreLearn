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
	pid_t pid;
	int   ret;
	int   connfd;
	int   listenfd;
	int op  = 1;
	socklen_t len;
	char  sendbuf[512] = {};
	char  recvbuf[512] = {};
	struct sockaddr_in addr;
	struct sockaddr_in caddr;
	
	bzero(&addr, sizeof(addr));
	bzero(&caddr, sizeof(caddr));
	
	if ( (listenfd = socket(PF_INET, SOCK_STREAM, 0)) == -1)
		ERR_EXIT("socket");
	
	addr.sin_family = AF_INET;
	addr.sin_port   = htons(10000);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	len = sizeof(addr);
	op = 1;
	setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR,  &op, sizeof(op));
	if ( bind(listenfd, (struct sockaddr*)&addr, len) == -1)
		ERR_EXIT("bind");
	
	if ( listen(listenfd, SOMAXCONN) == -1)
		ERR_EXIT("listen");
	
	len = sizeof(caddr);
	if ( (connfd = accept(listenfd, (struct sockaddr*)&caddr, &len)) == -1)
		ERR_EXIT("accept");
	
	if ( (pid=fork()) == -1)
		ERR_EXIT("fork");
	
	if ( pid == 0 ) {
		close(listenfd);
		for ( ; ; ) {
			bzero(recvbuf, sizeof(recvbuf));
			ret = read(connfd, recvbuf, sizeof(recvbuf));
			if ( ret == -1 ) {
				if ( errno == EINTR)
					continue;
				ERR_EXIT("read");
			} else if ( ret == 0 ) {
				printf("peer close!\n");
				break;
			}
			recvbuf[ret] = 0;
			printf("%s\n", recvbuf);
		}
		
		close(connfd);
		exit(EXIT_SUCCESS);
	}else {
		while ( fgets(sendbuf, sizeof(sendbuf), stdin) != NULL ) {
			if ( write(connfd, sendbuf, strlen(sendbuf)) == -1)
				ERR_EXIT("write");
			bzero(sendbuf, sizeof(sendbuf));
		}
		exit(EXIT_SUCCESS);
	}
	
	return 0;
}

