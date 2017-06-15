#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
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

void do_echo(int connfd)
{
	int ret;
	char buf[1024] = {};
	
	for ( ; ; ) {
		ret = read(connfd, buf, sizeof(buf));
		if ( ret == -1 )
			ERR_EXIT("read");
		else if ( ret == 0 ) {
			printf("cli close!\n");
			exit(EXIT_SUCCESS);
		}
		if ( write(connfd, buf, ret) == -1)
			ERR_EXIT("write");
	}
}

int main( void )
{
	int connfd;
	int listenfd;
	socklen_t len;
	struct sockaddr_in saddr;
	struct sockaddr_in caddr;

	memset(&saddr, 0x00, sizeof(saddr));
	memset(&caddr, 0x00, sizeof(caddr));

	if ( (listenfd=socket(PF_INET, SOCK_STREAM, 0)) == -1)
		ERR_EXIT("socket");
	
	saddr.sin_family = AF_INET;
	saddr.sin_port   = htons(10000);
	inet_aton("192.168.0.205", &saddr.sin_addr);
	len = sizeof(saddr);
	if ( bind(listenfd, (struct sockaddr*)&saddr, len) == -1)
		ERR_EXIT("bind");
	
	if ( listen(listenfd, SOMAXCONN) == -1)
		ERR_EXIT("listen");
	
	len = sizeof(caddr);
	connfd = accept(listenfd, (struct sockaddr*)&caddr, &len);
	if ( connfd == -1 ) ERR_EXIT("accept");
	
	do_echo(connfd);
	
	close(connfd);
	close(listenfd);

	return 0;
}


