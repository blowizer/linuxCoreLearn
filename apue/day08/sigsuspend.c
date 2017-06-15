#include <unistd.h>
#include <fcntl.h>

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

void handler(int s)
{
	printf("recv sig %d\n", s);
	sleep(5);
}

int main( void )
{
	sigset_t set;
	
	signal(SIGINT, handler);

	sigemptyset(&set);	
	//sigaddset(&set, SIGINT);
	
	printf("before!\n");
	sigsuspend(&set);
	printf("after!\n");

	return 0;
}


