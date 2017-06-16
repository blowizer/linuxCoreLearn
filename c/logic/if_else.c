#include <stdio.h>

int main( void )
{
	int grade;

	printf("输入成绩:");
	scanf("%d", &grade);

	if ( grade<0 || 100<grade ) {
		printf("输入无效!");
		return 1;
	}
/*
	if ( grade >= 80 ) {
		printf("优秀!\n");
	} else if ( grade >= 70 ) {
		printf("良好!\n");
	} else if ( grade >= 60 ) {
		printf("及格!\n");
	} else {
		printf("不及格!\n");
	}
*/
	grade = grade / 10;
	switch ( grade ) {
		case 10:
		case 9:
		case 8:
			printf("优秀!\n");
			break;
		case 7:
			printf("良好!\n");
			break;
		case 6:
			printf("及格!\n");
			break;
		default:
			printf("不及格!\n");
			break;
	}

	return 0;
}

