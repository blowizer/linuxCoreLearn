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

#define MAXLINE 1024

int main( int argc, char *argv[] )
{
	int ret;
	int fout;
	int fin;
	char buf[MAXLINE+1] = {};
	if ( argc != 2 )
		fprintf(stderr, "usage:%s file\n", argv[0]),exit(0);
	
	if ( (fout=open(argv[1], O_WRONLY|O_CREAT, 0644)) == -1)
		ERR_EXIT("open");
	
	if ( (fin=open("my.p", O_RDONLY)) == -1)
		ERR_EXIT("open");
	
	while ( (ret=read(fin, buf, MAXLINE)) > 0 ) {
		while ( write(fout, buf, ret) == -1){
			if ( errno == EINTR )
				continue;
			break;
		}
		memset(buf, 0x00, sizeof(buf));
	}
	
	close(fout);
	close(fin);
	
	return 0;
}

