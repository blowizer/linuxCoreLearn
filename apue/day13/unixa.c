#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int main( void )
{
	int fd;
	int connfd;
	char buf[1024] = {};
	struct sockaddr_un su = {};

	fd = socket(AF_UNIX, SOCK_STREAM, 0);
	if ( fd == -1 ) 
		perror("socket"),exit(-1);
	
	su.sun_family = AF_UNIX;
	strcpy(su.sun_path, "my.s");
	if ( bind(fd, (struct sockaddr*)&su, sizeof(su)) == -1)
		perror("bind"),exit(-1);
	if ( listen(fd, 10) == -1)
		perror("listen"),exit(-1);
	connfd = accept(fd, NULL, NULL);
	if ( connfd == -1)
		perror("accept"),exit(-1);
	read(connfd, buf, 1024);
	printf("%s\n", buf);
	
	close(fd);
	close(connfd);
}

