#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define ERR_EXIT(m) \
	do { \
		fprintf(stderr, "[%s][%d]:%s %s\n", __FILE__, __LINE__, m, strerror(errno)); \
		exit(EXIT_FAILURE); \
	} while ( 0 )

typedef struct book {
	int price;
	char name[20];
}book_t;

int main( void )
{
	int fd;
	book_t *p;
	
	fd=open("book.dat", O_RDWR);
	if ( fd == -1)
		ERR_EXIT("open");
	
	p = (book_t*)mmap(NULL, 5*sizeof(book_t), PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
	if ( p == MAP_FAILED)
		ERR_EXIT("mmap");
	int i=0;
	
	for (i=0; i<5; i+=2) {
		printf("price:%d", p[i].price);
		printf("name :%s\n", p[i].name);
	}
	
	munmap(p, 5*sizeof(book_t));
	close(fd);
	return 0;
}

