
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
int sig_int_flag=0;
void sig_int(){
//	signal(SIGINT,sig_int);
	sig_int_flag =1;
}
int main( void )
{
	
	printf("input signal\n");
	
	signal(SIGINT,sig_int);
	while(sig_int_flag==0)
	{
	printf("hehe");
	pause();
		
	}
	return 0;
}

