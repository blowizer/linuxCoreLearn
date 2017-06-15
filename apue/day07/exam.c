#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <time.h>

#define ERR_EXIT(m) \
	do { \
		fprintf(stderr, "[%s][%d]:%s %s\n", __FILE__, __LINE__, m, strerror(errno)); \
		exit(EXIT_FAILURE); \
	} while ( 0 )

int V = 0;
int X = 0;

void handler(int s) {
	if ( s == SIGALRM) {
		printf("\033[6;5Htime out!\n");
		printf("\033[7;5HV=%d, X=%d\n", V, X);
		printf("\033[0m");
		exit(EXIT_SUCCESS);
	} else if ( s == SIGINT) {
		printf("\033[0m\n");
		exit(EXIT_SUCCESS);
	}
}

int main( void )
{
	int i;
	int j;
	int left;
	int right;
	int ret;

	if ( signal(SIGALRM, handler) == SIG_ERR)
		ERR_EXIT("signal");
	if ( signal(SIGINT, handler) == SIG_ERR)
		ERR_EXIT("signal");
	alarm(20);
	
	system("clear");
	printf("   examp system");
	for (i=2; i<10; i++) {
		printf("\033[%d;%dH\033[35m\033[45mX", i,3);
		printf("\033[%d;%dH\033[35m\033[45mX", i,20);
	}
	for (i=0; i<20; i++) {
		printf("\033[%d;%dH\033[35m\033[45mX", 2, i);
		printf("\033[%d;%dH\033[35m\033[45mX", 10,i);
	}
	
	srand(time(NULL));
	for (i=0; i<10; i++) {
		left = rand() % 10;
		right = rand() % 10;
		
		printf("\033[0m");
		printf("\033[5;5H%d+%d=", left, right);
		scanf("%d", &ret);
		printf("\033[5;5H              ");
		if ( ret == left+right )
			V++;
		else 
			X++;
	}
	
	printf("\033[6;5H恭喜你，答完了!\n");
	printf("\033[7;5HV=%d, X=%d\n", V, X);
	printf("\033[0m");

	return 0;
}

