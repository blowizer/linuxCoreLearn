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

__sighandler_t my_signal(int sig, __sighandler_t handler) {
	struct sigaction nact;
	struct sigaction oact;
	
	nact.sa_handler = handler;
	sigemptyset(&nact.sa_mask);
	nact.sa_flags = 0;
	
	if ( sigaction(sig, &nact, &oact) == -1)
		return SIG_ERR;
	
	return oact.sa_handler;
}

int main( void )
{
	struct sigaction sa;
	
	sa.sa_handler = handler;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGQUIT);
	sa.sa_flags = 0;
	
	if ( sigaction(SIGINT, &sa, NULL) == -1)
		ERR_EXIT("sigaction");
	signal(SIGINT, handler);

#if 0
	my_signal(SIGINT, handler);
#endif 
	
	for (; ; ) {
		pause();
	}

	return 0;
}

