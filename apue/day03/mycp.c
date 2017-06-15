#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <dirent.h>

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

void cp_file(char* src, char *dest, mode_t mode)
{
	int fdout;
	int fdin;
	int ret;
	char buf[MAXLINE+1] = {};
	
	fdin = open(src, O_RDONLY);
	fdout=open(dest, O_WRONLY|O_CREAT, mode);
	if ( fdout==-1 || fdin==-1)
		ERR_EXIT("open");

	while ( 1 ) {
		while ( (ret=read(fdin, buf, MAXLINE)) == -1) {
			if ( errno == EINTR)
				continue;
			break;
		}
		if ( ret == 0 )
			break;
		write(fdout, buf, ret);
	}
	
	if ( ret == -1)
		ERR_EXIT("read");
	
	close(fdin);
	close(fdout);
}

void cp_dir(const char *src, const char *dest)
{
	DIR *dp;
	struct dirent *entp;
	struct stat sbuf;
	
	if ( (dp=opendir(src)) == NULL ) 
		ERR_EXIT("opendir");
	
	while ( (entp=readdir(dp) ) != NULL ) {
		if ( strcmp(entp->d_name, "..") == 0
			|| strcmp(entp->d_name, ".") == 0 )
			continue;

		char *name_dest=malloc(strlen(dest)+1+strlen(entp->d_name)+1);
		char *name_src=malloc(strlen(src)+1+strlen(entp->d_name)+1);
		sprintf(name_dest, "%s/%s", dest, entp->d_name);
		sprintf(name_src, "%s/%s", src, entp->d_name);
		if ( lstat(name_src, &sbuf) == -1)
			ERR_EXIT("lstat");
		if ( S_ISREG(sbuf.st_mode) ) {
			cp_file(name_src, name_dest, sbuf.st_mode);
		} else if ( S_ISDIR(sbuf.st_mode) ) {
			mkdir(name_dest, sbuf.st_mode);
			cp_dir(name_src, name_dest);
		}
	}
	
	closedir(dp);
}

int main( int argc, char *argv[] )
{
	if ( argc != 3 ) {
		fprintf(stderr, "%s src dest\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	mode_t oldmask = umask(0);
	struct stat buf;
	struct stat bufdest;
	
	if ( lstat(argv[1], &buf) == -1)
		ERR_EXIT("lstat");
	
	if ( S_ISREG(buf.st_mode) ) {
		//源文件是普通文件
		if ( lstat(argv[2], &bufdest) == -1) {
			if ( errno == ENOENT ) {
				//创建目标文件，并拷贝源文件的内容
				cp_file(argv[1], argv[2], buf.st_mode);
			}else
				ERR_EXIT("lstat");
		} else  {
			if ( S_ISDIR(bufdest.st_mode) ) {
				char *p = malloc(strlen(argv[2])+1+strlen(argv[1])+1);	
				memset(p, 0x00, sizeof(p));
				sprintf(p, "%s/%s", argv[2], argv[1]);
				cp_file(argv[1], p, buf.st_mode);
			} else {
				char c;
				printf("file %s exist, do you want overwrite ? y/n", argv[2]);
				scanf(" %c", &c);
				if ( c=='y' || c=='Y' ) {
					unlink(argv[2]);
					cp_file(argv[1], argv[2], buf.st_mode);
				}
			}
		}
	} else if ( S_ISDIR(buf.st_mode) ) {
		if ( lstat(argv[2], &bufdest) == -1) {
			if ( errno == ENOENT) {
				mkdir(argv[2], buf.st_mode);
				cp_dir(argv[1], argv[2]);
			}
		} else if ( S_ISREG(bufdest.st_mode) ) {
			printf("%s is a file!\n", argv[2]);
			exit(EXIT_FAILURE);
		} else if ( S_ISDIR(bufdest.st_mode) ) {
			char *p = malloc(strlen(argv[2])+1+strlen(argv[1])+1);
			memset(p, 0x00, sizeof(p));
			sprintf(p, "%s/%s", argv[2], argv[1]);
			mkdir(p, buf.st_mode);
			cp_dir(argv[1], p);	
		}
	}
	
	umask(oldmask);

	return 0;
}

