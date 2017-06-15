#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <net/if.h>

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define ERR_EXIT(m) \
do { \
	fprintf(stderr, "[%s][%d] %s %s\n", \
	 __FILE__,__LINE__, m, strerror(errno)); \
	exit(EXIT_FAILURE);\
} while ( 0 )

int main( void )
{
	int fd;
	char buf[1024] = {};
	struct sockaddr_in addr = {};
	struct sockaddr_in caddr = {};
	
	if ( (fd=socket(PF_INET, SOCK_DGRAM, 0)) == -1)
		ERR_EXIT("socket");
	
	addr.sin_family = AF_INET;
	addr.sin_port = htons(9898);
	inet_pton(AF_INET, "224.2.2.2", &addr.sin_addr);
	int op = 1;
	setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &op, sizeof(op));
	if ( bind(fd, (struct sockaddr*)&addr, sizeof(addr)) == -1)
		ERR_EXIT("bind");
	
	struct ip_mreqn mreq;
	inet_aton("224.2.2.2", &mreq.imr_multiaddr);
	inet_aton("192.168.0.200", &mreq.imr_address);
	mreq.imr_ifindex = if_nametoindex("eth0");
	setsockopt(fd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq));
	
	socklen_t len = sizeof(caddr);
	recvfrom(fd, buf, 1024, 0, (struct sockaddr*)&caddr, &len);
	printf("%s:buf=%s\n", inet_ntoa(caddr.sin_addr), buf);

	close(fd);
}

