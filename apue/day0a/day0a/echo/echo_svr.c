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

void echo_svr(int id)
{
	int n;
	int pid;
	msgbuf msg = {};
	
	while ( 1 ) {
		memset(msg.mtext, 0x00, sizeof(msg.mtext));
		if ( (n=msgrcv(id, &msg, MAXLINE, 1, 0)) == -1)
			ERR_EXIT("msgrcv");
		pid = *(int*)(msg.mtext);
		printf("pid=%d, buf=%s\n", pid, msg.mtext+4);
		msg.mtype = pid;
		if ( msgsnd(id, &msg, strlen(msg.mtext+4)+4, 0) == -1)
			ERR_EXIT("msgsnd");
	}
}

int main( void )
{
	int id;
	
	if ( (id=msgget(1234, IPC_CREAT|0666)) == -1)
		ERR_EXIT("msget");		
	
	echo_svr(id);

	return 0;
}

