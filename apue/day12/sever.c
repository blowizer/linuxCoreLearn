#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

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

void echo_sever(int connfd)
{
	struct packet buf;
	int len;
	int ret;
	while ( 1 ) {
		memset(&buf, 0x00, sizeof(buf));
		if ( (ret=readn(connfd, &len, 4)) == -1) ERR_EXIT("readn");
		if ( ret < 4 ) {
			printf("peer close!\n");
			break;
		}
		buf.len = ntohl(len);
		if ( readn(connfd, buf.buf, buf.len) == -1) ERR_EXIT("readn");
		writen(connfd, buf.buf, buf.len);
		memset(&buf, 0x00, sizeof(buf));
	}
}

void handler(int s)
{
	while (waitpid(-1, NULL, WNOHANG)> 0 )
		;
}

int main( void )
{
	pid_t pid;
	int connfd;
	int listenfd;
	struct sigaction sa;
	struct sockaddr_in addr;
	memset(&addr,0x00,sizeof(addr));

	if ( (listenfd = socket(PF_INET, SOCK_STREAM, 0)) == -1)
		ERR_EXIT("socket");
	
	//if ( signal(SIGCHLD, SIG_IGN) == SIG_ERR)
	//	ERR_EXIT("signal");
	sa.sa_handler = handler;
	sa.sa_flags   = 0;
	sigemptyset(&sa.sa_mask);
	if ( sigaction(SIGCHLD, &sa, NULL) == -1)
		ERR_EXIT("sigaction");

	int op = 1;
	setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &op, sizeof(op));
	addr.sin_family = AF_INET;
	addr.sin_port   = htons(9999);
	inet_pton(AF_INET, "192.168.0.200", &addr.sin_addr);
	if ( bind(listenfd, (struct sockaddr*)&addr, sizeof(addr)) == -1)
		ERR_EXIT("bind");
	
	if ( listen(listenfd, SOMAXCONN) == -1)
		ERR_EXIT("listen");
	
	while ( 1 ) {
		if ( (connfd=accept(listenfd, 0, 0)) == -1) {
			if ( errno == EINTR)
				continue;
			ERR_EXIT("accept");
		}

		if ( (pid=fork()) == -1 )ERR_EXIT("fork");
		if ( pid == 0 ) {
			close(listenfd);
			echo_sever(connfd);
			close(connfd);
			exit(EXIT_SUCCESS);
		} else if ( pid > 0 ){
			close(connfd);
		}
	}
	
	close(connfd);
	close(listenfd);

	return 0;
}

