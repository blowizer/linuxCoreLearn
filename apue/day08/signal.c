
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
	if(s==SIGINT)
	{
		printf( "rec sig is%d:\n",s);
	
	}else if(s==SIGQUIT)
	{
		sigset_t bset;
		sigemptyset(&bset);
		sigaddset(&bset,SIGINT);
		if(sigprocmask(SIG_UNBLOCK,&bset,NULL)==-1)
			ERR_EXIT("sigpromask");
	}
}
int print(sigset_t *ret){
	int i;
	for(i=1;i<NSIG;i++)
	{
		if(sigismember(ret,i))
		putchar('1');
		else
		putchar('0');
	}
	printf("\n");
}
int main( void )
{
	signal(SIGINT,handler);
	signal(SIGQUIT, handler);
	sigset_t bset;
	sigset_t pset;
	
	sigemptyset(&bset);
	sigaddset(&bset,SIGINT);
	
	if(sigprocmask(SIG_BLOCK,&bset,NULL)==-1)
		ERR_EXIT("sigpromask");

	for(; ;){
			sigemptyset(&pset);
			sigpending(&pset);
			print(&pset);
			sleep(1);
	}
	return 0;
}

