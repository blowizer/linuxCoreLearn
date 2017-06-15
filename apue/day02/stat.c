#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define ERR_EXIT(m) \
	do { \
		fprintf(stderr, "[%s][%d]:%s %s\n", __FILE__, __LINE__, m, strerror(errno)); \
		exit(EXIT_FAILURE); \
	} while ( 0 )

#define MAJOR(m) ((int)(unsigned short)(m.st_dev>>8)&0XFF)
#define MINOR(m) ((int)(unsigned short)m.st_dev&0XFF)

void filetype(struct stat * buf);
void perm(struct stat * buf);

int main( int argc, char *argv[] )
{
	if ( argc != 2 ) {
		fprintf(stderr, "usage: %s file\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	
	struct stat buf;
	struct passwd *pwd;
	struct group *grp;
	struct tm *ptm;
	
	if ( lstat(argv[1], &buf) == -1)
		ERR_EXIT("stat");
	
	printf("major: %d, minor: %d\n", MAJOR(buf), MINOR(buf));
	printf("inode: %d\n", buf.st_ino);
	
	//filetype(&buf);
	perm(&buf);
	printf(" %d", buf.st_nlink);
	pwd = getpwuid(buf.st_uid);
	printf(" %s", pwd->pw_name);
	grp = getgrgid(buf.st_gid);
	printf(" %s", grp->gr_name);
	printf(" %d", buf.st_size);
	ptm = localtime(&buf.st_mtime);
	printf(" %d月   %d", ptm->tm_mon+1, ptm->tm_mday);
	printf(" %d:%d", ptm->tm_hour, ptm->tm_min);
	if ( (buf.st_mode & S_IFMT) == S_IFLNK) {
		char buf[256] = {};
		readlink(argv[1], buf, 256);
		printf(" %s -> %s\n", argv[1], buf);
	} else {
		printf(" %s\n", argv[1]);
	}
	
	return 0;
}

void filetype(struct stat * buf)
{
	printf("file type: ");
	mode_t mode = buf->st_mode;
	
	switch( mode & S_IFMT ) {
		case S_IFSOCK:
			printf("socket\n");
		break;
		case S_IFLNK:
			printf("symbolic link\n");
		break;
		case S_IFREG:
			printf("regular file\n");
		break;
		case S_IFBLK:
			printf("block device\n");
		break;
		case S_IFDIR:
			printf("directory\n");
		break;
		case S_IFCHR:
			printf("character device\n");
		break;
		case S_IFIFO:
			printf("FIFO\n");
		break;
	}
	//printf("mode : %o\n", buf->st_mode&07777);
}

void perm(struct stat * pbuf)
{
	char buf[11] = "?---------";
	mode_t mode = pbuf->st_mode;
	switch( mode & S_IFMT ) {
		case S_IFSOCK:
			buf[0] = 's';
		break;
		case S_IFLNK:
			buf[0] = 'l';
		break;
		case S_IFREG:
			buf[0] = '-';
		break;
		case S_IFBLK:
			buf[0] = 'b';
		break;
		case S_IFDIR:
			buf[0] = 'd';
		break;
		case S_IFCHR:
			buf[0] = 'c';
		break;
		case S_IFIFO:
			buf[0] = 'p';
		break;
	}
	if ( mode & S_IRUSR )
		buf[1] = 'r';
	if ( mode & S_IWUSR )
		buf[2] = 'w';
	if ( mode & S_IXUSR )
		buf[3] = 'x';

	if ( mode & S_IRGRP )
		buf[4] = 'r';
	if ( mode & S_IWGRP )
		buf[5] = 'w';
	if ( mode & S_IXGRP )
		buf[6] = 'x';

	if ( mode & S_IROTH )
		buf[7] = 'r';
	if ( mode & S_IWOTH )
		buf[8] = 'w';
	if ( mode & S_IXOTH )
		buf[9] = 'x';
	
	printf("%s", buf);
}

