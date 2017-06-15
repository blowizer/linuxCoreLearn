
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
	printf("/");
	fflush(stdout);
	alarm(1);
}
int main( void )
{
	signal(SIGALRM,handler);
	alarm(1);
	for(; ;)
	pause();
	
	return 0;
}

