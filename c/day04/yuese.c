#include <stdio.h>

int main( void ) {
	int i = -1;
	int j = 0;
	int kill = 0; //跳海的人数，用于控制循环结束
	int a[8] = {1,2,3,4,5,6,7,8};
	
	while ( kill < 8 ) {
	
		//for用于找到第三个离开的人
		for (j=0; j<=2; ) {
			i = (i+1)%8; //让i在0-7之间找下一个
			if (a[i] != -1 )
				j++;
		}

		printf("%d ", a[i]);
		a[i] = -1; //离开后位置用-1表示
		kill ++; //跳海人数+1
	}
	printf("\n");
	
	return 0;
}

