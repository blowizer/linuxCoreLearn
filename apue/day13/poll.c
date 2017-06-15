#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <poll.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#if 0
int poll(struct pollfd *fds, //监控的文件描述符的集合
 		nfds_t nfds, // 监控的文件描述符的个数
		int timeout); // 超时时间 -1表示永久阻塞

struct pollfd {
	int   fd;         /* file descriptor */
	short events;     /* requested events */
	short revents;    /* returned events */
};
#endif

int main( void )
{
	int ret;
	char buf[1024] = {};
	struct pollfd fds[1];
	fds[0].fd = 0;
	fds[0].events = POLLIN;
	
	
	while ( 1 ) {
		ret = poll(fds, 1, -1);
		if ( ret == -1 )
			perror("poll"),exit(1);
		if ( fds[0].revents & POLLIN ) {
			printf("有数据到达!\n");
			ret = read(0, buf, 1024);
			printf("%s\n", buf);
			memset(buf, 0x00, sizeof(buf));
		}
	}
	return 0;
}

