#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main( void )
{
	srand(time(NULL));
	char *names[20] = {
		"苏洋洋", "武国军", "徐  鹏", "杜兴铎",
		"张  瑜", "徐  欣", "刘  健", "尹  东",
		"强  磊", "杨  宁", "吝旭阳", "夏  攀",
		"任伟文", "曹颜博", "马  涛", "李金焕",
		"杨文举", "王  琦", "魏思宽", "刘超伟"
	};
	int i;
	int j = rand()%20;

	for (i=0; i<20; i++)
	{
		if ( j == i )
			printf("[");
		else
			printf(" ");
		printf("%s%c%s",names[i],j==i?']':' ',(i+1)%4==0?"\n":"  ");
	}
	
	return 0;
}

