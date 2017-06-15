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
typedef struct msgbuf {
	long mtype;
	char mtext[1];
}msgbuf;


int main( int argc, char *argv[] )
{
	if ( argc != 3 )
		fprintf(stderr, "%s <bytes> <type>\n", argv[0]),exit(0);
	
	int id;
	int len = atoi(argv[1]);
	int type = atoi(argv[2]);
	struct msgbuf *ptr = NULL;

	if ( (id=msgget(1234, 0)) == -1)
		ERR_EXIT("msgget");
	
	ptr = (msgbuf*)malloc(sizeof(long)+len);
	ptr->mtype = type;
	//if ( msgsnd(id, ptr, len, IPC_NOWAIT) == -1)
	while ( msgsnd(id, ptr, len, 0) == -1) {
		if ( errno == EINTR)
			continue;
		ERR_EXIT("msgsnd");
	}
	
	return 0;
}

