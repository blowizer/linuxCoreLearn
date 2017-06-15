#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include<arpa/inet.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <signal.h>

#define ERR_EXIT(m) \
do { \
	fprintf(stderr, "[%s][%d] %s %s\n", \
	 __FILE__,__LINE__, m, strerror(errno)); \
	exit(EXIT_FAILURE);\
} while ( 0 )

int main( void )
{
	fd_set rset;
	fd_set allset;
	int    i;
	int    maxfd;
	int    connfd;
	int    nready;
	int    listenfd;
	int    maxi = 0;
	char   recvbuf[1024];
	int client[FD_SETSIZE];
	struct sockaddr_in addr;
	
	for (i=0; i<FD_SETSIZE; i++)
		client[i] = -1;
	
	if ( (listenfd=socket(PF_INET, SOCK_STREAM, 0)) == -1)
		ERR_EXIT("socket");
	addr.sin_family = AF_INET;
	addr.sin_port   = htons(9999);
	inet_aton("192.168.0.200", &addr.sin_addr);
	int op = 1;
	signal(SIGPIPE, SIG_IGN);
	setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &op, sizeof(op));
	if ( bind(listenfd, (struct sockaddr*)&addr, sizeof(addr)) == -1)
		ERR_EXIT("bind");
	if ( listen(listenfd, SOMAXCONN) == -1)
		ERR_EXIT("listen");
	
	FD_ZERO(&rset);
	FD_ZERO(&allset);
	FD_SET(listenfd, &allset);
	maxfd = listenfd;
	
	for ( ; ; ) {
		rset = allset;
		nready = select(maxfd+1, &rset, NULL, NULL, NULL);
		if ( nready == -1 ) {
			if ( errno == EINTR) continue;
			ERR_EXIT("select");
		}
	
		if ( FD_ISSET(listenfd, &rset) ) {
			connfd = accept(listenfd, NULL, NULL);
			for (i=0; i<FD_SETSIZE; i++ ) {
				if ( client[i] == -1) {
					client[i] = connfd;
					if ( i > maxi ) maxi = i;
					break;
				}
			}
			if ( i == FD_SETSIZE ) {
				printf("too many clients!\n");
				ERR_EXIT("accept");
			}
			FD_SET(connfd, &allset);
			if ( connfd > maxfd)
					maxfd = connfd;
			if ( --nready <= 0 ) {
				continue;
			}
		}
	
		for (i=0; i<=maxi; i++) {
			connfd = client[i];
			if ( connfd == -1)
				continue;
			if ( FD_ISSET(connfd, &rset) ) {
				memset(&recvbuf, 0x00, sizeof(recvbuf));
				int ret = read(connfd, recvbuf, 1024);
				if ( ret == 0 ) {
					printf("client close!\n");
					client[i] = -1;
					FD_CLR(connfd, &allset);
				}
				
				write(connfd, recvbuf, strlen(recvbuf));
				if ( --nready <= 0)
					break;
			}
		}
	}
	
	close(listenfd);
}

