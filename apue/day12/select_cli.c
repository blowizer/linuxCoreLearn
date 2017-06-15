/*
 * select用来管理多个I/O，如果其中一个或多个I/O检测到感兴趣的事件，select就返回
 * int select(int nfds, //监控的文件描述符的最大值+1
 * 		fd_set *readfds, //读文件描述符的集合，该参数即使输入也是输出
 * 						 // 输入：要监控的文件描述符的集合
 * 						 // 输出：有数据的文件描述符的集合
 * 		fd_set *writefds,
 * 		fd_set *exceptfds,
 * 		struct timeval *timeout); //指定阻塞时间，如果为NULL，表示永久
 * 								  //返回的是剩余的等待时间
 * 	返回值：
 * 		> 0 发生改变的文件描述符的个数
 * 		= 0 时间限制到
 * 		=-1 出错
 *
 * 		   void FD_CLR(int fd, fd_set *set);
 * 		   int  FD_ISSET(int fd, fd_set *set);
 * 		   void FD_SET(int fd, fd_set *set);
 *		   void FD_ZERO(fd_set *set);
 */
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

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
	int    ret;
	int    maxfd;
	fd_set rset;
	char sendbuf[1024];
	char recvbuf[1024];

	memset(sendbuf, 0x00, sizeof(sendbuf));
	memset(recvbuf, 0x00, sizeof(recvbuf));
	
	FD_ZERO(&rset);
	int fd_stdin = fileno(stdin);
	
	maxfd = fd_stdin > fd ? fd_stdin : fd;
	
	for ( ; ; ) {
		FD_SET(fd_stdin, &rset);
		FD_SET(fd, &rset);
		ret = select(maxfd+1, &rset, NULL, NULL, NULL);
		if ( ret == -1 ) {
			if ( errno == EINTR)
				continue;
			break;
		}
	
		if ( FD_ISSET(fd_stdin, &rset) ) {
			if ( fgets(sendbuf, 1024, stdin) == NULL)
				break;
			write(fd, sendbuf, strlen(sendbuf));
			memset(sendbuf, 0x00, sizeof(sendbuf));
		}
		
		if ( FD_ISSET(fd, &rset) ) {
			if ( (ret=read(fd, recvbuf, 1024)) == -1)
				ERR_EXIT("read");
			else if ( ret == 0 ) {
				printf("sever close!\n");
				break;
			}
			printf("%s", recvbuf);
			memset(recvbuf, 0x00, 1024);
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

