#include <stdio.h>

int main( void )
{
	int i;
	int sum = 0;
	int grade;

	for (i=0; ; i++)
	{
		printf("输入第%d人的成绩:", i+1);
		scanf("%d", &grade);
		if ( grade == -1 )
			break;
		sum = sum + grade;
	}
	
	printf("avg=%f\n", (double)sum/i);
}

