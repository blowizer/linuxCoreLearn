#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>

#define ERR_EXIT(m) \
	do { \
		fprintf(stderr, "[%s][%d]:%s %s\n", __FILE__, __LINE__, m, strerror(errno)); \
		exit(EXIT_FAILURE); \
	} while ( 0 )

#define MAXLINE 1024

int main( void ) {
	int i;
	int stat = 1;
	int k = 0;
	pid_t pid;
	char *arge[8] = {};
	char buf[MAXLINE+1] = {};
	
	while ( 1 ) {

		stat = 1;
		k = 0;
		memset(arge, 0x00, sizeof(arge));
		memset(buf, 0x00, sizeof(buf)+1);

		printf("taogeshell> ");
		fflush(stdout);
		fgets(buf, MAXLINE, stdin);
		
		for (i=0; buf[i]!='\0'; i++)
			if ( isspace(buf[i]) != 0)
				break;
	
		arge[k++] = buf;
		for (; buf[i]!='\0'; i++) {
			if ( stat && isspace(buf[i]) ) {
				stat = 0;
				buf[i] = '\0';
			} else if (stat==0 && !isspace(buf[i])) {
				stat = 1;
				arge[k++] = buf+i;
			}
		}
		arge[k] = NULL;

		if ( memcmp(arge[0], "exit", 4) == 0)
			exit(0);
		if ( *arge[0] == '\0' )
			continue;
	
		if ( (pid=fork()) == -1)
			ERR_EXIT("fork");
		
		if ( pid == 0 ) {
			for (i=0; i<k; i++) {
				if ( memcmp(arge[i],">", 1) == 0 ) {
					int fd;
					fd=open(arge[i+1], O_WRONLY|O_CREAT, 0644);
					if ( fd == -1)
						ERR_EXIT("open");
					printf("before!\n");
					close(1);
					printf("after!\n");
					fcntl(fd, F_DUPFD, 0);
					arge[i] = NULL;
					k = i;
					break;
				}
			}
			for (i=0; i<k; i++)
				printf("%s\n", arge[i]);
			if ( execvp(arge[0], arge) == -1 )
				ERR_EXIT("execve");
		}
		wait(NULL);
	}
	
	return 0;
}

