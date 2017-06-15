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

int main( int argc, char *argv[], char *envp[])
{
	printf("in main...%d\n", getpid());
	char *const argv2[] = {"main", "hahah", "hehe", NULL};
	//char *const envp[] = {"LL=furong",NULL};

	execve("./main", argv2, envp);

	printf("out main...\n");
	return 0;
}

