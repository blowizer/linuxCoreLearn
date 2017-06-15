#include <stdio.h>

typedef struct student student_t;
struct student
{
	char name[20];
	int  id;
	float grade;
};

int main( void )
{
	int i;
	int j;
	int choose;
	int num = 0;
	student_t stu[50] = {};
	
	do {
		printf("\n\n\n\n\n\n\n\n\n\n\n\n\n");
		printf("+------欢迎进入UMIS-------+\n");
		printf("|                         |\n");
		printf("|  1 查看        2 添加   |\n");
		printf("|  3 删除        4 修改   |\n");
		printf("|  5 排序        0 退出   |\n");
		printf("+-------------------------+\n");
		printf("choose: ");
		scanf("%d", &choose);

		switch ( choose ) {
		case 0:
			printf("感谢使用UMIS\n");
			break;
		case 1:
			printf("+--------------------------+\n");
			for (i=0; i<num; i++) {
				printf("| %06d | %8s | %5.2f |\n", 
					stu[i].id, stu[i].name, stu[i].grade);
			printf("+--------------------------+\n");
			}
			scanf("%*[^\n]");
			scanf("%*c");
			getchar();
			break;
		case 2:
			printf("姓名:");
			scanf("%s", stu[num].name);
			printf("学号:");
			scanf("%d", &stu[num].id);
			printf("成绩:");
			scanf("%f", &stu[num].grade);
			num++;
			break;
		case 3:
		{
			int id;
			printf("学号:");
			scanf("%d", &id);
			for (i=0; i<num; i++) {
				if ( stu[i].id == id ) {
					break;
				}
			}
			if ( i == num ) {
				printf("查无此人!\n");
			} else {
				for ( ; i<num; i++)
					stu[i] = stu[i+1];
				num--;
			}
	
			scanf("%*[^\n]");
			scanf("%*c");
			getchar();
		}
		break;
		case 4:
		{
			int id;
			float score;
			printf("id:");
			scanf("%d", &id);
			printf("成绩:");
			scanf("%f", &score);
			for (i=0; i<num; i++) {
				if ( id == stu[i].id ) {
					printf("找到!\n");
					stu[i].grade = score;
					break;
				}
			}
		}
		break;
		case 5:
			for (i=0; i<num; i++)
				for (j=i; j<num; j++)
					if ( stu[j].grade < stu[i]. grade ) {
						student_t tmp;
						tmp = stu[i];
						stu[i] = stu[j];
						stu[j] = tmp;
					}
			break;
		default:
			break;
		}
	} while ( choose != 0 );

	return 0;
}

