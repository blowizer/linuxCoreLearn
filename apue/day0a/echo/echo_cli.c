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

#define MAXLINE 8192

typedef struct msgbuf {
	long mtype;
	char mtext[MAXLINE];
}msgbuf;

void msg_cli(int id)
{
	int pid;
	msgbuf msg = {};

	msg.mtype = 1;
	pid = (int)getpid();
	
	while ( fgets(msg.mtext+4, MAXLINE-4, stdin) != NULL ) {
		*(int*)(msg.mtext) = pid;
		msg.mtype = 1;
		if ( msgsnd(id, &msg, strlen(msg.mtext+4)+4, 0) == -1)
			ERR_EXIT("msgsnd");
		memset(msg.mtext, 0x00, sizeof(msg.mtext));
		if ( msgrcv(id, &msg, MAXLINE, pid, 0) == -1)
			ERR_EXIT("msgrcv");
		printf("%s", msg.mtext+4);
		memset(msg.mtext, 0x00, sizeof(msg.mtext));
	}
}

int main( void )
{
	int id;
	if ( (id=msgget(1234, 0)) == -1)
		ERR_EXIT("msgget");
	
	msg_cli(id);

	return 0;
}

