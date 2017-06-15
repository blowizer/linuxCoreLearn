
#include <unistd.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <sys/socket.h>
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
	int fd;
	socklen_t  len;
	char sendbuf[1024]={};
	char recvbuf[1024]={};
	struct  sockaddr_in addr;
	
	memset(&addr,0x00,sizeof(addr));
	
	if( (fd=socket(PF_INET,SOCK_STREAM,0))==-1)
		ERR_EXIT("socket");
	
	addr.sin_family=AF_INET;
	addr.sin_port=htons(10000);
	addr.sin_addr.s_addr=inet_addr("192.168.0.205");
	
	len=sizeof(addr);
	if( connect( fd ,( struct sockaddr *)&addr,len)==-1)
		ERR_EXIT("connect");	
	
	while(fgets(sendbuf,1024,stdin)!=NULL){
		
		if(write(fd,sendbuf,strlen(sendbuf))==-1)
			ERR_EXIT("wirte");
		if(read(fd,recvbuf,1024)==-1)
			ERR_EXIT("read");
		fputs(recvbuf,stdout);
		memset(recvbuf,0x00,sizeof(recvbuf));
		memset(sendbuf,0x00,sizeof(sendbuf));
	}
	return 0;
}
	
