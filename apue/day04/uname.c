#include <unistd.h>
#include <fcntl.h>
#include <sys/utsname.h>

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
	char str[64] = {};
	struct utsname buf;
	if ( uname(&buf) == -1)
		ERR_EXIT("uname");

	printf("sysname:%s\n", buf.sysname);
	printf("nodename:%s\n", buf.nodename);
	printf("release:%s\n", buf.release);
	printf("version:%s\n", buf.version);
	printf("machine:%s\n", buf.machine);

	gethostname(str, 64);
	printf("hostname:%s\n", str);

	return 0;
}

