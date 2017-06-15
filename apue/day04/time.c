#include <unistd.h>
#include <fcntl.h>
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

int main( void )
{
	struct tm *pt;
	char buf[26+1] = {};
	time_t t = time(NULL);
	if ( -1 == t )
		ERR_EXIT("time");
	
	pt = localtime(&t);
	/*
	printf("%d\n", t);
	printf("sec:%d\n", t%60);
	printf("min:%d\n", t/60%60);
	printf("hou:%d\n", (t/60/60+8)%24);
	*/

	while ( 1 ) {
	
		//printf("%02d:%02d:%02d\r", 
		//		(t/60/60+8)%24, t/60%60, t%60);

		/*
		printf("%04d年%02d月%02d日 "
				"%02d:%02d:%02d\r", 
				pt->tm_year + 1900, 
				pt->tm_mon + 1, 
				pt->tm_mday, 
				pt->tm_hour,
				pt->tm_min,
				pt->tm_sec);
		*/
		//printf("%s\n", ctime(&t));
		
		//strftime(buf, 26, "%F %T", pt);
		//printf("%s\r", buf);
		memset(buf, 0x00, sizeof(buf));
		fflush(stdout);
		t = time(NULL);
		printf("t=%d\n", t);
		pt = localtime(&t);
		printf("return=%d\n", mktime(pt));
		sleep(1);
	}
	
	return 0;
}

