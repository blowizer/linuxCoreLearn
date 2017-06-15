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

void set_flg(int fd, int flag)
{
	int flags;
	if ( (flags=fcntl(fd, F_GETFL, 0)) == -1)
		ERR_EXIT("fcntl");
	if ( fcntl(fd, F_SETFL, flags|flag) == -1)
		ERR_EXIT("fcntl");
}

void handler(int s)
{
	printf("catch sig %d\n", s);
}

int main( void )
{
	int fds[2];
	pid_t pid;
	
	struct sigaction sa;
	
	sa.sa_handler = handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	
	if ( sigaction(SIGPIPE, &sa, NULL) == -1)
		ERR_EXIT("sigaction");
	
	if ( pipe(fds) == -1)
		ERR_EXIT("pipe");

	if ( (pid=fork()) == -1)
		ERR_EXIT("fork");

	if ( pid == 0 ) {
		close(fds[0]);
		//sleep(1);
		if ( write(fds[1], "furong", 6) == -1)
			ERR_EXIT("write");
		close(fds[1]);
		exit(EXIT_SUCCESS);
	}

//	char buf[1024] = {};
	
//	set_flg(fds[0], O_NONBLOCK);
	close(fds[1]);
	close(fds[0]);

/*
	if ( read(fds[0], buf, 1024) == -1)
		ERR_EXIT("read");
	close(fds[0]);
	printf("buf=%s\n", buf);
*/
	
	return 0;
}

