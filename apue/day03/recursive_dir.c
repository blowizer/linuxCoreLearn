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

void printdir(const char *dir, int gap)
{
	DIR *pd;
	struct dirent *dirent;
	struct stat sbuf;
	int i;
	
	if ( (pd=opendir(dir)) == NULL )
		ERR_EXIT("opendir"); 

	chdir(dir);
	while ( (dirent=readdir(pd)) != NULL ) {
		if ( memcmp(dirent->d_name, ".", 1) == 0 ||
			 memcmp(dirent->d_name, "..", 2) == 0 )
			continue;
		if ( lstat(dirent->d_name, &sbuf) == -1)
			ERR_EXIT("lstat");
		for (i=0; i<gap; i++)
			printf("%c", ' ');
		if ( S_ISDIR(sbuf.st_mode) ) {
			printf("%s\n", dirent->d_name);
			printdir(dirent->d_name, gap+4);
		} else {
			printf("%s\n", dirent->d_name);
		}
	}
	chdir("..");
	
	closedir(pd);
}

int main( void )
{
	printdir("..", 0);
	return 0;
}

