#include <unistd.h>
#include <fcntl.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <assert.h>

#define ERR_EXIT(m) \
	do { \
		fprintf(stderr, "[%s][%d]:%s %s\n", __FILE__, __LINE__, m, strerror(errno)); \
		exit(EXIT_FAILURE); \
	} while ( 0 )

#define MAXLINE 8192

struct msgbuf{
	long mtype;
	char mtext[MAXLINE];
};

int main( int argc, char *argv[] )
{
	int id;
	int ret;
	struct msgbuf *ptr;

	int flag = 0;
	int type = 0;
	int opt;
	while ( 1 ) {
		opt=getopt(argc, argv, "nt:");
		if ( opt == '?')
			ERR_EXIT("getopt");
		if ( opt == -1 )
			break;
		switch ( opt ) {
			case 'n':
				flag |= IPC_NOWAIT;
				break;
			case 't':
				type = atoi(optarg);
				break;
			default:
				break;
		}
	}

	if ( (id=msgget(1234, 0)) == -1)
		ERR_EXIT("msgget");
	ptr = (struct msgbuf*)malloc(sizeof(long)+MAXLINE);
	assert(ptr);

	ptr->mtype = type;
	if ( (ret=msgrcv(id, ptr, MAXLINE, type, flag)) == -1)
		ERR_EXIT("msgrcv");
	printf("read %d bytes type=%d\n", ret, ptr->mtype);
			
	return 0;
}

