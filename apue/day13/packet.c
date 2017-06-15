#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <linux/ip.h>
#include <linux/if_ether.h>

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
	int fd;
	struct ethhdr *eh;
	struct iphdr  *iph;
	char buf[1024] = {};
	struct in_addr addr;
	
	if ( (fd=socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL))) == -1)
		ERR_EXIT("socket");
	
	while ( 1 ) {
		read(fd, buf, 1023);
		eh = (struct ethhdr*)buf;
		printf("%02X:%02X:%02X:%02X:%02X:%02X\n", 
			eh->h_dest[0], eh->h_dest[1],
			eh->h_dest[2], eh->h_dest[3],
			eh->h_dest[4], eh->h_dest[5]);
		if ( ntohs(eh->h_proto) == 0X0800) {
			iph = (struct iphdr*)(buf+14);
			addr.s_addr = iph->saddr;
			printf("\t%s\n", inet_ntoa(addr));
		} else if ( ntohs(eh->h_proto) == 0X0806) {
			printf("ARP请求!\n");
		} else if ( ntohs(eh->h_proto) == 0x0835) {
			printf("ARP应答!\n");
		}
 	}
}

