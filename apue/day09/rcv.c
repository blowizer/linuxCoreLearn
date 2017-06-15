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

void print(sigset_t *ret)
{
    int i;
    for (i=1; i<NSIG; i++) {
        if ( sigismember(ret, i) )
            putchar('1');
        else
            putchar('0');
    }   
    printf("\n");
}

void handler(int s)
{
	if ( s == SIGINT )
		printf("recv sig %d\n", s);
	else if ( s == SIGRTMIN )
		printf("recv sig %d\n", s);
	else if ( s == SIGUSR1 ) {
		sigset_t set;
		sigemptyset(&set);
		sigaddset(&set, SIGINT);
		sigaddset(&set, SIGRTMIN);
		if ( sigprocmask(SIG_UNBLOCK, &set, NULL) == -1)
			ERR_EXIT("sigprocmask");
		if ( sigprocmask(SIG_UNBLOCK, &set, NULL) == -1)
			ERR_EXIT("sigprocmask");
	}
}

int main( void )
{
	sigset_t set;
	struct sigaction act;
	
	sigemptyset(&set);
	sigaddset(&set, SIGINT);
	sigaddset(&set, SIGRTMIN);

	act.sa_handler = handler;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;

	if ( sigaction(SIGINT, &act, NULL) == -1)
		ERR_EXIT("sigaction");
	if ( sigaction(SIGRTMIN, &act, NULL) == -1)
		ERR_EXIT("sigaction");
	if ( sigaction(SIGUSR1, &act, NULL) == -1)
		ERR_EXIT("sigaction");
	
	if ( sigprocmask(SIG_BLOCK, &set, NULL) == -1)
		ERR_EXIT("sigprocmask");
	
	for ( ; ; ) {
		sigset_t pset;
		sleep(1);
		sigemptyset(&pset);
        sigpending(&pset);
        print(&pset);
	}
	
	return 0;
}

