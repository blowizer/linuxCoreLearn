
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
	wait(NULL,WNOWAIT);
}
int main( void )
{	
	struct sigaction sa;
	sa.sa_handler=handler;
	
	sigemptyset(&sa.sa_mask);	
	sa.sa_flags=0;
	if(sigaction(SIGCHLD,&sa,NULL)==-1)
		ERR_EXIT("sigaction");
	
	pid_t pid;
	
	if(-1==(pid=fork()))
			ERR_EXIT("fork");
	if(pid==0)
	{
		printf(".");
		fflush(stdout);
		sleep(1);
	}
	else
		for(; ;){
		printf("$");
		fflush(stdout);
		sleep(1);
	
	}

	return 0;
}
