#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int getnum(int a)
{
	return rand() % a + 1;
}

int input(int a, int b)
{
	int n;
	while ( scanf("%d",&n)==0 || n<a || n>b ) {
		while ( getchar() != '\n')
			;
	}
	
	return n;
}

void guess(int num)
{
	int guess_num = 0;
	
	for ( ; ; )
	{
		printf("请猜1-100之间的数: ");
		guess_num = input(1, 100);
		if ( guess_num == num )
		{
			printf("恭喜你对了!\n");
			break;
		}
		else if ( guess_num < num )
			printf("小了!\n");
		else
			printf("大了!\n");
	}
}

int contiu( void )
{
	char c;

	printf("是否继续y/n? ");
	scanf(" %c", &c);
	
	return c=='y' || c=='Y';
}

int main( void )
{
	srand(time(NULL));
	int num;
	
	do{
		num = getnum(100);
		//printf("%d\n", num);
		guess(num);
	} while (contiu());

	return 0;
}

