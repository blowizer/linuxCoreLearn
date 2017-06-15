#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <signal.h>

#define ERR_EXIT(m) \
	do { \
		fprintf(stderr, "[%s][%d]:%s %s\n", __FILE__, __LINE__, m, strerror(errno)); \
		exit(EXIT_FAILURE); \
	} while ( 0 )

int  connfd;
int  listenfd;
void handler(int s)
{
	char buf[1024];
	if ( s == SIGURG ) {
		memset(buf, 0x00, sizeof(buf));
		recv(connfd, buf, 1024, MSG_OOB);
		printf("oob:%s\n", buf);
	}
}

int main( void )
{
	int  ret;
	char buf[1024];
	struct sockaddr_in addr;
	
	if ( (listenfd = socket(PF_INET, SOCK_STREAM, 0)) == -1 )
		ERR_EXIT("socket");
	
	addr.sin_family = AF_INET;
	addr.sin_port   = htons(9999);
	inet_aton("127.0.0.1", &addr.sin_addr);
	int op = 1;
	
	struct sigaction sa;
	sa.sa_handler = handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if ( sigaction(SIGURG, &sa, NULL) == -1)
		ERR_EXIT("sigaction");
	
	setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &op, sizeof(op));
	if ( bind(listenfd, (struct sockaddr*)&addr, sizeof(addr)) == -1)
		ERR_EXIT("bind");
	if ( listen(listenfd, SOMAXCONN) == -1)
		ERR_EXIT("listen");
	
	if ( (connfd = accept(listenfd, NULL, NULL)) == -1)
		ERR_EXIT("accept");
	fcntl(connfd, F_SETOWN, getpid());
	while ( 1 ) {
		memset(buf, 0x00, sizeof(buf));
		recv(connfd, buf, 1024, 0);
		printf("%s\n", buf);
	}

	close(connfd);
	close(listenfd);
}

