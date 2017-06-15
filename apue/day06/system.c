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
	char buf[1024] = {};
	while ( 1 ) {
		memset(buf, 0x00, sizeof(buf));
	
		printf("NB > ");
		fflush(stdout);
		fgets(buf, 1024, stdin);
		
		system(buf);
	}

	return 0;
}

