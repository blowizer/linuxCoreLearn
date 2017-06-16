#include <stdio.h>

//联合，所有成员共用一块地方
//大小是最大成员的大小
int main( void )
{
	typedef union IP {
		unsigned char ip[4];
		unsigned int  net;
	} IP;
	
	IP myip = {0x12,0x34,0x56,0x78};//联合体一般不初始化
			 //如果想要初始化,只能初始化第一个成员
	printf("sizoef myip=%d\n", sizeof(myip));

	printf("ip[0]=%X\n", myip.ip[0]);
	printf("ip[1]=%X\n", myip.ip[1]);
	printf("ip[2]=%X\n", myip.ip[2]);
	printf("ip[3]=%X\n", myip.ip[3]);
	
	printf("%X\n", myip.net);
	
	printf("=============\n");
	int a= 0x12345678;
	char* pc = (char*)&a;
	int i;
	for (i=0; i<4; i++)
		printf("%X\n", pc[i]);
}

