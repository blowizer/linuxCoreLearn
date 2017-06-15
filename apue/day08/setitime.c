#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <sys/time.h>

#define ERR_EXIT(m) \
	do { \
		fprintf(stderr, "[%s][%d]:%s %s\n", __FILE__, __LINE__, m, strerror(errno)); \
		exit(EXIT_FAILURE); \
	} while ( 0 )

void handler(int s) {
	printf("recv sig %d\n", s);
}

int main( void ) {
	struct sigaction act;
	struct itimerval it;

	it.it_value.tv_sec = 5;
	it.it_value.tv_usec = 0;
	it.it_interval.tv_sec = 1;
	it.it_interval.tv_usec = 0;

	act.sa_handler = handler;
	act.sa_flags = 0;
	sigemptyset(&act.sa_mask);

	if ( sigaction(SIGALRM, &act, NULL) == -1)
		ERR_EXIT("sigaction");
	
	setitimer(ITIMER_REAL, &it, NULL);
	
	for (; ; )
		pause();

	return 0;
}

