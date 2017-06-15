#include <stdio.h>

int main( void )
{
	int i = 0;
aa:
	printf("我是美女奶茶妹妹!\n");
	goto bb;
	
	goto aa;

bb:
	printf("昙花一现!\n");
	
	goto cc;
	return 0;

cc:
	printf("凉茶，王老吉!\n");
	if ( ++i <= 2)
		goto bb;
}

