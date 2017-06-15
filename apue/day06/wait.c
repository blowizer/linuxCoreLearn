
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
	
	if ( (pid=fork()) == -1)
		ERR_EXIT("fork");
	
	if ( pid == 0) {
		sleep(2);
		printf("this is child! %d\n", getpid());
		//exit(100);
		abort();
	}

	int status;
	pid_t cid;
	cid = wait(&status);
	if ( cid == -1)
		ERR_EXIT("wait");
	printf("this is parent!cid=%d\n", cid);
	if ( WIFEXITED(status) )
		printf("status=%hhd\n", WEXITSTATUS(status));
		//(char)(((unsigned int)status)>>8));
	else if (WIFSIGNALED(status)) {
		printf("exit abnormal! %d\n", WTERMSIG(status));
	}

	return 0;
}

