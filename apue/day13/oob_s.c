#include <unistd.h>
#include <sys/socket.h>
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
	int fd;
	char buf[1024] = {};
	struct sockaddr_in addr;
	
	if ( (fd=socket(PF_INET, SOCK_STREAM, 0)) == -1)
		ERR_EXIT("socket");
	
	addr.sin_family = AF_INET;
	addr.sin_port   = htons(9999);
	inet_aton("127.0.0.1", &addr.sin_addr);
	if ( connect(fd, (struct sockaddr*)&addr, sizeof(addr)) == -1)
		ERR_EXIT("connect");
	
	while ( 1 ) {
		send(fd, "hehe", 4, MSG_OOB);
		memset(buf, 0x00, sizeof(buf));
		sleep(1);
	}
	
	close(fd);
	
	return 0;
}

