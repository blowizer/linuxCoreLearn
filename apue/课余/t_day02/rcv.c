
#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/types.h>
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
	int connfd;
	int listenfd;
	int ret;

	socklen_t clilen;
	socklen_t len;

	char readbuf[1024]={};
	struct sockaddr_in addr;
	struct sockaddr_in cliaddr;

	memset(&addr,0x00,sizeof(addr));
	memset(&cliaddr,0x00,sizeof(cliaddr));
	
	//create socket 
	if( (listenfd=socket(PF_INET,SOCK_STREAM,0))==-1)
		ERR_EXIT("scoket");
	printf("socket success\n");
	
	addr.sin_family=AF_INET;
	addr.sin_port  =htons(6000);
	addr.sin_addr.s_addr=inet_addr("192.168.0.215");

	len=sizeof(addr);

	if(bind(listenfd,(struct sockaddr*)&addr,len)=-1)

		ERR_EXIT("bind");
	printf("bind success\n");
	
	if(listen(listenfd,SOMAXCONN)==-1)
		ERR_EXIT("listen");
	printf("listen success\n");	
	
	clilen=sizeof(cliaddr);
	connfd=accept(listenfd,(struct sockaddr *)&cliaddr, &clilen);
	if(connfd==-1)
		ERR_EXIT("accept");

	while(1){
		if( ret= read ( connfd , readbuf , sizeof ( readbuf ) ) == -1)
			ERR_EXIT("read");
		else if(ret==0){
			printf("cli close!\n");
			break;
		}
	}
	memset(readbuf,0x00,sizeof(readbuf));
	
	close(listenfd);
	close(connfd);	 
	
	return 0;
}
