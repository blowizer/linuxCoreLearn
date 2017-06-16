#include <stdio.h>

int main( void )
{
	int grade = 0;
	
	do {
		printf("输入成绩:");
		if ( scanf("%d", &grade) != 1 ){
			printf("输入无效!");
			scanf("%*[^\n]");
			scanf("%*c");
			continue;
			printf("hehe");//这里不会被执行到
		} else {
			if ( grade<0 || 100<grade) {
				printf("成绩不在合法范围内!\n");
				scanf("%*[^\n]");
				scanf("%*c");
				grade = 0;
				continue;
			}
			printf("成绩是:%d\n", grade);
		}
	} while ( grade < 60 && grade >= 0 );

	printf("恭喜你,考试通过!\n");

	return 0;
}

