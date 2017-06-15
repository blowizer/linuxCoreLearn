#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define ERR_EXIT(m) \
	do { \
		fprintf(stderr, "[%s][%d]:%s %s\n", __FILE__, __LINE__, m, strerror(errno)); \
		exit(EXIT_FAILURE); \
	} while ( 0 )

void set_flg(int fd, int flag) {
	int val;
	if ( (val = fcntl(fd, F_GETFL, 0)) == -1)
		ERR_EXIT("fcntl");
	if ( fcntl(fd, F_SETFL, flag|val) == -1)
		ERR_EXIT("fcntl");
}

void clr_flg(int fd, int flag){
	int val;
	if ( (val = fcntl(fd, F_GETFL, 0)) == -1)
		ERR_EXIT("fcntl");
	val &= ~flag;
	if ( fcntl(fd, F_SETFL, val) == -1)
		ERR_EXIT("fcntl");
}

int main( void )
{
	char buf[1024] = {};
	if ( read(0, buf, 1024) == -1)
		ERR_EXIT("read");

	printf("buf=%s\n", buf);
	
	/*
	int flags = fcntl(0, F_GETFL, 0);
	if ( flags == -1)
		ERR_EXIT("fcntl");
	
	if ( fcntl(0, F_SETFL, O_NONBLOCK|flags) == -1)
		ERR_EXIT("fcntl");
	*/
	set_flg(0, O_NONBLOCK);
	clr_flg(0, O_NONBLOCK);
	
	if ( read(0, buf, 1024) == -1) // EAGAIN
		ERR_EXIT("read");
	
	return 0;
}

