#include <stdio.h>

typedef struct stu {
	int id;
	char name[20];
	double grade;
}stu_t;

#define MAXSIZE 5

void println(stu_t *s, int len)
{
	int i;

	printf("-------学生信息-------\n");
	for (i=0; i<len; i++) 
		printf("%d %s %g\n", s[i].id, s[i].name, s[i].grade);
	printf("----------------------\n");
}

/*
 * 功能：
 *		从s中查找关键字key，如果存在，通过res返回
 * 参数：
 * 		s
 * 		len
 * 		key
 * 		res 结果参数
 * 	返回值：
 * 		0成功，-1失败
 */
int find(stu_t *s, int len, int key, stu_t **res)
{
	int i;
	int ret = -1;
		
	for (i=0; i<len; i++) {
		if ( s[i].id == key ) {
			*res = s+i;
			ret = 0;
			break;
		}
	}
	
	return ret;
}

int main( void )
{
	stu_t student[MAXSIZE] = {};
	int i;
	
	for (i=0; i<MAXSIZE; i++) {
		printf("id: ");
		scanf("%d", &student[i].id);
		printf("name: ");
		scanf("%s", student[i].name);
		printf("grade: ");
		scanf("%lf", &student[i].grade);
	}
	
	println(student, MAXSIZE);
	printf("find: ");
	int key;
	stu_t *ret = NULL;
	scanf("%d", &key);
	if ( find(student, MAXSIZE, key, &ret) != 0 ) {
		printf("not found!\n");
	} else {
		printf("%d %s %g\n", ret->id, ret->name, ret->grade);
	}
}

