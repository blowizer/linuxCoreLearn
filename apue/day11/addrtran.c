#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <stdio.h>
#include <stdlib.h>

int main( void )
{
	unsigned addr = 192<<24 | 168<<16 | 0<<8 | 200;
	printf("%X\n", addr);
	unsigned char *p = (unsigned char *)&addr;
	printf("%hhu.%hhu.%hhu.%hhu\n", p[0], p[1], p[2], p[3]);
	
	printf("%X\n", inet_addr("192.168.0.200"));
	struct in_addr ad;
	inet_aton("10.168.0.200", &ad);
	printf("%s\n", inet_ntoa(ad));
	
	in_addr_t at;
	struct in_addr ad2;
	at = inet_lnaof(ad);
	ad2.s_addr = at;
	printf("%s\n", inet_ntoa(ad2));
}

