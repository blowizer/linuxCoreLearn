#include <unistd.h>
#include <netdb.h>
#include <errno.h>

#include <stdio.h>
#include <stdlib.h>

int main ( void )
{
	struct hostent *host;
	
	host=gethostbyname("localhost");
	if ( host == NULL ) {
		perror("gethost");
		exit(1);
	}
	
	printf("addr:%hhd.%hhd.%hhd.%hhd\n", 
		host->h_addr[0],
		host->h_addr[1],
		host->h_addr[2],
		host->h_addr[3]
		);
}

