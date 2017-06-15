#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <linux/ip.h>
#include <linux/udp.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main( void )
{
	int fd;
	int ret;
	int op = 1;
	char buf[1024] = {};
	struct iphdr *iphdr;
	struct udphdr *udphdr;
	struct in_addr addr;

	if ( (fd=socket(PF_INET, SOCK_RAW, IPPROTO_UDP)) == -1)
		perror("socket"),exit(1);
	setsockopt(fd, IPPROTO_IP, IP_HDRINCL, &op, sizeof(op));
	
	while ( 1 ) {
		ret=read(fd, buf, 1024);
		iphdr = (struct iphdr*)buf;
		addr.s_addr = iphdr->saddr;
		printf("source addr:%s\n", inet_ntoa(addr));
		addr.s_addr = iphdr->daddr;
		printf("dest addr:  %s\n", inet_ntoa(addr));
		printf("ttl:        %hhd\n", iphdr->ttl);
		printf("protocol:   %s\n", iphdr->protocol == IPPROTO_ICMP ? "ICMP":"NULL");
		printf("id:   %hu\n", iphdr->id);
		udphdr = (struct udphdr*)(buf+20);
		printf("\tsource:%d\n", ntohs(udphdr->source));
		printf("\tdest:%d\n", ntohs(udphdr->dest));
	}
}

