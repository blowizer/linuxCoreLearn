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

typedef struct stu{
	int    no;
	char   name[20];
	double score;
}stu_t;

int openfile(const char *filename) {
	int fd;
	
	fd=open(filename, O_RDWR);
	
	return fd;
}

void output(const stu_t *record) {
	printf("id    = %d\n", record->no);
	printf("name  = %s\n", record->name);
	printf("score = %lf\n", record->score);
}

int load(int fd, stu_t *record){
	int ret;
	while ( (ret=read(fd, record, sizeof(stu_t))) == -1){
		if ( errno == EINTR)
			continue;
		break;
	}

	return ret;
}
/*
int isContinue( void )
{
	char c;

	printf("continue[y/n]: ");
	scanf(" %c", &c);
	if ( c=='Y' || c=='y')
		return 1;

	return 0;
}
*/

int main( void )
{
	int fd;
	stu_t st = {};
	
	fd = openfile("stu.dat");
	if ( fd == -1)
		ERR_EXIT("open file");
	
	while ( 1 ) {
		if ( load(fd, &st) <= 0 )
			break;
		output(&st);
		bzero(&st, sizeof(stu_t));
	}
	
	close(fd);
	
	return 0;
}

