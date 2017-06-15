#include <unistd.h>
#include <fcntl.h>
#include <sys/resource.h>

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
	struct rlimit rm;
	//if ( getrlimit(RLIMIT_NPROC, &rm) == -1)
	//	ERR_EXIT("getrlimit");
	//printf("rlim_cur:%d\n", rm.rlim_cur);
	//printf("rlim_max:%d\n", rm.rlim_max);
	printf("%d\n", sysconf(_SC_CHILD_MAX));
	return 0;
}

