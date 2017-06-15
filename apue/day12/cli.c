#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <signal.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define ERR_EXIT(m) \
	do { \
		fprintf(stderr, "[%s][%d]:%s %s\n", __FILE__, __LINE__, m, strerror(errno)); \
		exit(EXIT_FAILURE); \
	} while ( 0 )

ssize_t readn(int fd, void *buf, size_t count)
{
	size_t nleft = count;
	size_t nread;
	char *bufp = (char *)buf;

	while ( nleft > 0 ) {
		if ( (nread=read(fd, bufp, nleft)) == -1) {
			if ( errno == EINTR) continue;
			return -1;
		}
		else if ( nread == 0 )
			return count-nleft;
		bufp += nread;
		nleft -= nread;
	}
	
	return count;
}

ssize_t writen(int fd, const void *buf, size_t count)
{
	size_t nleft = count;
	size_t nwritten;
	char *bufp = (char*)buf;

	while ( nleft > 0 ) {
		if ( (nwritten=write(fd, bufp, nleft)) == -1 ) {
			if ( errno == EINTR) continue;
			return -1;
		} else if ( nwritten == 0 )
			continue;
		bufp  += nwritten;
		nleft -= nwritten;
	}
	
	return count;
}

struct packet {
	int len;
	char buf[1024];
};

void echo_cli(int cfd)
{
	struct packet buf;
	int ret;
	int len;
	memset(&buf, 0x00, sizeof(buf));
	while ( fgets(buf.buf, 1024, stdin) != NULL ) {
		len = strlen(buf.buf);
		buf.len = htonl(len);
		if ( (ret=writen(cfd, &(buf.len), 4)) == -1) ERR_EXIT("writen");
		if ( (ret=writen(cfd, buf.buf, len)) == -1) ERR_EXIT("writen");
		if ( (ret=readn(cfd, buf.buf, len)) == -1) {
			ERR_EXIT("readn");
		} else if ( ret == 0 ) {
			printf("serv close!\n");
		}
		printf("%s\n", buf.buf);
		memset(&buf, 0x00, sizeof(buf));
	}
	printf("peer close!\n");
}

void handler(int sig)
{
	printf("recv %d\n", sig);
}

int main( void )
{
	int i;
	int cfd[5];
	struct sockaddr_in addr;
	struct sigaction sa;
	sa.sa_handler = SIG_IGN;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	
	if ( sigaction(SIGPIPE, &sa, NULL) == -1)
		ERR_EXIT("sigaction");
	
	memset(&addr, 0x00, sizeof(addr));
	
	for (i=0; i<5; i++) {
		if ( (cfd[i]=socket(PF_INET, SOCK_STREAM, 0)) == -1)
			ERR_EXIT("socket");
		addr.sin_family = AF_INET;
		addr.sin_port   = htons(9999);
		inet_aton("192.168.0.200", &addr.sin_addr);
		if ( connect(cfd[i], (struct sockaddr*)&addr, sizeof(addr)) == -1)
			ERR_EXIT("connect");
	}
	
	echo_cli(cfd[0]);
	close(cfd[0]);
}

