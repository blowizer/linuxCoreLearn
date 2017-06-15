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

#define MAXLINE 2

int main( int argc, char *argv[] )
{
	int fin;
	int fout;
	int ret;
	char buf[MAXLINE+1]; 
	
	if ( argc != 3 ) {
		fprintf(stderr, "%s infile outfile\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	
	if ( (fin=open(argv[1], O_RDONLY)) == -1)
		ERR_EXIT("open source file");
	if ( (fout=open(argv[2], O_WRONLY|O_CREAT|O_EXCL))==-1){
		if ( (fout=open(argv[2], O_WRONLY|O_TRUNC)) == -1) {
			close(fin);
			ERR_EXIT("open dest file");
		}
	}
	
	while ( 1 ) {
		if ( (ret=read(fin, buf, MAXLINE)) <= 0) {
			if ( errno == EINTR)//被信号打断后要重新读内容
				continue;
			break;
		}
	
		while ( write(fout, buf, ret) == -1) {
			if ( errno == EINTR)
				continue;
			ERR_EXIT(fout);
		}
		memset(buf, 0x00, sizeof(buf));
	} 
	
	if ( ret == -1)
		ERR_EXIT("read");
	
	close(fin);
	close(fout);

	return 0;
}

