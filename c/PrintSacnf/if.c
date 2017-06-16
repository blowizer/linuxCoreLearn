#include <stdio.h>

int main( void )
{
	int age;

	printf("请问多大:");
	scanf("%d", &age);
	
	if ( age<0 || 100<age )
	{
		if ( 100<age && age<150 )
		{
			printf("寿星啊，在家安度晚年!\n");
		}
		else if ( age >= 150 )
		{
			printf("老妖!\n");
		}
		else
		{
			printf("来自未来!\n");
		}
	}
	else if ( age < 18 )
	{
		printf("小朋友，回家写作业!\n");
	}
	else
	{
		printf("欢迎来尚观学习!\n");
	}
	
	return 0;
}

