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
	
	if ((fd=open(filename, O_RDWR|O_CREAT|O_EXCL, 0644))==-1){
		fd = open(filename, O_RDWR|O_APPEND);
	}
	
	return fd;
}

void input(stu_t *record) {
	bzero(record, sizeof(stu_t));
	printf("id: ");
	scanf("%d", &record->no);
	printf("name: ");
	scanf("%s", record->name);
	printf("score: ");
	scanf("%lf", &record->score);
}

int save(int fd, stu_t *record){
	int ret;
	while ( (ret=write(fd, record, sizeof(stu_t))) == -1){
		if ( errno == EINTR)
			continue;
		break;
	}

	return ret;
}

int isContinue( void )
{
	char c;

	printf("continue[y/n]: ");
	scanf(" %c", &c);
	if ( c=='Y' || c=='y')
		return 1;

	return 0;
}

int main( void )
{
	int fd;
	stu_t st = {};
	
	fd = openfile("stu.dat");
	if ( fd == -1)
		ERR_EXIT("open file");
	
	while ( 1 ) {
		input(&st);
		save(fd, &st);
		if ( !isContinue() )
			break;
	}
	
	close(fd);
	
	return 0;
}

