#include <unistd.h>
#include <fcntl.h>
#include <sys/ipc.h>
#include <sys/msg.h>

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
	int id;
	if ( (id=msgget(1234, IPC_CREAT|IPC_EXCL|0666)) == -1)
	//if ( (id=msgget(IPC_PRIVATE, 0666)) == -1)
		ERR_EXIT("msgget");
	return 0;
}
