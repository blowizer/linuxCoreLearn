#include <stdio.h>

//位段:有时候每个成员我们可能只希望使用几个位，这是可以通过位段，指定成员占几位(bit数)
typedef struct mode
{
	unsigned char ur : 1; 
	unsigned char uw : 1;
	unsigned char ux : 1;

	unsigned char gr : 1; 
	unsigned char gw : 1;
	unsigned char gx : 1;
	
	unsigned char or : 1; 
	unsigned char ow : 1;
	unsigned char ox : 1;
}mode;

int main( void )
{
	mode m = {1,1,0, 1,0,0, 1,0,0};
	printf("%d\n", sizeof(mode));
	printf("%d%d%d%d%d%d%d%d%d\n",
			m.ur, m.uw, m.ux,
			m.gr, m.gw, m.gx,
			m.or, m.ow, m.ox);

	return 0;
}

