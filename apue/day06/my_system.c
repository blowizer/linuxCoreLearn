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

int my_system(const char * cmd) {
	int status = -1;
	pid_t pid;

	if ( cmd == NULL )
		return -1;
	
	if ( (pid=fork()) == -1)
		status = -1;
	if ( pid == 0 ) {
		if ( execl("/bin/sh", "sh", "-c", cmd, NULL) == -1 )
			_exit(127);
	} else if ( pid > 0 ) {
		while ( waitpid(pid, &status, 0) == -1) {
			if ( errno == EINTR )
				continue;
			status = -1;
			break;
		}
	}
	
	return status;
}

int main( void )
{
	char buf[1024] = {};
	
	while ( 1 ) {
		printf("> ");
		fflush(stdout);
		fgets(buf, 1024, stdin);
		if ( memcmp(buf, "exit", 4) == 0)
			exit(0);
		my_system(buf);
		memset(buf, 0x00, sizeof(buf));
	}
	return 0;
}

