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

void handler(int s) {
	printf("外部事件开始处理....\n");
	sleep(3);
	printf("外部事件处理完毕\n");
}

int main( void ) {
	int i;
	sigset_t sets; //屏蔽的信号
	sigset_t setp; //suspend
	sigset_t setu; //未决信号集
	
	if ( signal(SIGINT, handler) == SIG_ERR)
		ERR_EXIT("signal");
	sigemptyset(&sets);
	sigaddset(&sets, SIGINT);

	if ( sigprocmask(SIG_BLOCK, &sets, NULL) == -1)
		ERR_EXIT("sigprocmask");

	for (i=0; i<10; i++) {
		printf("正在拷贝电影%d集...\n", i+1);
		sleep(5);
		printf("电影%d集拷贝完毕!\n", i+1);
		sigemptyset(&setp);
		sigemptyset(&setu);

		if ( sigpending(&setu) == -1)
			ERR_EXIT("sigpending");
		if ( sigismember(&setu, SIGINT) )
			if ( sigsuspend(&setp)==-1 && errno!=EINTR )
				ERR_EXIT("sigsuspend");
	}
	
	printf("电影全部拷贝完毕!\n");

	if ( sigprocmask(SIG_UNBLOCK, &sets, NULL) == -1 )
		ERR_EXIT("sigprocmask");
	
	return 0;
}

