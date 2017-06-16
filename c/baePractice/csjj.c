#include <stdio.h>

int main( void )
{
	int last = 21;
	int user;
	int computer;

	for ( ; ; ) {
		printf("还剩%d根火柴!\n", last);
		printf("用户取几根? ");
		scanf("%d", &user);
		if ( user<1 || user>4 || user>last)
			continue;
		printf("你取了%d根火柴!\n", user);
		last -= user;
		if ( last == 0) {
		  printf("你取走了最后一支火柴,你失败!\n");
		  break;
		}
	
		computer = 5 - user;
		printf("计算机取了%d根火柴!\n", computer);
		last -= computer;
	}

	return 0;
}

