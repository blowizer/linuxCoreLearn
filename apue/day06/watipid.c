
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define ERR_EXIT(m) \
	do { \
		fprintf(stderr, "[%s][%d]:%s %s\n", __FILE__, __LINE__, m, strerror(errno)); \
		exit(EXIT_FAILURE); \
	} while ( 0 )

int main( void )
{
	pid_t pid;
	int ret;
	if((pid=fork())==-1)
		ERR_EXIT("fork");
	if(pid==0){
		printf("i am a chile process\n");
		sleep(2);
	}else{
	if(-1==(ret=waitpid(-1,NULL,0)))	
		ERR_EXIT("waitpid");
		printf("i am a parent process");
	}
	
	return 0;
}

