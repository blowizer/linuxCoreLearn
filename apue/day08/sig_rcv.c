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

void handler(int s, siginfo_t *info, void *cntx)
{
	printf("recv sig %d, data%d\n", s, info->si_value.sival_int);
}

int main( void )
{
	struct sigaction sa;
	sa.sa_sigaction = handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	
	sigaction(SIGINT, &sa, NULL);
	
	printf("pid=%d\n", getpid());
	for (;;)
		pause();

	return 0;
}

