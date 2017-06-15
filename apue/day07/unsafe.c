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

typedef struct {int a; int b;}TEST;
TEST g_data;

void unsafe()
{
	printf("a=%d,b=%d\n", g_data.a, g_data.b);
}

void handler(int s)
{
	unsafe();
	alarm(1);
}

int main( void )
{
	TEST zeros = {0,0};
	TEST ones  = {1,1};
	
	if ( signal(SIGALRM, handler) == SIG_ERR)
		ERR_EXIT("signal");
	
	g_data = zeros;
	
	alarm(1);
	for (; ; ) {
		g_data = zeros;
		g_data = ones;
	}
	
	return 0;
}

