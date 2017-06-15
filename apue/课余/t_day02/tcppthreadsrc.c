#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>
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
do_service(void *arg)
{	
	int ret;	
	char readbuf[1024] = {};	
	int connfd;
	connfd=(int *)arg;
	while ( 1 ) {
		if ( (ret=read(connfd, readbuf, sizeof(readbuf))) == -1)
			ERR_EXIT("read");
		else if ( ret == 0 ) {
			printf("cli close!\n");
			break;
		}
		printf("%s\n",readbuf);
		memset(readbuf, 0x00, sizeof(readbuf));
	}
}	
void *route(void *arg)
{
	pthread_detach(pthread_self());
	int connfd=*((int *)arg);
	free(arg);
	do_service(connfd);
}	
int main( void )
{
	int connfd;
	int listenfd;
	socklen_t  len;
	socklen_t  clilen;

	struct sockaddr_in addr;
	struct sockaddr_in cliaddr;

	memset(&addr, 0x00, sizeof(addr));
	memset(&cliaddr, 0x00, sizeof(cliaddr));

	// 1. 创建socket
	if ( (listenfd=socket(PF_INET, SOCK_STREAM, 0)) == -1)
		ERR_EXIT("socket");
	printf("create socket success!\n");
	
	addr.sin_family = AF_INET;
	addr.sin_port   = htons(5188);
	addr.sin_addr.s_addr = inet_addr("192.168.0.205");
	len = sizeof(addr);
	// 2.绑定套接字
	if ( bind(listenfd, (struct sockaddr*)&addr, len) == -1)
		ERR_EXIT("bind");
	printf("bind success!\n");

	len = sizeof(addr);
	// 3.设置为监听套接字
	if ( listen(listenfd, SOMAXCONN) == -1)
		ERR_EXIT("listen");
	printf("set listen success!\n");
	
	// 4.等待客户端连接
	while(1){
	pthread_t tid;
	if(tid=pthread_create(&tid,NULL,route,NULL)==-1)
		ERR_EXIT("pthread_create");
	clilen = sizeof(cliaddr);
	connfd=accept(listenfd, NULL, &clilen);
	if ( connfd == -1) ERR_EXIT("accept");
	printf("%s on line!\n", inet_ntoa(cliaddr.sin_addr));
	}
	close(connfd);
	
	return 0;
}

