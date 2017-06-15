
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

void handler(int s){
	printf("外部事件ing\n");
	sleep(2);
	
	printf("外部事件ing\n");
}

int main( void )
{
		int i;
		sigset_t sets;
	sigset_t setp;
	sigset_t setu;

	if(signal(SIGINT,handler)==SIG_ERR)
		ERR_EXIT("signal");
	sigemptyset(&sets);
	sigaddset(&sets,SIGINT);
	sigprocmask(SIG_BLOCK,&sets,NULL);
	
	for(i=0;i<10;i++){ 
	printf("拷贝电影%ding...\n",i+1);
	sleep(2);
	
	printf("拷贝电影%dover...\n",i+1);
	sigemptyset(&setp);
	sigemptyset(&setu);
	sigpending(&setu);
	
	if(sigismember(&setu,SIGINT))
			if(sigsuspend(&setp)==-1&&errno!=EINTR)
					ERR_EXIT("sigsuspend");
	}
	
	printf("拷贝电影%dover...\n",i+1);
		if(sigprocmask(SIG_UNBLOCK,&sets,NULL)==-1)
			ERR_EXIT("sigprocmask");
	return 0;
}

