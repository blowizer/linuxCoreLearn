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
	struct msqid_ds buf;
	if ( (id=msgget(1234, 0)) == -1)
		ERR_EXIT("msgget");
	
	if ( msgctl(id, IPC_STAT, &buf) == -1)
		ERR_EXIT("msgctl");
	
	printf("permission:%o\n", buf.msg_perm.mode);
	printf("msg No.:%d\n", buf.msg_qnum);
	printf("bytes:%d\n", buf.__msg_cbytes);
	
/*
	sscanf("0600", "%o", &buf.msg_perm.mode);
	if ( msgctl(id, IPC_SET, &buf) == -1)
		ERR_EXIT("msgctl");
*/
	
	return 0;
}

