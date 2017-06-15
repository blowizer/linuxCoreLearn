#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <stdio.h>
#include <stdlib.h>
 
int main(void)
{
	printf("%X\n",inet_addr("192.168.0.200") );
	struct in_addr ad;
	inet_aton("192.168.0.1",&ad);
	printf("%s\n",inet_ntoa(ad));
	
	in_addr_t at;
	struct in_addr ad2;
	at=inet_netof(ad);
	ad2.s_addr=at;
	printf("%s\n",inet_ntoa(at));

	in_addr_t at;
	struct in_addr ad3;
	at=inet_lnaof(ad);
	ad3.s_addr=at;
	printf("%s\n",inet_ntoa(at));
}

