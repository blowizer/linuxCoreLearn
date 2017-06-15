#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <termios.h>

#define ERR_EXIT(m) \
	do { \
		fprintf(stderr, "[%s][%d]:%s %s\n", __FILE__, __LINE__, m, strerror(errno)); \
		exit(EXIT_FAILURE); \
	} while ( 0 )

int main( void )
{
	struct winsize w;
	
	while ( 1 ) {
		ioctl(STDIN_FILENO, TIOCGWINSZ, &w);
		printf("width:%d, high:%d\n",
			w.ws_col, w.ws_row);
		sleep(1);
	}
	
	return 0;
}

