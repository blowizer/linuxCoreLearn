
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include<signal.h>
#define ERR_EXIT(m) \
	do { \
		fprintf(stderr, "[%s][%d]:%s %s\n", __FILE__, __LINE__, m, strerror(errno)); \
		exit(EXIT_FAILURE); \
	} while ( 0 )

void handler(int s)
{
	printf("recv sig %d\n",s);
	
}
int main( void )
{
	sigset_t sig;
	int i;
	int sum=0;
	signal(SIGINT,handler);
	
	sigemptyset(&sig);

	sigaddset(&sig,SIGINT);
	sigprcmask(SIG_BLOCK,&sig,NULL);
	for(i=0;i<5;i++){
		sum+=i;
		sleep(1);
	}
	printf("sum=%d\n",sum);
	sigprcmask(SIG_UNBLOCK,&sig,NULL);
	printf("finsh\n");
	return 0;
}

