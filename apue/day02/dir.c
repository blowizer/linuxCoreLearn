#include <unistd.h>
#include <fcntl.h>
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

int main( void )
{
	DIR *dp;
	struct dirent *p;
	dp = opendir(".");
	if ( dp == NULL )
		ERR_EXIT("opendir");
	
	while ( (p=readdir(dp)) != NULL ) {
		if ( p->d_name[0] == '.')
			continue;
		printf("%s\n", p->d_name);
	}
	
	closedir(dp);

	return 0;
}

